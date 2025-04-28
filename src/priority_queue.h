
//#ifndef CPP_HSE_PRIORITY_QUEUE_H
//#define CPP_HSE_PRIORITY_QUEUE_H
#pragma once


#include "vector"
#include "algorithm"
#include "iostream"
#include "cstdint"
#include "trie.h"

class ListIndexOutOfRange : public std::runtime_error {
public:
    ListIndexOutOfRange() : std::runtime_error("ListIndexOutOfRange") {
    }
};

//template <typename T>

class PriorityQueue {
public:
    PriorityQueue() {
        heap_.resize(1);
    }

    ~ PriorityQueue() {
        while (!Empty()) {
            Pop();
        }
    }

    void Insert(Node* elem) {
        heap_.emplace_back(elem);
        int32_t i = Size();
        while (i > 0) {
            int32_t p = i >> 1;
            if (p > 0 && Check(heap_[i], heap_[p])) {
                std::swap(heap_[p], heap_[i]);
                i = p;
            } else {
                i = 0;
                break;
            }
        }
    }

    int32_t Size() {
        return static_cast<int32_t>(heap_.size() - 1);
    }

    bool Empty() {
        return Size() == 0;
    }

    Node* Top() {
        if (!Empty()) {
            return heap_[1];
        } else {
            throw ListIndexOutOfRange();
        }
    }

    void Pop() {
        if (Empty()) {
            return;
        }
        int32_t i = 1;
        std::swap(heap_[1], heap_.back());
        heap_.pop_back();
        int32_t sz = Size() + 1;
        while (i < sz) {
            auto left = i << 1;
            auto right = (i << 1) + 1;
            if (right < sz && Check(heap_[right], heap_[left])) {
                ++left;
            }
            if (left < sz && Check(heap_[left], heap_[i])) {
                std::swap(heap_[left], heap_[i]);
                i = left;
            } else {
                break;
            }
        }
    }
private:
    std::vector<Node*> heap_;
};

//#endif  // CPP_HSE_PRIORITY_QUEUE_H
