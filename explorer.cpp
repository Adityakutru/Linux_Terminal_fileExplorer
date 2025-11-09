#include <iostream>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
using namespace std;

// Colors for UI (optional)
#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"

// ✅ LIST DIRECTORY
void listDir(string path) {
    DIR *dir = opendir(path.c_str());
    dirent *entry;
    struct stat info;

    if (!dir) {
        cout << "❌ Unable to open directory.\n";
        return;
    }

    cout << "\n--------------------------------------------\n";
    cout << "📁 Current Directory: " << CYAN << path << RESET << endl;
    cout << "--------------------------------------------\n";

    while ((entry = readdir(dir)) != NULL) {
        string name = entry->d_name;
        string fullPath = path + "/" + name;
        stat(fullPath.c_str(), &info);

        if (S_ISDIR(info.st_mode)) // directory
            cout << BLUE << "[DIR]  " << name << RESET << endl;
        else // file
            cout << "[FILE] " << name << endl;
    }
    closedir(dir);
}

// ✅ SEARCH RECURSIVELY
void searchFile(string base, string target) {
    DIR *dir = opendir(base.c_str());
    if (!dir) return;

    dirent *entry;
    struct stat info;
    
    while ((entry = readdir(dir)) != NULL) {
        string name = entry->d_name;
        string fullPath = base + "/" + name;

        if (name == target)
            cout << "✅ Found at: " << fullPath << endl;

        stat(fullPath.c_str(), &info);

        if (S_ISDIR(info.st_mode) && name != "." && name != "..")
            searchFile(fullPath, target);
    }
    closedir(dir);
}

// --------------------------------------------------------------
// 🔥 MAIN PROGRAM — NUMBERED UI MENU
// --------------------------------------------------------------
int main() {
    string currentPath = ".";
    string arg1, arg2;

    while (true) {
    cout << "\n==== FILE EXPLORER ====\n";
    cout << "1. List directory\n";
    cout << "2. Change directory\n";
    cout << "3. Create file\n";
    cout << "4. Delete file\n";
    cout << "5. Rename file\n";
    cout << "6. Copy file\n";
    cout << "7. Search file\n";
    cout << "8. Change permissions (chmod)\n";
    cout << "0. Exit\n";
    cout << "Enter choice: ";

    int choice;
    cin >> choice;

    switch (choice) {

    case 1:
        listDir(currentPath);
        break;

    case 2: {
        string path;
        cout << "Enter directory name: ";
        cin >> path;
        chdir(path.c_str());
        char buf[500];
        getcwd(buf, sizeof(buf));
        currentPath = buf;
        break;
    }

    case 3: {
        string filename;
        cout << "Enter filename to create: ";
        cin >> filename;
        ofstream file(filename);
        file.close();
        cout << "✅ File created\n";
        break;
    }

    case 4: {
        string filename;
        cout << "Enter filename to delete: ";
        cin >> filename;
        remove(filename.c_str());
        cout << "✅ File deleted\n";
        break;
    }

    case 5: {
        string oldName, newName;
        cout << "Old name: ";
        cin >> oldName;
        cout << "New name: ";
        cin >> newName;
        rename(oldName.c_str(), newName.c_str());
        cout << "✅ Renamed\n";
        break;
    }

    case 6: {
        string src, dest;
        cout << "Enter source filename: ";
        cin >> src;
        cout << "Enter destination filename: ";
        cin >> dest;
        ifstream in(src, ios::binary);
        ofstream out(dest, ios::binary);
        out << in.rdbuf();
        cout << "✅ Copied\n";
        break;
    }

    case 7: {
        string target;
        cout << "Enter filename to search: ";
        cin >> target;
        searchFile(currentPath, target);
        break;
    }

    case 8: {
        string perm, file;
        cout << "Enter permission (e.g., 755): ";
        cin >> perm;
        cout << "Enter filename: ";
        cin >> file;
        chmod(file.c_str(), stoi(perm, 0, 8));
        cout << "✅ Permission changed\n";
        break;
    }

    case 0:
        return 0;
    }
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}
