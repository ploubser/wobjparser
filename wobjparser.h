#ifndef H_WOBJPARSER
#define H_WOBJPARSER

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdlib>

class WobjParser{
  public :
    WobjParser(const char *);
    ~WobjParser();
    int parse();
    std::vector<std::vector<float> > vertices;
    std::vector<std::vector<int> > faces;

  private:
    std::ifstream wobj_file;
};

#endif
