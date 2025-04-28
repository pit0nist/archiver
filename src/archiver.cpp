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
//    try {
//        switch (parse.GetStatus()) {
//            case ArgParse::Status::ENCODER:
//                break;
//            case ArgParse::Status::DECODER:
//                break;
//            case ArgParse::Status::HELP:
//                Help();
//                break;
//        }
//    } catch (...) {
//        throw 111;
//    }
}

////void BuildTrie(std::map<unsigned char, int32_t>& number, trie& trie, PriorityQueue <Node>& pq) {
////    int num = 0;
////    for (auto & [symb, count] : number) {
////        Node elem = Node(num, symb, count);
////        trie.Add(elem);
////        pq.Insert(elem);
////    }
////    while (pq.Size() > 1) {
////        auto n1 = pq.Top();
////        pq.Pop();
////        auto n2 = pq.Top();
////        //        std::cout << n1.prior << ' ' << n2.prior << std::endl;
////        pq.Pop();
////        auto n3 = trie.Add(n1, n2);
////        pq.Insert(n3);
////    }
////}
//bool Cmp(const std::pair<std::string, unsigned char>& a, const std::pair<std::string, unsigned char>& b) {
//    return std::make_tuple(static_cast<int>(a.first.size()), a.second) <
//           std::make_tuple(static_cast<int>(b.first.size()), b.second);
//}
////
////void MakeCanonical(trie& trie, int32_t head, std::vector <std::pair<std::string, unsigned char> >& canonical) {
////    std::string s;
////    trie.GetCanonical(head, s, canonical);
////    std::sort(canonical.begin(), canonical.end(), Cmp);
////
////}
//
//void CoderFile(std::string file_name, std::string archieve_name) {
//    std::map<unsigned char, int32_t> number;
//    for (auto & symb : file_name) {
//        number[symb]++;
//    }
//    number[static_cast<unsigned char>(FILENAME_END)]++;
//    number[static_cast<unsigned char>(ONE_MORE_FILE)]++;
//    number[static_cast<unsigned char>(ARCHIVE_END)]++;
//    try {
//        std::ifstream in;
//        in.open(file_name, std::ios::in | std::ios::binary);
//        char symb = 0;
//        while (in.read(&symb, 1)) {
//            number[static_cast<unsigned char>(symb)]++;
//        }
//        in.close();
//    } catch (...){
//        throw ID_ERROR;
//    }
////    trie trie;
////    PriorityQueue <Node> pq;
////    BuildTrie(number, trie, pq);
////    std::vector <std::pair<std::string, unsigned char> > canonical;
//}
//
//
//void Coder(std::vector<std::string> & request) {
//
//    for (int32_t i = 3; i < static_cast<int32_t>(request.size()); i++) {
//
//
//
//    }
//}


//    while (true) {
//        std::string req;
//        getline(std::cin, req);
//        std::vector <std::string> request;
//        Split(req, request);
//        if (request[0] != COMMAND) {
//            std::cout << "Incorrect request\n";
//            continue;
//        } else if (request[1] == CODER) {
//
//        } else if (request[1] == DECODER) {
//
//        } else if (request[1] == HEAD) {
//
//        } else {
//            std::cout << "Incorrect request\n";
//            continue;
//        }
//    }





//    PriorityQueue <Node> h;
//    trie trie;
//    Node c = Node(0, 2, 'c');
//    Node b = Node(1, 6, 'b');
//    Node e = Node(2, 7, 'e');
//    Node _ = Node(3, 10, '_');
//    Node d = Node(4, 10, 'd');
//    Node a = Node(5, 11, 'a');
////    return 0;
//    trie.Add(c);
//    trie.Add(b);
//    trie.Add(e);
//    trie.Add(_);
//    trie.Add(d);
//    trie.Add(a);
//    h.Insert(c);
//    h.Insert(b);
//    h.Insert(e);
//    h.Insert(_);
//    h.Insert(d);
//    h.Insert(a);
//
//
//    while (h.Size() > 1) {
//        auto n1 = h.Top();
//        h.Pop();
//        auto n2 = h.Top();
//        std::cout << n1.prior << ' ' << n2.prior << std::endl;
//        h.Pop();
//        auto n3 = trie.Add(n1, n2);
//        h.Insert(n3);
////        if (h.Size() == 4) {
////            while (!h.Empty()) {
////                auto n = h.Top();
////                h.Pop();
////                std::cout << n.prior << ' ' << n.min_elem << std::endl;
////            }
////        }
//
//    }
//    trie.Print(h.Top().num, "");
//    exit(0);
//
////    std::vector <Node> = {Node()};
//}