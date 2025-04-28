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
//    std::array<size_t, MAX_CHAR_NUMBER> freq;
    BuildHuff(name, number);
//    std::vector<Node*> link(MAX_CHAR_NUMBER);
    std::vector<size_t> length(MAX_CHAR_NUMBER);
//    std::array<Node*, MAX_CHAR_NUMBER> link;


    Node* root = BuildTrie(number);
    std::vector<int32_t> order;
    root->GetLength(0, order, length);
    std::sort(order.begin(), order.end());
//    std::cout << order.size() << std::endl;
    MakeSorted(order, length);
    std::vector<Mask> codes(MAX_CHAR_NUMBER);
//    std::array<Mask, MAX_CHAR_NUMBER> codes;
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
//                         const std::vector<size_t>& length) {
//    Heap<Node*, Node::Comp> heap;

    PriorityQueue pq;
//    std::priority_queue <Node> pq;
//    Trie trie;
    for (int32_t c = 0; c < static_cast<int32_t>(MAX_CHAR_NUMBER); ++c) {
        if (number[c] != 0) {
//            std::cout << " " << c << std::endl;
            Node* tmp = new Node(c, number[c]);
//            heap.Push(tmp);
            pq.Insert(tmp);
//            trie.Add(tmp);
//            pq.push(tmp);
        }
    }
    while (pq.Size() > 1) {
//        Node* n1 = heap.Pop();
//        Node* n2 = heap.Pop();
//
//        heap.Push( new Node(std::min(n1->GetSymb(), n2->GetSymb()), n1->GetCol() + n2->GetCol(), n1, n2));
        Node* n1 = pq.Top();
        pq.Pop();
        Node* n2 = pq.Top();
        pq.Pop();

        pq.Insert( new Node(std::min(n1->GetSymb(), n2->GetSymb()), n1->GetCol() + n2->GetSymb(), n1, n2));
    }
//    return heap.Top();
    return pq.Top();
}

//void Encoder::GetLength(Node* root, int ln, std::vector<int32_t>& order, std::vector<size_t>& length) {
//    if (root->IsTerm()) {
//        order.emplace_back(root->GetSymb());
//        length[root->GetSymb()] = ln;
//        return;
//    }
//
//    for (int i = 0; i < 2; i++) {
//        if (root->GetSon(i) != nullptr) {
//            GetLength(root->GetSon(i), ln + 1, order, length);
//        }
//    }
//}


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
//        auto itl = std::lower_bound(length.begin(), length.end(), i);
//        auto itr = std::upper_bound(length.begin(), length.end(), i);
//        writer_.WriteSymbol<SYMBOL>(static_cast<int32_t>(itr - itl));
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