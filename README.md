📂 Console-Based File Explorer (C++ | Linux Terminal)

A simple, lightweight File Explorer in the Linux terminal, built as part of the Wipro COE Embedded Linux Training Capstone Project.

The application lets users navigate directories and perform file operations using a numbered menu UI, making it easy even for those who are not comfortable with Linux commands.

🚀 Features

Feature	Description

✅ List files	Shows files & folders in current directory

✅ Navigate (cd)	Change directory and update working path

✅ Create file	Creates an empty file

✅ Delete file	Deletes the selected file

✅ Rename/Move	Renames a file or moves it to another path

✅ Copy file	Copies content from one file to another

✅ Search (Recursive)	Searches for a file inside all subdirectories

✅ chmod (Permissions)	Modify file permissions (e.g., 755)

✅ Menu-based UI	No need to remember commands

🛠️ Tech Stack

Programming Language -	C++

Linux Concepts Used -	System Calls, File Handling

Headers Used - <dirent.h>, <unistd.h>, <sys/stat.h>, <fstream>

Environment - Ubuntu (WSL / Linux)

Version Control	- Git, GitHub

▶️ How to Run

1️⃣ Clone the repository

git clone https://github.com/Adityakutru/Linux_Terminal_fileExplorer

cd Linux_Terminal_fileExplorer

2️⃣ Compile

g++ explorer.cpp -o explorer

3️⃣ Run

./explorer

⭐ Suggestions or Contributions

Feel free to fork this repository and enhance features:

Add ncurses UI (arrow key navigation)

Add file details (size, created date)

Show directory tree visually

Pull requests welcome!
