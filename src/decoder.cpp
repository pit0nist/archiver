#include "decoder.h"

Decoder::Decoder(std::filesystem::path name) : reader_(std::move(name)) {
    do {
    } while (DecodeFile());
}

bool Decoder::DecodeFile() {
    std::vector<int32_t> order;
    std::vector<size_t> code_len(MAX_CHAR_NUMBER);
    ReadOrder(order, code_len);
    std::vector<Mask> codes(MAX_CHAR_NUMBER);
//    std::array<std::vector<bool>, MAX_CHAR_NUMBER> codes;
    MakeCanonical(order, code_len, codes);
    Node* root = BuildTrie(order, codes);
    std::string name;
    ReadName(root, name);
    bool result = ReadWriteContent(root, name);
    delete root;
    return result;
}

void Decoder::ReadOrder(std::vector<int32_t>& order, std::vector<size_t>& code_len) {
    int32_t symbols_count = reader_.ReadSymb<SYMBOL>();
    for (size_t i = 0; i < static_cast<size_t>(symbols_count); ++i) {
        order.push_back(reader_.ReadSymb<SYMBOL>());
    }
    std::fill(code_len.begin(), code_len.end(), 0);
    for (size_t i = 0, len = 1; i < static_cast<size_t>(symbols_count); ++len) {
        for (size_t cnt = reader_.ReadSymb<SYMBOL>(); cnt; --cnt, ++i) {
            code_len[order[i]] = len;
        }
    }
}

Node* Decoder::BuildTrie(const std::vector<int32_t>& order, const std::vector<Mask>& codes) {
    Node* root = new Node();
    for (int32_t c : order) {
        root->Add(c, codes[c]);
    }
    return root;
}

int32_t Decoder::ReadSymbol(Node* v) {
    while (!v->IsTerm()) {
        v = v->GetSon(reader_.ReadSymb<BIT>());
    }
    return v->GetSymb();
}

void Decoder::ReadName(Node* root, std::string& name) {
    for (int32_t c = ReadSymbol(root); c != FILENAME_END; c = ReadSymbol(root)) {
        name.push_back(static_cast<char>(c));
    }
}

bool Decoder::ReadWriteContent(Node* root, const std::string& name) {
    Writer writer(name);
    for (int32_t c = ReadSymbol(root);; c = ReadSymbol(root)) {
        switch (c) {
            case ONE_MORE_FILE:
                return true;
            case ARCHIVE_END:
                return false;
            default:
                writer.WriteSymbol<BYTE>(c);
        }
    }
}
