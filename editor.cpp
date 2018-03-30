#include <iostream>
#include <fstream>
#include <string>
//#include <conio.h>
#include <dirent.h>

using namespace std;

int i(1);
DIR *dir;
dirent *pdir;
fstream editor ("editor.io");
string name, ext, n, name_dir;

int edit(){
    editor >> name >> ext;
    name += ext;
    string path = name_dir + "\\" + name;
    ofstream out(path);
    while(getline(editor, n)){
        if(n == "$stop")
            edit();
        if(n == "$stopf")
            return 0;
        while(n.length() == 0)
            getline(editor, n);
        if(!editor.eof())
            out << n << " ";
        out << endl;
    }
    editor.close();
}

int main()
{
    // use "." for current folder. use ".." for previous folder
    dir = opendir(".");

    //lists elements from dir
    while(pdir = readdir(dir)){
        cout << i << " " << pdir -> d_name << endl;
        i++;
    }
    closedir(dir);

    //get folder names with spaces
    getline(cin, name_dir);

    //make folder with name_dir
    mkdir(name_dir.c_str());
    edit();
}

