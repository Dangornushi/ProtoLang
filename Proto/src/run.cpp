#include"main.hpp"


int main( int argc, char **arg ) {

    string data, arg1 = arg[1];
    map<string, string> valls;
    map<string, string> funcs;

    ifstream run( arg1 );

    vector<string> funcvalls = import( "main", arg1 );
    VM( data, arg1, funcs, valls, funcvalls );
    return 0;
}

void VM( string data, string arg1, map<string, string>funcs, map<string, string>valls, vector<string> funcvalls ) {

    for (size_t i3 = 0; i3 < funcvalls.size(); ++i3) {
        string data2, funcdata, funcname, cont, cont2, order, word, word2 ;
        vector<string> args, args2;
        int callj = 0;
        int i = 0;
        int count = 0;
        ostringstream oss;
        int popcount = 0;
        string a, b;
        cont = replace( funcvalls[i3], "    " );
        cont2 = cont.substr( 0, 3 );

        if ( cont != "" ) {
            callj = 0;
            if ( cont2 == "msg" ) {
                word = "";
                word = split( cont, "msg " )[1];
                if ( word.find( "\"" ) != string::npos ) {
                    cout << split( replace( word, "\"" ), ";" )[0] << endl;
                }
                else {
                    cout << valls[split( word, ";" )[0]] << endl;
                }
            }

            if ( cont2 == "mov" ) {
                word = split( replace( cont, ";" ), ", " )[1];
                word2 = replace( split( cont, ", " )[0], " " );
                valls[ replace(word2, "mov") ] = word;
            }

            if ( cont2 == "add" ) {
                valls[split( split( cont, "," )[0], "add " )[1]] = calc( cont, valls, "add " );
            }

            if ( cont2 == "sub" ){
                valls[split( split( cont, "," )[0], "sub " )[1]] = calc( cont, valls, "sub " );
            }

            if ( cont2 == "mul" ) {
                valls[split( split( cont, "," )[0], "mul " )[1]] = calc( cont, valls, "mul " );
            }

            if ( cont2 == "div" ) {
                valls[split( split( cont, "," )[0], "div " )[1]] = calc( cont, valls, "div" );
            }
        
            if ( cont2 == "ja " && ifj(  cont, valls, "ja " ) == 0 ) {
                VM( data, arg1, funcs, valls, import ( split( split( split( cont, ";" )[0], "(" )[0], ", " )[2], arg1 ) );
            }
            if ( cont2 == "jne" && ifj(  cont, valls, "jne " ) == 0 ) {
                VM( data, arg1, funcs, valls, import ( split( split( split( cont, ";" )[0], "(" )[0], ", " )[2], arg1 ) );
            }

            if ( cont2 == "cal" ) {
                string cont3 = replace( cont, " " );
                vector<string> funcvalls = import( replace( split( cont3, "(" )[0], "call" ), arg1 );
                vector<string> args = split( split( split( cont3, "(" )[1], ")" )[0], "," );
                for (int ii = 0; ii < args.size(); ++ii) {
                    if ( keyfind( valls, args.at(ii) ) ) {
                        valls[to_string(ii)] = valls[args.at(ii) ];
                    }
                    else {
                        valls[to_string(ii)] = args.at(ii);
                    }
                }
                VM( data, arg1, funcs, valls, funcvalls );
            }

            if ( cont2 == "jmp" ) {
                b = split( replace( cont , ";"), ", " )[1];
                vector<string> funcvalls10 = import( split( split( cont, ";" )[0], "jmp " )[1], arg1 );
                while ( 1 ) {
                    VM( data, arg1, funcs, valls, funcvalls10 );
                    count ++;
                    if ( count > atoi( valls[b].c_str() ) ) {
                        break;
                    }
                }
            }

            if ( cont2 == "pop" ) {
                oss << popcount;
                args2 = split( replace( replace( cont, ";" ), "pop " ), "," );
                for (int iii = 0; iii < args2.size(); ++iii) {
                    valls[args2.at(iii)] = valls[to_string( popcount) ];
                    popcount++;
                }
            }
            i++;
        }
    }
}
