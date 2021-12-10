//
// Created by michael on 10/12/2021.
//

#include <vector>
#include <fstream>
#include <iterator>


#ifndef PROJECT_IO_H
#define PROJECT_IO_H
namespace io{
//    void write_vector(const std::vector<int> &v, const std::string& path){
//        std::ofstream output_file(path);
//        std::ostream_iterator<std::string> output_iterator(output_file, "\n");
//        std::copy(v.begin(), v.end(), output_iterator);
//    }
    void write_map(const std::map<int, std::vector<int>> Adj, std::string path){
        ofstream stream(path);
        for(auto &kv: Adj){
            stream << kv.first << "---->";
            std::ostream_iterator<int> output_iterator(stream, " ");
            std::copy(Adj.at(kv.first).begin(), Adj.at(kv.first).end(), output_iterator);
            stream << "\n";
            }
        }

    }

#endif //PROJECT_IO_H
