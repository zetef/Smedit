#include <conio.h>
#include <dirent.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <sys/stat.h>
#include <stdexcept>
#include <string>
#include <time.h>
#include <windows.h>

//for later use
//#define KB_UP 72
//#define KB_DOWN 80

using namespace std;

DIR *dir, *ndir;
HANDLE hstdout;
dirent *pdir, *npdir;
ifstream editor ("editor.io");
string name, ext, n, name_dir, name_ndir, name_ddir, location, decision;
string commands[ ] = {"$op", "$cd", "$dd", "$cl", "$sc", "$rc", "$cls", "$ex"};
short comds_size(8), index(0);
int i(1), KB_code(0);
bool clr_screen = false, changed_c = false, title_set = false;

struct console{

    //creating the console
    console(unsigned width, unsigned height)
    {
        SMALL_RECT  r;
        COORD       c;
        hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
        if (!GetConsoleScreenBufferInfo( hstdout, &csbi ))
          throw runtime_error( "You must be attached to a human." );

        //size
        r.Left   = 0;
        r.Top    = 0;
        r.Right  = width - 1;
        r.Bottom = height - 1;
        SetConsoleWindowInfo( hstdout, TRUE, &r );

        c.X = width;
        c.Y = height;
        SetConsoleScreenBufferSize( hstdout, c );
        }

    ~console()
    {
    SetConsoleTextAttribute(    hstdout,        csbi.wAttributes );
    SetConsoleScreenBufferSize( hstdout,        csbi.dwSize      );
    SetConsoleWindowInfo(       hstdout, TRUE, &csbi.srWindow    );
    }

    HANDLE                     hstdout;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
};

string convert_to_string(double num){
    ostringstream conv;
    conv << num;
    return conv.str();
}

double round(double num){
    double d = num * 100.0f;
    int i = d + 0.5;
    d = (float)i / 100.0f;
    return d;
}

string convert_size(size_t sz){
    static const char *SIZES[] = {"b", "kb", "mb", "gb"};
    int div = 0;
    size_t rem = 0;

    //it decides what size it is
    while(sz >= 1024 && div < (sizeof SIZES / sizeof *SIZES)){
        rem = sz % 1024;
        div++;
        sz /= 1024;
    }

    double size_d = (float)sz + (float)rem / 1024.0;
    string result = convert_to_string(round(size_d)) + " " + SIZES[div];
    return result;
}

long file_size(const string& file_name){
    struct stat buf;
    if(stat(file_name.c_str(), &buf) != 0)
        return 0;
    return buf.st_size;
}

string get_file_size(string path){
    size_t sz = file_size((const char *)path.c_str());
    return convert_size(sz);
}

void size_position(dirent *file){
    short name_len = file -> d_namlen;
    short space_len = 35;
    for(short i = name_len; i < space_len; i++){
        cout << '-';
    }
    cout << get_file_size(file -> d_name) << endl;
}

int is_directory_or_file(string name){
    struct stat st_buf;
    int status = stat (name.c_str(), &st_buf);

    if (status != 0) {
        printf ("error = &#37;d\n");
        return 2;
    }

    //file
    if (S_ISREG (st_buf.st_mode)) {
        return 0;
    }

    //directory
    if (S_ISDIR (st_buf.st_mode)) {
        return 1;
    }
}

void open_folder(string folder_name){
    TCHAR npath[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, npath);
    string start = "start explorer "; //EXPLORER IS NECESSARY SO YOU DON'T WASTE ONE HOUR
    string path;
    path += npath;
    path += "\\";

    //name of the folder to open
    for(unsigned int i = 0; i < folder_name.length(); i++) //in case it has spaces
        path += folder_name[i];

    path += "\\";
    string n_path = path;
    start += n_path;
    system(start.c_str()); //open directory
}

void list_directory(){
    //when used multiple times
    i = 1;

    cout << char(201) << "                                    size\n";

    // use "." for current folder. use ".." for previous folder. starting pos need no change
    dir = opendir(".");

    if(!title_set)
        //set name to current location
        SetConsoleTitle(dir -> dd_name);

    //lists elements from dir
    while((pdir = readdir(dir))){
        //converting the name from pointer into a string
        stringstream ss;
        ss << pdir -> d_name;
        string name = ss.str();

        if(i == 1)
            cout << char(204) << " " << pdir -> d_name << " (current directory)" << endl;
        if(i == 2)
            cout << char(204) << " " << pdir -> d_name << " (previous directory)" << endl;
        else if(i != 1){
            cout << char(204) << " " << pdir -> d_name;

            //is file
            if(is_directory_or_file(name) == 0)
                size_position(pdir);

            //is directory
            else{
                cout << endl;
            }
        }
        i++;
    }
    cout << char(200);
    closedir(dir);
}

int main()
{
    //SetConsoleTitle("");

    //create console
    console con(50, 50);

    //for the ascii table
    //for(int i = 0; i < 256; i++)
        //cout << i << char(i) << " ";

    //function that needs main();
    void unknownCommand();
    void edit();

    //if set color don't randomize the color
    if(!changed_c){
        //some color action
        srand(time(NULL));
        hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
        //remember the original state
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo( hstdout, &csbi );
        //setting the actual color
        auto randColor = rand() % 5 + 10; //with black bg
        SetConsoleTextAttribute(hstdout, randColor);
    }

    //check if it should list the elements
    if(!clr_screen)
        list_directory();
    else
        clr_screen = false;
    cout << "\n>";

    //get folder names with spaces
    getline(cin, name_dir);

    //if input is empty
    if(name_dir.empty()){
        cout << "please enter command (starts with $) or valid name \n";
        system("pause");
        system("cls");
        main();
    }

    //not so special commands
    if(name_dir[0] == '$'){
        //open directory                                                    $op
        if(name_dir[1] == 'o' && name_dir[2] == 'd'){
            cout << "location: ";
            getline(cin, location); //location to open. works ".." and '.'
            SetCurrentDirectory(location.c_str()); // sets current directory to location
            system("cls");
            main();
        }else

        //create directory                                                  $cd
        if(name_dir[1] == 'c' && name_dir[2] == 'd'){
            //creating the actual directory
            cout << "new directory name: ";
            getline(cin, name_ndir); //new folder name
            cout << "location: ";
            getline(cin, location); //location
            SetCurrentDirectory(location.c_str()); //set location to create directory
            mkdir(name_ndir.c_str()); //create the directory

            //open the created directory
            open_folder(name_ndir);

            system("cls");
            main();
        }else

        //clear screen                                                      $cls
        if(name_dir[1] == 'c' && name_dir[2] == 'l' && name_dir[3] == 's'){
            clr_screen = true;
            system("cls");
            main();
        }else

        //get current location                                              $cl
        if(name_dir[1] == 'c' && name_dir[2] == 'l'){
            TCHAR npath[MAX_PATH]; //where to store the location
            GetCurrentDirectory(MAX_PATH, npath); //stored the location
            wcout << npath << '\n'; //couts the location
            system("pause");
            system("cls");
            main();
        }else

        //seting color manually                                             $sc
        if(name_dir[1] == 's' && name_dir[2] == 'c'){
            string color;
            cout << "green\nblue\nred\npink\nyellow\nwhite\n>";
            getline(cin, color);
            if(color == "green"){
                SetConsoleTextAttribute(hstdout, 10);
                changed_c = true;
                system("cls");
                main();
            }
            if(color == "blue"){
                SetConsoleTextAttribute(hstdout, 11);
                changed_c = true;
                system("cls");
                main();
            }
            if(color == "red"){
                SetConsoleTextAttribute(hstdout, 12);
                changed_c = true;
                system("cls");
                main();
            }
            if(color == "pink"){
                SetConsoleTextAttribute(hstdout, 13);
                changed_c = true;
                system("cls");
                main();
            }
            if(color == "yellow"){
                SetConsoleTextAttribute(hstdout, 14);
                changed_c = true;
                system("cls");
                main();
            }
            if(color == "white"){
                SetConsoleTextAttribute(hstdout, 15);
                changed_c = true;
                system("cls");
                main();
            }else
                cout << "choose a valid color! \n";
                system("pause");
                system("cls");
                main();
        }else

        //reset color                                                       $rc
        if(name_dir[1] == 'r' && name_dir[2] == 'c'){
            changed_c = false;
            system("cls");
            main();
        }else

        //exit the program                                                  $ex
        if(name_dir[1] == 'e' && name_dir[2] == 'x'){
            return 0;
        }else

        //delete directory (auto-checks if file and if so it deletes it)    $dd
        if(name_dir[1] == 'd' && name_dir[2] == 'd'){
            cout << "location: ";
            getline(cin, name_ddir);
            cout << "are you sure? y/n\n";
            getline(cin, decision);

            if(decision == "y" || decision == "Y"){
                //a directory
                if(is_directory_or_file(name_ddir)){

                //for now just full path is accepted
                string path_del = "rmdir /s /q ";
                path_del += '\"';
                path_del += name_ddir;
                system(path_del.c_str());
                path_del += '\"';

                //a file
                }else if(is_directory_or_file(name_ddir) == 0){

                    //full path is needed
                    string file_del = "del ";
                    file_del += '\"';
                    file_del += name_ddir;
                    file_del += '\"';
                    system(file_del.c_str());
                }
                system("cls");
                main();
            }else{
                system("cls");
                main();
            }
        }else

        //set title                                                         $st
        if(name_dir[1] == 's' && name_dir[2] == 't'){
            title_set = true;

            string title;
            cout << "name of title: ";

            //get title
            getline(cin, title);

            //set title
            SetConsoleTitle(title.c_str());

            //reset
            system("cls");
            main();
        }else

        //reset title                                                       $rs
        if(name_dir[1] == 'r' && name_dir[2] == 't'){
            if(!title_set){
                cout << "set title first!\n";
                system("pause");
                system("cls");
                main();
            }else{
                title_set = false;
                SetConsoleTitle(dir -> dd_name);
                system("cls");
                main();
            }
        }else
            unknownCommand();


        //just to make sure the rest of the program doesn't run. not really needed
        return 0;
    }

    //restore normal color
    //SetConsoleTextAttribute(hstdout, csbi.wAttributes);

    //make folder with name_dir
    mkdir(name_dir.c_str());

    //open the folder
    open_folder(name_dir);

    //the editor
    edit();
}

//functions that need main()
void unknownCommand(){
    cout << "unknown command\navailable commands are:\n$od - open directory\n$cd - create directory\n$cls - clear screen\n$cl - current location\n$sc - set color\n$rc - reset color\n$ex - exit\n$dd - delete directory\n$st - set title\n$rt - reset title";
    system("pause");
    system("cls");
    main();
}

int edit(){

    //the editor
    editor >> name >> ext;
    name += ext;
    string path = name_dir + "\\" + name;
    ofstream out(path);
    //reads the file
    while(getline(editor, n)){
        //new file command
        if(n == "$stop")
            edit();
        //stop editing command
        if(n == "$stopf"){
            return 0;
        }
        //read more characters
        while(n.length() == 0)
            getline(editor, n);
        //comment
        if(n[0] == '#' ||
            //in case you comment after an extension declaration
            (n[0] == ' ' && n[1] == '#'))
            continue;
        //write the string
        if(!editor.eof())
            out << n << " ";
        out << endl;
    }
    editor.close();
}

