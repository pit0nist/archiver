#include "inout.h"

const int32_t ZERO = 0;

Reader::Reader(std::filesystem::path file) : file_(std::move(file)){
}

void Writer::Eat(const Mask &line) {
    for (auto x : line) {
        WriteSymbol<1>(x);
    }
}
Writer::Writer(std::filesystem::path file) : file_(std::move(file)){
}

//Writer::~Writer() {
//    if (sz_ != 0) {
//        file_ << static_cast<unsigned char>((buf_ & ((1 << sz_) - 1)) << (8 - sz_));
//    }
//}

void MakeCanonical(const std::vector<int32_t>& arr, const std::vector<size_t> & length,
                   std::vector<Mask>& canonical) {
    canonical[arr.front()].assign(length[arr.front()], false);
    for (auto it = std::next(arr.begin()); it != arr.end(); ++it) {
        canonical[*it] = canonical[*std::prev(it)];
        auto last_zero = canonical[*it].rbegin();
        while (*last_zero != ZERO) {
            last_zero++;
        }
        *last_zero = true;
        std::fill(canonical[*it].rbegin(), last_zero, false);
        canonical[*it].resize(length[*it], false);
    }
}

