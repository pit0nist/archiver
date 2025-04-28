#pragma once


#include <string>
#include <filesystem>
#include "inout.h"
#include "trie.h"
#include "array"

class Decoder {
public:
    explicit Decoder(std::filesystem::path name);

private:
    bool DecodeFile();
    void ReadOrder(std::vector<int32_t>& order, std::vector<size_t>& length);
    Node* BuildTrie(const std::vector<int32_t>& order, const std::vector<Mask>& codes);
    int32_t ReadSymbol(Node* root);
    void ReadName(Node* root, std::string& name);
    bool ReadWriteContent(Node* root, const std::string& name);

    Reader reader_;
};