#include <iostream>
#include <map>
#include <queue>
#include <vector>
#include <fstream>  // for file handling
using namespace std;

class Note {
public:
    string title;
    string content;

    Note() {}

    Note(string t, string c) {
        title = t;
        content = c;
    }

    void display() {
        cout << "Title: " << title << endl;
        cout << "Content: " << content << endl;
    }
};

map<string, Note> noteMap;
vector<Note> noteList;
queue<string> recentNotes;
const int MAX_RECENT = 5;

void addNote(string title, string content) {
    Note newNote(title, content);
    noteMap[title] = newNote;
    noteList.push_back(newNote);
    cout << "Note added successfully.\n";
}

void viewNote(string title) {
    if (noteMap.find(title) != noteMap.end()) {
        cout << "\n--- Note ---\n";
        noteMap[title].display();

        queue<string> temp;
        while (!recentNotes.empty()) {
            string current = recentNotes.front();
            recentNotes.pop();
            if (current != title) {
                temp.push(current);
            }
        }
        recentNotes = temp;
        recentNotes.push(title);
        if (recentNotes.size() > MAX_RECENT) {
            recentNotes.pop();
        }

    } else {
        cout << "Note not found.\n";
    }
}

void viewAllNotes() {
    if (noteList.size() == 0) {
        cout << "No notes available.\n";
        return;
    }

    for (int i = 0; i < noteList.size(); i++) {
        cout << "\n";
        noteList[i].display();
    }
}

void viewRecentNotes() {
    if (recentNotes.empty()) {
        cout << "No recent notes.\n";
        return;
    }

    cout << "--- Recent Notes ---\n";
    queue<string> temp = recentNotes;
    while (!temp.empty()) {
        cout << "- " << temp.front() << endl;
        temp.pop();
    }
}

void deleteNote(string title) {
    if (noteMap.find(title) == noteMap.end()) {
        cout << "Note not found. Nothing to delete.\n";
        return;
    }

    noteMap.erase(title);

    for (int i = 0; i < noteList.size(); i++) {
        if (noteList[i].title == title) {
            noteList.erase(noteList.begin() + i);
            break;
        }
    }

    queue<string> temp;
    while (!recentNotes.empty()) {
        string current = recentNotes.front();
        recentNotes.pop();
        if (current != title) {
            temp.push(current);
        }
    }
    recentNotes = temp;

    cout << "Note deleted successfully.\n";
}

void saveNotesToFile() {
    ofstream file("notes.txt");
    if (!file) {
        cout << "Error opening file for writing.\n";
        return;
    }

    for (int i = 0; i < noteList.size(); i++) {
        file << "Title: " << noteList[i].title << "\n";
        file << "Content: " << noteList[i].content << "\n\n";
    }

    file.close();
    cout << "All notes saved to 'notes.txt'\n";
}

int main() {
    string password;
    const string correctPassword = "vansh1910";
    int attempts = 0;

    while (attempts < 3) {
        cout << "Enter password to access DSA Notepad: ";
        getline(cin, password);

        if (password == correctPassword) {
            cout << "Access granted!\n";
            break;
        } else {
            attempts++;
            cout << "Incorrect password. Attempts left: " << 3 - attempts << endl;
        }

        if (attempts == 3) {
            cout << "Too many failed attempts. Exiting program.\n";
            return 0;
        }
    }




    
    int choice;
    string title, content;

    while (true) {
        cout << "\n=== DSA Notepad ===\n";
        cout << "1. Add Note\n";
        cout << "2. View Note\n";
        cout << "3. View All Notes\n";
        cout << "4. View Recent Notes\n";
        cout << "5. Delete Note\n";
        cout << "6. Save Notes to File\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Enter title: ";
            getline(cin, title);
            cout << "Enter content: ";
            getline(cin, content);
            addNote(title, content);
        }
        else if (choice == 2) {
            cout << "Enter title to view: ";
            getline(cin, title);
            viewNote(title);
        }
        else if (choice == 3) {
            viewAllNotes();
        }
        else if (choice == 4) {
            viewRecentNotes();
        }
        else if (choice == 5) {
            cout << "Enter title to delete: ";
            getline(cin, title);
            deleteNote(title);
        }
        else if (choice == 6) {
            saveNotesToFile();
        }
        else if (choice == 7) {
            cout << "Exiting. Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
