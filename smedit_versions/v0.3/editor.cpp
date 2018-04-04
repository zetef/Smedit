#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <sys/stat.h>

using namespace std;

int i(1), inputTimes;
DIR *dir;
HANDLE hstdout;
dirent *pdir;
fstream editor ("editor.io");
string name, ext, n, name_dir, name_ndir, name_ddir, location;
bool clr_screen = false, changed_c = false;

int isDirectoryOrFile(string name){
    struct stat st_buf;
    int status = stat (name.c_str(), &st_buf);

    if (status != 0) {
        printf ("error, errno = &#37;d\n", errno);
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

void openFolder(string folder_name){
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

void listDirectory(){
    // use "." for current folder. use ".." for previous folder. starting pos need no change
    dir = opendir(".");

    //lists elements from dir
    while((pdir = readdir(dir))){
        if(i == 1)
            cout << pdir -> d_name << " (current directory)" << endl;
        if(i == 2)
            cout << pdir -> d_name << " (previous directory)" << endl;
        else if(i != 1)
            cout << pdir -> d_name << endl;
        i++;
    }
    closedir(dir);
}

int main()
{
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
        listDirectory();
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

    //special commands
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
            openFolder(name_ndir);

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
            cout << "green\nblue\nred\npink\nyellow\nwhite\n";
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

            //a directory
            if(isDirectoryOrFile(name_ddir)){

                //for now just full path is accepted
                string path_del = "rmdir /s /q ";
                path_del += '\"';
                path_del += name_ddir;
                system(path_del.c_str());
                path_del += '\"';
                
            //a file
            }else if(isDirectoryOrFile(name_ddir) == 0){

                //full path is needed
                string file_del = "del ";
                file_del += '\"';
                file_del += name_ddir;
                file_del += '\"';
                system(file_del.c_str());
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
    openFolder(name_dir);

    //the editor
    edit();
}

//functions that need main()
void unknownCommand(){
    cout << "unknown command\navailable commands are:\n$od - open directory\n$cd - create directory\n$cls - clear screen\n$cl - current location\n$sc - set color\n$rc - reset color\n$ex - exit\n$dd - delete directory\n";
    system("pause");
    system("cls");
    main();
}

int edit(){
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
