#include "wobjparser.h"

/*******************************************************************
 * Constructor
 * ****************************************************************/
WobjParser::WobjParser(const char *filename){
    wobj_file.open(filename);
}

/*******************************************************************
 * Destructor
 * ****************************************************************/
WobjParser::~WobjParser(){
    wobj_file.close();
}

/*******************************************************************
 * Parse obj file
 * ****************************************************************/
int WobjParser::parse(){
    if (!wobj_file.is_open()){
        return FILE_READ_ERROR;
    }

    char in[256];

    while (!wobj_file.eof()){
        wobj_file.getline(in, 256);

        if (in[0] == 'v'){
            std::vector<float> v_vec;

            char *pch;
            pch = strtok(in, " v");

            if (!pch){
                return BAD_VERTEX_STRING_ERROR;
            }

            for (int i = 0; i < 3; ++i){
                v_vec.push_back(atof(pch));
                pch = strtok (NULL, " ");
            }

            vertices.push_back(v_vec);

        } else if (in[0] == 'f'){

            char *pch;
            pch = strtok(in, " f");

            if (!pch){
                return BAD_FACE_STRING_ERROR;
            }

            int fcounter = 0;

            while (pch){
                if (fcounter < 3){
                    faces.push_back(atof(pch));
                } else if (fcounter == 3){
                    int j = faces.size();
                    faces.push_back(faces[j - 1]);
                    faces.push_back(atof(pch));
                    faces.push_back(faces[j - 3]);

                } else{
                    //Not a triangle or quad
                    return BAD_SHAPE_ERROR;
                }

                pch = strtok(NULL, " ");
                ++fcounter;
            }
        }
    }

    return PARSE_SUCCESS;
}
