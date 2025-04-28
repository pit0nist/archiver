//#ifndef CPP_HSE_ENCODER_H
//#define CPP_HSE_ENCODER_H

#pragma once

#include "fstream"
#include "filesystem"
#include <functional>
#include "inout.h"
#include "trie.h"

class Encoder {
public:
    Encoder(std::filesystem::path path, const std::vector<std::filesystem::path>& names);

private:
    void EncodeFile(const std::filesystem::path& name, bool is_end);
    void BuildHuff(const std::filesystem::path& name, std::vector<int32_t>& number);
    Node* BuildTrie(const std::vector <int32_t>& number);
//    void GetLength(Node* root, int ln, std::vector<int32_t>& order, std::vector<size_t>& length);
    static void MakeSorted(std::vector<int32_t>& order, std::vector<size_t>& length);
    void WriteHeader(std::vector<int32_t>& order, std::vector<size_t>& length);
    void WriteContent(const std::filesystem::path& name, bool is_end, const std::vector<Mask>& codes);

    Writer writer_;
};

//#endif  // CPP_HSE_ENCODER_H
