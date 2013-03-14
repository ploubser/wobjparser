#include "wobjparser.h"
#include <iomanip>

using namespace std;

int main(){
    const char * file = "test_object.obj";

    WobjParser *parser = new WobjParser(file);
    int result = parser->parse();

    if (result > 0){
        cout << "Could not load file: " << file << endl;
    }

    cout << "Found vertices..." << endl;

    for (unsigned int i = 0; i < parser->vertices.size(); i++){
        for (int j = 0; j < 3; ++j){
            cout << setprecision(10) << parser->vertices[i][j] << " ";
        }
        cout << endl;
    }

    cout << "Found faces..." << endl;

    for (unsigned int i = 0; i < parser->faces.size(); i++){
        cout << setprecision(10) << parser->faces[i] << " ";

        if ((i + 1) % 3 == 0){
            cout << endl;
        }
    }

    delete(parser);

    return 0;
}
