//#ifndef CPP_HSE_ARGPARSE_H
//#define CPP_HSE_ARGPARSE_H

#pragma once


#include "string"
#include "map"
#include <filesystem>
#include "vector"

class ArgParse {
public:
    enum class Status {
        ENCODER,
        DECODER,
        HELP,
    };

    ArgParse(int arg, char** argv);

    [[nodiscard]] Status GetStatus() const;

    [[nodiscard]] std::filesystem::path GetArg(const std::string& s) const;
    [[nodiscard]] std::vector<std::filesystem::path> GetArgs() const;
private:
    std::map<std::string, std::filesystem::path> args_;
    std::vector<std::filesystem::path> free_args_;
};

//#endif
