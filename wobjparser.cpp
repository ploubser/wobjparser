#include "wobjparser.h"
#include <iomanip>

using namespace std;

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

      int fcounter = 0;

      while(pch){
        if(fcounter < 3){
          f_vec.push_back(atof(pch));
        } else {
          tf_vec.push_back(atof(pch));
          tf_vec.push_back(f_vec[2]);
          tf_vec.push_back(f_vec[1]);
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


int main(){
  const char * file = "cube.obj";

  WobjParser *parser = new WobjParser(file);
  int result = parser->parse();

  if(result > 0){
    cout << "Could not load file: " << file << endl;
  }

  cout << "Found vertices..." << endl;
  for(unsigned int i = 0; i < parser->vertices.size(); i++){
    for(int j = 0; j < 3; ++j){
      cout << setprecision(10) << parser->vertices[i][j] << " ";
    }
    cout << endl;
  }

  cout << "Found faces..." << endl;
  for(unsigned int i = 0; i < parser->faces.size(); i++){
    for(int j = 0; j < 3; ++j){
      cout << setprecision(10) << parser->faces[i][j] << " ";
    }
    cout << endl;
  }

  delete(parser);

  return 0;
}
