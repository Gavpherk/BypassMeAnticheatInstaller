// ConsoleApplication10.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS
#define ARRAY_SIZE 1024
#include <iostream>
#include <filesystem>
#include <shlobj_core.h>
#include <windows.h>
#include <fstream>
#include <shtypes.h>
#include <thread>
#include <Windows.h>
#include <string.h>
#include <vector>
#include "stdio.h"
#include "direct.h"
#include <sys/stat.h>
#include <Psapi.h>
#include <TlHelp32.h>
#include <comdef.h>
#include <tchar.h>
#include <cstdlib>
#include "md5.h"
#include "sha1.h"
#include "obfuscate.h"
#include "chrono"

using namespace std;
string convertIntArrayToString(int arr[], int n);
string convertCharArrayToString(char* a, int size);
bool DevMode = false;

int main() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    byte IsBannedByte = 0;
    if (DevMode == false) {
        ifstream IsBanned; // Initilize ifstream object for reading 
        string path = getenv(AY_OBFUSCATE("appdata")); // Get Local Environment Variable %APPDATA%
        path += AY_OBFUSCATE("\\Robots.txt"); //Appends the variable with \Banned.txt 
        IsBanned.open(path.c_str()); // Open Banned.txt
        IsBanned >> IsBannedByte;
        if (IsBannedByte == 1) {
            SetConsoleTextAttribute(h, 4);
            cerr << "This program was only designed to be ran once. You are effectively banned from using it again." << endl;
            SetConsoleTextAttribute(h, 15);
            cerr << AY_OBFUSCATE("If you have an integrity violation and need to get a new BypassMe.exe, replace your current one with the one I supplied.") << endl;
            cerr << AY_OBFUSCATE("If you have found and or misplaced any AntiCheat Internal Files, restore them from your recycling bin.") << endl;
            cerr << AY_OBFUSCATE("This Installation is a one time process.") << endl;
            SetConsoleTextAttribute(h, 7);
            system("pause");
            return 1;
        }
        IsBanned.close();
    }
    string path = getenv(AY_OBFUSCATE("appdata"));
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    int num = 1024;
    char buffer3[1024]; // Get Current Working Dir
    _getcwd(buffer3, num); // store working dir into char array buffer
    convertCharArrayToString(buffer3, (num)); // convert working dir char to a string

    if (_getcwd(buffer3, num) == NULL) // Checks to see if we got the Current Working Dir
    {
        SetConsoleTextAttribute(h, 4);
        cerr << AY_OBFUSCATE("You broke the goddamn GETCWD() System! Go To Jail For 1 Turn") << endl;
        SetConsoleTextAttribute(h, 7);
        system("pause");
        return 1;
    }
    string TargetExecutable = buffer3;
    SetConsoleTextAttribute(h, 15);
    TargetExecutable += AY_OBFUSCATE("\\BypassMe.exe");
    cout << AY_OBFUSCATE("Attempting to Install HotPockets AntiCheat to: ") << TargetExecutable << endl;
    SetConsoleTextAttribute(h, 7);

    ifstream Binary; // initalize ifstream object for reading 
    Binary.open(TargetExecutable, ifstream::binary); // Open Executable, and prepare to read it in a Binary format.
    if (Binary.fail()) //Checks to See if we could get a handle to the executable or not
    {
        SetConsoleTextAttribute(h, 4);
        string s(AY_OBFUSCATE("Sorry bud, but we can't find BypassMe.exe. Make sure you keep this program in the same folder as the Game."));
        cout << s << endl;
        SetConsoleTextAttribute(h, 7);
        // If you think this isnt cheating you are a disgrace to people who do real Reverse Engineering
        system("pause");
        return 1;
    }
    Binary.seekg(0, Binary.end); // get length of file
    int length = Binary.tellg();
    Binary.seekg(0, Binary.beg);
    char* buffer = new char[length]; // store length into Char Array

    if (DevMode == true) {
        SetConsoleTextAttribute(h, 3);
        cout << AY_OBFUSCATE("Reading ") << length << AY_OBFUSCATE(" characters of Binary Data ") << endl;
        SetConsoleTextAttribute(h, 7);
    } //debug

    Binary.read(buffer, length); // read data as a block

    if (Binary) // if read was succesful
    {
        if (DevMode == true) {
            SetConsoleTextAttribute(h, 3);
            cout << AY_OBFUSCATE("Buffer Generated") << endl;
            SetConsoleTextAttribute(h, 7);
        }
    } //debug
    else {
        SetConsoleTextAttribute(h, 4);
        cerr << AY_OBFUSCATE("We found BypassMe.exe a second ago, but its gone now. What have you done? ") << endl; // literally
        system("pause");
        SetConsoleTextAttribute(h, 7);
    }

    Binary.close(); // close the executable - free up memory
    SHA1 HashSHA1; // Create SHA1 Hash Object
    MD5 HashMD5; // Create MD5 Hash Object
    string InstanceHashMD5 = HashMD5(buffer, length); // store hash into string
    string InstanceHashSHA1 = HashSHA1(buffer, length); //store hash into string
    SetConsoleTextAttribute(h, 15);
    cout << AY_OBFUSCATE("Hashes Generated") << endl;
    SetConsoleTextAttribute(h, 7);
    if (DevMode == true) {
        SetConsoleTextAttribute(h, 3);
        std::cout << AY_OBFUSCATE("Executables SHA1 Hash: ") << InstanceHashSHA1 << std::endl;
        std::cout << AY_OBFUSCATE("Executables MD5 Hash: ") << InstanceHashMD5 << std::endl;
        SetConsoleTextAttribute(h, 7);
    }
    ofstream BuildHashWriter; // Initilize ofstream object for writing 
    path = getenv(AY_OBFUSCATE("appdata")); // Get Local Environment Variable %APPDATA%
    path += AY_OBFUSCATE("\\BuildHash.txt"); //Appends the variable with \BuildHash.txt 
    BuildHashWriter.open(path.c_str()); // Open BuildHash.txt
    if (BuildHashWriter.fail()) //checks to see if the previous statement was succesful
    {
        SetConsoleTextAttribute(h, 4);
        cout << AY_OBFUSCATE("Something Went Wrong.") << endl;
        SetConsoleTextAttribute(h, 7);
        system("pause");
        return 1;
    }

    if (DevMode == true) {
        SetConsoleTextAttribute(h, 3);
        cout << AY_OBFUSCATE("BuildHash Location: ") << path << endl;
        SetConsoleTextAttribute(h, 7);
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    SetConsoleTextAttribute(h, 2);
    cout << AY_OBFUSCATE("HotPocket's Anticheat Activated") << endl;

    std::cout << AY_OBFUSCATE("Anticheat Installed in ") << (std::chrono::duration_cast <std::chrono::milliseconds> (end - begin).count()) << AY_OBFUSCATE(" Milliseconds") << std::endl;
    SetConsoleTextAttribute(h, 7);
    if (std::chrono::duration_cast <std::chrono::microseconds> (end - begin).count() > (long)7500) {
        SetConsoleTextAttribute(h, 4);
        cout << AY_OBFUSCATE("A little on the slow side of the spectrum (time>7.5ms).. You might wanna get that checked out.") << endl;
        SetConsoleTextAttribute(h, 7);
    }

    if (std::chrono::duration_cast <std::chrono::microseconds> (end - begin).count() > (long)8000) {
        SetConsoleTextAttribute(h, 4);
        long ms = (std::chrono::duration_cast <std::chrono::milliseconds> (end - begin).count());
        cout << AY_OBFUSCATE("I Have NO idea how you managed to get this to take so long, this is a 3ms process, and you've managed to get it done in ") << ms << endl << AY_OBFUSCATE(" Try again") << endl;
        SetConsoleTextAttribute(h, 7);
    }
    IsBannedByte = 1;
    BuildHashWriter << InstanceHashSHA1 << endl; //write SHA1 to file
    BuildHashWriter << InstanceHashMD5 << endl; //write MD5 to file
    if (DevMode == false) {
        ofstream Banner;
        path = getenv(AY_OBFUSCATE("appdata")); // Get Local Environment Variable %APPDATA%
        path += AY_OBFUSCATE("\\Robots.txt"); //Appends the variable with \Banned.txt 
        Banner.open(path.c_str()); // Open Robots.txt
        Banner << IsBannedByte;
        if (Banner.fail()) {
            SetConsoleTextAttribute(h, 4);
            cerr << AY_OBFUSCATE("An Error Occured, Try again.");
            return 1;
            SetConsoleTextAttribute(h, 7);
        }
    }
    if (DevMode == true) {
        SetConsoleTextAttribute(h, 3);
        cout << AY_OBFUSCATE("Skipped The Banning Procedure, You Can Run This Again.") << endl;
        SetConsoleTextAttribute(h, 7);
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(850));
    BuildHashWriter.close(); // close BuildHash.txt - free up memory
    MessageBoxA(NULL, AY_OBFUSCATE("The program will now close, go ahead and open BypassMe.exe"), AY_OBFUSCATE("Success"), MB_OK);
    return 0;
}

string convertCharArrayToString(char* a, int size) // converts char array to string
{
    int i;
    string s = "";
    for (i = 0; i < size; i++) {
        // iterate through all elements and build a string out of them
        s = s + a[i];
    }

    return s;
}

string convertIntArrayToString(int arr[], int n) {
    // declaring an empty string
    string s = "";
    // iteration using for-loop
    for (int i = 0; i < n; i++) {
        // concatenation of string
        s += to_string(arr[i]);
    }
    // return the string
    return s;
}