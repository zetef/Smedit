#include <iostream>
#include <fstream>
#include <string>
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
    // use "." for current folder. use ".." for previous folder. starting pos need no change
    dir = opendir(".");

    cout << "where to store the files from the editor" << endl << endl;

    //lists elements from dir
    while(pdir = readdir(dir)){
        if(i == 1)
            cout << pdir -> d_name << " (current directory)" << endl;
        if(i == 2)
            cout << pdir -> d_name << " (previous directory)" << endl;
        else if(i != 1)
            cout << pdir -> d_name << endl;
        i++;
    }
    closedir(dir);

    cout << endl << "chose directory" << endl;
        
    //get folder names with spaces
    getline(cin, name_dir);

    //make folder with name_dir
    mkdir(name_dir.c_str());
    edit();
}

