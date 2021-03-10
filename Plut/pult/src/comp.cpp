#include "main.hpp"

int main ( int argc, char **arg ) {
    string filename = arg[1];
    string writename= filename + "s";
    string data;
    string deffunc;
    string a;
    string b;
    string def;
    string impfile;
    string callfunc;
    
    vector<string> arglis;
    vector<string> impdata;
    vector<string> incfunc;
    

    ifstream wfs ( filename );
    ofstream ofs ( writename );

    int argliscount = 0;
    int iwcount = 0;
    int elj = 0;
    int liscount = 0;
    int find_c;
    
    if (wfs.fail()) {
        cerr << "Failed to open " << filename << endl;
        return -1;
    }

    while ( getline ( wfs , data) ) {
        data = regex_replace(data, regex( "    " ), "" );
        if ( data.substr( 0, 3 ) == "fn " ) {
            deffunc = split( split( data, "fn" )[1], "{" )[0];
            deffunc = regex_replace( deffunc, regex(" "), "");
            arglis = split( split( split(deffunc, "(")[1], ")")[0], ",");
            ofs << deffunc << ":" << endl;
            incfunc.resize(liscount+1);
            incfunc[liscount] = deffunc;
            for (size_t i = 0; i < arglis.size(); ++i) {
                if ( arglis.at(i) != "") {
                    ofs << "    pop " << arglis.at(i) << ";" << endl;
                }
            }
        }

        if ( data.substr ( 0, 7 ) == "return " ) {
            ofs << "    ret " << deffunc << ", " << split( data, "return " )[1] << endl;
            ofs << "    fin" << ";" << endl;
            impdata = import(split( callfunc, "(" )[0], impfile);
            for (size_t i2 = 0; i2 < impdata.size(); ++i2) {
                ofs << impdata.at(i2) << endl;
            }
            elj = 0;
        }

        if ( data.substr( 0, 4 ) == "let " ) {
            def = regex_replace( split( data, "let " )[1], regex(" "), "" );
            a = split( def, "=" )[0];
            b = split( def, "=" )[1];
            ofs << "    mov " << a << ", " << b << endl;
        }

        if ( data.find(");") != string::npos ) {
            callfunc = replace(data, " ");
            ofs << "    call " << callfunc << endl;
        }

        if ( data.substr( 0, 4 ) == "put " ) {
            ofs << "    msg " << split( data, "put " )[1] << endl;
        }

        if ( data.substr( 0, 7) == "import " ) {
            impfile = split( data, "import " )[1]; 
        }

        if ( data.substr( 0, 3 ) == "if " ) {
            data = regex_replace( regex_replace( split( data, "{" )[0] , regex( "if" ), "" ) , regex( " " ), "" );
            if ( data.find( "<" ) != string::npos ) {
                a = split( data, "<" )[0];
                b = split( data, "<")[1];
                ofs << "    ja " << a << ", " << b << ", L" << iwcount << ";" << endl;
                ofs << "    call L" << iwcount << "()" << ";" << endl;
            }
            
            if ( data.find( ">" ) != string::npos ) {
                a = split( data, ">" )[0];
                b = split( data, ">")[1];
                ofs << "    jne " << a << ", " << b << ", L" << iwcount << ";" << endl;
                ofs << "    call L" << iwcount << "()" << ";" << endl;
            }

            ofs << "    fin;" << endl;

            ofs << "L" << iwcount << "():" << endl;
            iwcount++;
        }

        if ( data.substr( 0, 6 ) == "while " ) {
            string data2 = replace( split( data, "{" )[0], " " );
            a = split( data2, "while" )[1];
            ofs << "    jmp " << "L" << iwcount << ", " << a << ";" << endl;
            ofs << "    fin;" << endl;
            ofs << "L" << iwcount << ", " << a << "():" << endl;
        }

        if ( data.find("=") != string::npos ) {
            string form = regex_replace( data, regex(" "), "" );
            string x = split( form, "=" )[0];

            if ( data.find("+") != string::npos ) {
                a = split( split( form, "=" )[1], "+" )[0];
                b = split( form, "+" )[1];
                ofs << "    add " << x << ", " << a << ", " << b <<endl;
            }

            if ( data.find("-") != string::npos ) {
                a = split( split( form, "=" )[1], "-" )[0];
                b = split( form, "-" )[1];
                ofs << "    sub " << x << ", " << a << ", " << b <<endl;
            }

            if ( data.find("*") != string::npos ) {
                a = split( split( form, "=" )[1], "*" )[0];
                b = split( form, "*" )[1];
                ofs << "    mul " << x << ", " << a << ", " << b <<endl;
            }

            if ( data.find("/") != string::npos ) {
                a = split( split( form, "=" )[1], "/" )[0];
                b = split( form, "/" )[1];
                ofs << "    div " << x << ", " << a << ", " << b <<endl;
            }
        }
        liscount++;
    }
    if ( find( incfunc, callfunc ) == 0 ) {
        for (size_t i2 = 0; i2 < inc( callfunc ).size(); ++i2) {
            ofs << inc( callfunc )[i2] << endl;
        }
    }

    wfs.close();
    ofs.close();

    return 0;
}

vector<string> inc ( string callfunc ) {
    vector<string> incfuncs;
    int inc_c = 0;
    vector<string> impdata = import(split( callfunc, "(" )[0], "include/dango.phs");
    for (size_t i2 = 0; i2 < impdata.size(); ++i2) {
        incfuncs.resize(inc_c+1);
        incfuncs[ inc_c ] = impdata.at(i2);
        inc_c++;
    }
    return incfuncs;
}