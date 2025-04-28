#pragma once

#include <array>
#include <cstddef>
#include <vector>
#include "inout.h"
#include "cstdint"

class Node {
public:
    struct Comp {
        bool operator()(Node* a, Node* b) const;
    };

    explicit Node(int32_t c = 0, size_t cnt = 0, Node* left = nullptr, Node* right = nullptr);
    ~Node();

    Node*& GetSon(bool x);
    [[nodiscard]] bool IsTerm() const;
    [[nodiscard]] int32_t GetSymb() const;
    [[nodiscard]] size_t GetCol() const;
    [[nodiscard]] std::vector<bool> GetMask() const;
    void Add(int32_t c, const std::vector<bool>& code);
    void GetLength(int ln, std::vector<int32_t> &order, std::vector<size_t> &length);

private:
    Node* left_;
    Node* right_;
    int32_t symb_;
    size_t col_;
//    Node* par_ = nullptr;

};

bool Check(Node* a, Node* b);


