#ifndef WOBJPARSER_WOBJPARSER_H
#define WOBJPARSER_WOBJPARSER_H

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

#define PARSE_SUCCESS 0
#define BAD_VERTEX_STRING_ERROR 1
#define BAD_FACE_STRING_ERROR 2
#define BAD_SHAPE_ERROR 3

class WobjParser{
    public :
        WobjParser(const char *);
        ~WobjParser();
        int parse();

        std::vector<std::vector<float> > vertices;
        std::vector<unsigned int> faces;
    private:
        std::ifstream wobj_file;
};

#endif
