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


//
//
////#ifndef CPP_HSE_TRIE_H
////#define CPP_HSE_TRIE_H
//
//#pragma once
//
//
//#include "cstdint"
//#include "algorithm"
//#include "vector"
//#include "tuple"
//
//struct Node {
//    int32_t go[2], num;
//    unsigned int min_elem;
//    int32_t prior;
//
//    Node() {
//        go[0] = go[1] = -1;
//        prior = 0;
//        num = 0;
//    }
//
//    Node(int32_t n, int32_t count, unsigned int symb) {
//        go[0] = go[1] = -1;
//        num = n;
//        prior = count;
//        min_elem = symb;
//    }
//
//    Node(Node l, Node r, int32_t n) {
//        go[0] = l.num, go[1] = r.num;
//        prior = l.prior + r.prior;
//        min_elem = std::min(l.min_elem, r.min_elem);
//        num = n;
//    }
//
//    bool operator < (Node & other) {
//        return std::make_pair(prior, min_elem) < std::make_pair(other.prior, other.min_elem);
//    }
//};
//
////bool operator < (const Node & n1, const Node & n2) {
////    return std::tie(n1.prior, n1.min_elem) < std::tie(n2.prior, n2.min_elem);
////}
//
//class Trie {
//public:
//    Trie() {
//        trie_.resize(1);
//    }
//
//    ~Trie() {
//        trie_.clear();
//    }
//
//    Node Add(Node & n1, Node & n2) {
//        Node tmp = Node(n1, n2, Size());
//        trie_.emplace_back(tmp);
//        return tmp;
//    }
//
//    void Add(Node & n1) {
//        trie_.emplace_back(n1);
//    }
//
//    void Add(int32_t root, const std::vector<bool>& mask, int32_t elem) {
//        for (auto x : mask) {
//            if (trie_[root].go[x] == -1) {
//                trie_.emplace_back(Node());
//                trie_.back().num = Size() - 1;
//                trie_[root].go[x] = Size() - 1;
//            }
//            root = trie_[root].go[x];
//        }
//        trie_[root].min_elem = elem;
//    }
//
//    Node Get(int x) {
//        return trie_[x];
//    }
//
//    int32_t Size() {
//        return static_cast<int32_t>(trie_.size());
//    }
//
//    void GetCanonical(int32_t p, size_t sz, std::vector <size_t>& canonical) {
//        if (trie_[p].go[0] == -1 && trie_[p].go[1] == -1) {
//            canonical[trie_[p].min_elem] = sz;
////                emplace_back(sz, trie_[p].min_elem);
////            std::cout << s << " " << trie_[p].min_elem << std::endl;
//            return;
//        }
//        if (trie_[p].go[0] != -1) {
//            GetCanonical(trie_[p].go[0], sz + 1, canonical);
//        }
////        v.emplace_back()
////        s.back() = '1';
//        if (trie_[p].go[1] != -1) {
//            GetCanonical(trie_[p].go[1], sz + 1, canonical);
//        }
////        s.pop_back();
//    }
//
//private:
//    std::vector <Node> trie_;
//};
//
////#endif  // CPP_HSE_TRIE_H
