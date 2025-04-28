#include "trie.h"

Node::Node(int32_t c, size_t cnt, Node* left, Node* right) : left_(left), right_(right), symb_(c), col_(cnt) {
}

Node::~Node() {
    delete left_;
    delete right_;
}

Node*& Node::GetSon(bool x) {
    if (x) {
        return right_;
    } else {
        return left_;
    }
}

bool Node::IsTerm() const {
    return left_ == nullptr && right_ == nullptr;
}

int32_t Node::GetSymb() const {
    return symb_;
}

size_t Node::GetCol() const {
    return col_;
}

void Node::GetLength(int ln, std::vector<int32_t>& order, std::vector<size_t>& length) {
    if (IsTerm()) {
        order.emplace_back(GetSymb());
        length[GetSymb()] = ln;
        return;
    }

    for (int i = 0; i < 2; i++) {
        if (GetSon(i) != nullptr) {
            GetSon(i)->GetLength(ln + 1, order, length);
        }
    }
}


void Node::Add(int32_t c, const std::vector<bool>& code) {
    Node* h = this;
    for (bool x : code) {
        Node*& son = h->GetSon(x);
        if (son == nullptr) {
            son = new Node();
        }
        h = son;
    }
    h->symb_ = c;
}

bool Check(Node* a, Node* b) {
    return std::make_pair(a->GetCol(), a->GetSymb()) < std::make_pair(b->GetCol(), b->GetSymb());
}

bool Node::Comp::operator()(Node* a, Node* b) const {
    return std::make_pair(a->GetCol(), a->GetSymb()) < std::make_pair(b->GetCol(), b->GetSymb());
}
