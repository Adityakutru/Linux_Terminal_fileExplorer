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
    int choice;
    string arg1, arg2;

    while (true) {
        cout << "\n============== LINUX FILE EXPLORER ==============\n";
        cout << "Current Path: " << CYAN << currentPath << RESET << "\n";
        cout << "--------------------------------------------------\n";
        cout << "1. List files\n";
        cout << "2. Change directory (cd)\n";
        cout << "3. Create file\n";
        cout << "4. Delete file\n";
        cout << "5. Rename/Move file\n";
        cout << "6. Copy file\n";
        cout << "7. Search file\n";
        cout << "8. Change permissions (chmod)\n";
        cout << "9. Exit\n";
        cout << "--------------------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listDir(currentPath);
                break;

            case 2:
                cout << "Enter directory name: ";
                cin >> arg1;
                if (chdir(arg1.c_str()) == 0) {
                    char buf[500];
                    getcwd(buf, sizeof(buf));
                    currentPath = buf;
                } else {
                    cout << "❌ Directory not found.\n";
                }
                break;

            case 3:
                cout << "Enter file name to create: ";
                cin >> arg1;
                ofstream(arg1); // creates file
                cout << "✅ File created.\n";
                break;

            case 4:
                cout << "Enter file name to delete: ";
                cin >> arg1;
                remove(arg1.c_str());
                cout << "🗑 File deleted.\n";
                break;

            case 5:
                cout << "Enter current file name: ";
                cin >> arg1;
                cout << "Enter new file name: ";
                cin >> arg2;
                rename(arg1.c_str(), arg2.c_str());
                cout << "♻️  File renamed/moved.\n";
                break;

            case 6:
                cout << "Enter source file: ";
                cin >> arg1;
                cout << "Enter destination file: ";
                cin >> arg2;
                {
                    ifstream src(arg1, ios::binary);
                    ofstream dest(arg2, ios::binary);
                    dest << src.rdbuf();
                }
                cout << "📄 File copied.\n";
                break;

            case 7:
                cout << "Enter filename to search: ";
                cin >> arg1;
                searchFile(currentPath, arg1);
                break;

            case 8:
                cout << "Enter permission (e.g., 755): ";
                cin >> arg1;
                cout << "Enter filename: ";
                cin >> arg2;
                chmod(arg2.c_str(), stoi(arg1, 0, 8));
                cout << "🔑 Permission changed.\n";
                break;

            case 9:
                cout << "Exiting explorer.\n";
                return 0;

            default:
                cout << "❌ Invalid choice. Try again.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
    }
}
