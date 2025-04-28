#include "argparse.h"
#include "encoder.h"
#include "decoder.h"
#include "help.h"
#include <iostream>

const std::string ENCODER = "-c";
const std::string DECODER = "-d";

int main(int argc, char** argv) {
    auto parse = ArgParse(argc, argv);

    if (parse.GetStatus() == ArgParse::Status::ENCODER) {
        Encoder(parse.GetArg(ENCODER), parse.GetArgs());
    } else if (parse.GetStatus() == ArgParse::Status::DECODER) {
        Decoder(parse.GetArg(DECODER));
    } else {
        Help();
    }
}