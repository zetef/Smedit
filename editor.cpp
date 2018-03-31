#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <windows.h>
#include <time.h>

using namespace std;

const WORD colors[] =
		{
		0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F,
		0xA1, 0xB2, 0xC3, 0xD4, 0xE5, 0xF6
		};
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
        //new file command
        if(n == "$stop")
            edit();
        //stop editing command
        if(n == "$stopf")
            return 0;
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
int main()
{
    //some color action
    srand(time(NULL));
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	//remember the original state
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo( hstdout, &csbi );
	//setting the actual color
	auto randColor = rand() % 10 + 2; //i did 10 + 2 so I don't get the first case where the text and bg in black
    SetConsoleTextAttribute(hstdout, randColor);

    cout << "where to store the files from the editor" << endl << endl;

    // use "." for current folder. use ".." for previous folder. starting pos need no change
    dir = opendir(".");

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

    //restore normal color
    SetConsoleTextAttribute(hstdout, csbi.wAttributes);

    //get folder names with spaces
    getline(cin, name_dir);

    //make folder with name_dir
    mkdir(name_dir.c_str());
    edit();
}
