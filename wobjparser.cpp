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
 *
 * @return
 * 0 = sucess
 * 1 = failure
 * ****************************************************************/
int WobjParser::parse(){
  if(! wobj_file.is_open()){
    return 1;
  }

  char in[256];

  while(!wobj_file.eof()){
    wobj_file.getline(in, 256);

    if(in[0] == 'v'){
      std::vector<float> v_vec;

      char *pch;
      pch = strtok(in, " v");

      if(!pch){
        // Found a bad vertex string
        return 1;
      }

      for(int i = 0; i < 3; ++i){
        v_vec.push_back(atof(pch));
        pch = strtok (NULL, " ");
      }

      vertices.push_back(v_vec);

    } else if(in[0] == 'f'){
      std::vector<int> f_vec;
      std::vector<int> tf_vec;

      char *pch;
      pch = strtok(in, " f");

      if(!pch){
        // Found a bad face string
        return 1;
      }

      int fcounter = 0;

      while(pch){
        if(fcounter < 3){
          f_vec.push_back(atof(pch));
        } else if(fcounter == 3){
          tf_vec.push_back(atof(pch));
          tf_vec.push_back(f_vec[2]);
          tf_vec.push_back(f_vec[1]);
        }else{
          //Not a triangle or quad
          return 0;
        }

        pch = strtok (NULL, " ");
        ++fcounter;
      }

      faces.push_back(f_vec);
      if(f_vec.size() > 0){
        faces.push_back(tf_vec);
      }
    }
  }

  return 0;
}
