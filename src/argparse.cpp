#include "argparse.h"
#include "iostream"

const std::string ENCODER = "-c";
const std::string DECODER = "-d";
const std::string HELP = "-h";

ArgParse::ArgParse(int arg, char **argv) {
    //    std::cout << arg << std::endl;
    auto end = arg + argv;
    for (auto it = std::next(argv); it != end; it++) {
        if (**it == '-') {
//            std::cout << *it << std::endl;
            if (++it == end) {
                args_.clear();
                break;
            }
            --it;
            //            if (*std::next(it) == DECODER || )
            args_[*it] = *std::next(it);

            ++it;
        } else {
            free_args_.emplace_back(*it);
        }
    }
}

ArgParse::Status ArgParse::GetStatus() const {
    //    std::cout << (args_.find(ENCODER) != args_.end()) << std::endl;
    //    std::cout << (args_.find(DECODER) != args_.end()) << std::endl;
    //    std::cout << (args_.find(HELP) != args_.end()) << std::endl;

    if (args_.find(ENCODER) != args_.end() && static_cast<int32_t>(args_.size()) == 1) {
        return Status::ENCODER;
    }
    if (args_.find(DECODER) != args_.end() && static_cast<int32_t>(args_.size()) == 1) {
        return Status::DECODER;
    }
    if (args_.find(HELP) != args_.end() && static_cast<int32_t>(args_.size()) == 1) {
        return Status::HELP;
    }

    return Status::HELP;
}

std::filesystem::path ArgParse::GetArg(const std::string &s) const {
    return args_.at(s);
}

std::vector<std::filesystem::path> ArgParse::GetArgs() const {
    return free_args_;
}