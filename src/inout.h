
//#ifndef CPP_HSE_INOUT_H
//#define CPP_HSE_INOUT_H

#pragma once

#include "cstdint"
#include <filesystem>
#include "filesystem"
#include <fstream>
#include "vector"
#include "array"

const int32_t FILENAME_END = 256;
const int32_t ONE_MORE_FILE = 257;
const int32_t ARCHIVE_END = 258;
const int32_t ID_ERROR = 111;
const size_t BIT = 1;
const size_t BYTE = 8;
const size_t SYMBOL = 9;
const size_t MAX_CHAR_NUMBER = 259;

using Mask = std::vector<bool>;

class Reader {
public:

    explicit Reader(std::filesystem::path file);

    template <size_t cnt>
    bool ReadSymb(int32_t& x) {
        while (sz_ < cnt) {
            if (file_.peek() == EOF) {
                return false;
            }
            int32_t symb = file_.get();
            buf_ = (buf_ << BYTE) + symb;
            sz_ += BYTE;
        }
        x = (buf_ & ((1 << sz_) - 1)) >> (sz_ - cnt);
        sz_ -= cnt;
        return true;
    }

    template <size_t cnt>
    int32_t ReadSymb() {
        int32_t res = 0;
        ReadSymb<cnt>(res);
        return res;
    }
private:
    size_t sz_ = 0;
    int32_t buf_ = 0;
    std::ifstream file_;
};

class Writer {
public:
    explicit Writer(std::filesystem::path name);

    ~Writer() = default;

    void Eat(const Mask& line);

    template <size_t cnt>
    void WriteSymbol(int32_t x) {
        buf_ = (buf_ << cnt) | x;
        sz_ += cnt;
        while (sz_ >= BYTE) {
            file_ << static_cast<unsigned char>((buf_ & ((1 << sz_) - 1)) >> (sz_ - 8));
            sz_ -= BYTE;
        }
    }

private:
    size_t sz_ = 0;
    int32_t buf_ = 0;
    std::ofstream file_;
};

void MakeCanonical(const std::vector<int32_t>& arr, const std::vector<size_t>& length,
                    std::vector<Mask>& canonical);

//#endif  // CPP_HSE_INOUT_H
