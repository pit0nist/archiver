#include "encoder.h"
#include "inout.h"
#include "priority_queue.h"

Encoder::Encoder(std::filesystem::path path, const std::vector<std::filesystem::path>& names) : writer_(std::move(path)) {
    for (auto it = names.begin(); it != names.end(); ++it) {
        EncodeFile(*it, std::next(it) == names.end());
    }
}

void Encoder::EncodeFile(const std::filesystem::path& name, bool is_end) {
    std::vector<int32_t> number(MAX_CHAR_NUMBER);
    BuildHuff(name, number);
    std::vector<size_t> length(MAX_CHAR_NUMBER);


    Node* root = BuildTrie(number);
    std::vector<int32_t> order;
    root->GetLength(0, order, length);
    std::sort(order.begin(), order.end());
    MakeSorted(order, length);
    std::vector<Mask> codes(MAX_CHAR_NUMBER);
    MakeCanonical(order, length, codes);
    WriteHeader(order, length);
    WriteContent(name, is_end, codes);
    delete root;
}

void Encoder::BuildHuff(const std::filesystem::path& name, std::vector <int32_t>& number) {
    number[FILENAME_END]++;
    number[ONE_MORE_FILE]++;
    number[ARCHIVE_END]++;
    for (char c : name.filename().string()) {
        number[c]++;
    }
    Reader reader(name);
    for (int32_t c = 0; reader.ReadSymb<BYTE>(c);) {
        number[c]++;
    }
}

Node* Encoder::BuildTrie(const std::vector<int32_t>& number) {

    PriorityQueue pq;
    for (int32_t c = 0; c < static_cast<int32_t>(MAX_CHAR_NUMBER); ++c) {
        if (number[c] != 0) {
            Node* tmp = new Node(c, number[c]);
            pq.Insert(tmp);
        }
    }
    while (pq.Size() > 1) {
        Node* n1 = pq.Top();
        pq.Pop();
        Node* n2 = pq.Top();
        pq.Pop();

        pq.Insert( new Node(std::min(n1->GetSymb(), n2->GetSymb()), n1->GetCol() + n2->GetSymb(), n1, n2));
    }
    return pq.Top();
}


void Encoder::MakeSorted(std::vector<int32_t>& order, std::vector<size_t>& length) {
    std::stable_sort(order.begin(), order.end(), [&length](int32_t a, int32_t b)
                     { return length[a] < length[b]; });
}

void Encoder::WriteHeader(std::vector<int32_t>& order, std::vector<size_t>& length) {

    writer_.WriteSymbol<SYMBOL>(static_cast<int32_t>(order.size()));
    for (auto c : order) {
        writer_.WriteSymbol<SYMBOL>(c);
    }
    std::sort(length.begin(), length.end());
    size_t max = length.back();
    for (size_t i = 1; i <= max; ++i) {
        const long col = std::count(length.begin(), length.end(), i);
        writer_.WriteSymbol<SYMBOL>(static_cast<int32_t>(col));
    }
}

void Encoder::WriteContent(const std::filesystem::path& name, bool is_end,
                           const std::vector<Mask>& codes) {
    for (char c : name.filename().string()) {
        writer_.Eat(codes[c]);
    }
    writer_.Eat(codes[FILENAME_END]);
    Reader reader(name);
    for (int32_t c = 0; reader.ReadSymb<BYTE>(c);) {
        writer_.Eat(codes[c]);
    }
    writer_.Eat(codes[is_end ? ARCHIVE_END : ONE_MORE_FILE]);
}