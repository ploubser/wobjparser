#ifndef WOBJPARSER_WOBJPARSER_H
#define WOBJPARSER_WOBJPARSER_H

#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

const char PARSE_SUCCESS = 0;
const char FILE_READ_ERROR = 1;
const char BAD_VERTEX_STRING_ERROR = 2;
const char BAD_FACE_STRING_ERROR = 3;
const char BAD_SHAPE_ERROR = 4;

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
