#include <iostream>
#include <unordered_map>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

class Note {
public:
    string title;
    string content;

    Note(string t, string c) {
        title = t;
        content = c;
    }

    void display() const {
        cout << "Title: " << title << "\nContent: " << content << endl;
    }
};

unordered_map<string, Note> noteMap;
queue<string> recentNotes;
vector<Note> noteList;
const int MAX_HISTORY = 5;

string toLower(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void addNote(string title, string content) {
    Note newNote(title, content);
    string key = toLower(title);
    noteMap[key] = newNote;
    noteList.push_back(newNote);
    cout << "Note saved successfully.\n";
}

void viewNote(string title) {
    string key = toLower(title);
    if (noteMap.find(key) != noteMap.end()) {
        cout << "\n--- Note ---\n";
        noteMap[key].display();

        queue<string> temp;
        while (!recentNotes.empty()) {
            string curr = recentNotes.front();
            recentNotes.pop();
            if (toLower(curr) != key) temp.push(curr);
        }
        recentNotes = temp;

        recentNotes.push(title);
        if (recentNotes.size() > MAX_HISTORY) recentNotes.pop();
    } else {
        cout << "Note not found.\n";
    }
}

void viewAllNotes() {
    if (noteList.empty()) {
        cout << "No notes saved yet.\n";
        return;
    }
    for (const Note& note : noteList) {
        cout << "\n";
        note.display();
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
        cout << "- " << temp.front() << "\n";
        temp.pop();
    }
}

int main() {
    int choice;
    string title, content;

    while (true) {
        cout << "\n=== DSA Notepad ===\n";
        cout << "1. Add Note\n";
        cout << "2. View Note by Title\n";
        cout << "3. View All Notes\n";
        cout << "4. View Recently Opened Notes\n";
        cout << "5. Exit\n";
        cout << "Choose: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter Title: ";
                getline(cin, title);
                cout << "Enter Content: ";
                getline(cin, content);
                addNote(title, content);
                break;
            case 2:
                cout << "Enter Title to View: ";
                getline(cin, title);
                viewNote(title);
                break;
            case 3:
                viewAllNotes();
                break;
            case 4:
                viewRecentNotes();
                break;
            case 5:
                cout << "Exiting Notepad. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
