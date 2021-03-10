#include "main.hpp"

int main() {
    string hoge = "hoge", data;
    map <string, string> map1;
    ifstream ifs ( "test.txt");

    while ( getline( ifs, data ) ) {
        map1[ hoge ] += data;
    }
    cout << map1[hoge] << endl;
}
