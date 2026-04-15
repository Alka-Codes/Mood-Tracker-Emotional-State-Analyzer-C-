#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
using namespace std;

// Mood class
class Mood {
private:
    string mood;
    string note;
    string date;

public:
    Mood(string m, string n, string d) {
        mood = m;
        note = n;
        date = d;
    }

    string getMood() const { return mood; }
    string getNote() const { return note; }
    string getDate() const { return date; }

    string toFileString() const {
        return mood + "|" + note + "|" + date;
    }
};

// Get current date
string getDate() {
    time_t now = time(0);
    return string(ctime(&now));
}

// Save mood
void saveMood(const Mood& m) {
    ofstream file("data.txt", ios::app);
    file << m.toFileString() << endl;
}

// Load moods
vector<Mood> loadMoods() {
    vector<Mood> moods;
    ifstream file("data.txt");

    string line;
    while (getline(file, line)) {
        int p1 = line.find("|");
        int p2 = line.rfind("|");

        if (p1 != string::npos && p2 != string::npos) {
            string mood = line.substr(0, p1);
            string note = line.substr(p1 + 1, p2 - p1 - 1);
            string date = line.substr(p2 + 1);

            moods.push_back(Mood(mood, note, date));
        }
    }
    return moods;
}

// Analyze moods
void analyze(const vector<Mood>& moods) {
    int happy = 0, sad = 0, neutral = 0, angry = 0;

    for (const auto& m : moods) {
        if (m.getMood() == "happy") happy++;
        else if (m.getMood() == "sad") sad++;
        else if (m.getMood() == "neutral") neutral++;
        else if (m.getMood() == "angry") angry++;
    }

    int total = moods.size();

    cout << "\n----- Mood Analysis -----\n";
    cout << "Total Entries: " << total << endl;

    if (total > 0) {
        cout << "Happy %: " << (happy * 100.0 / total) << endl;
        cout << "Sad %: " << (sad * 100.0 / total) << endl;
        cout << "Neutral %: " << (neutral * 100.0 / total) << endl;
        cout << "Angry %: " << (angry * 100.0 / total) << endl;

        // Trend detection
        if (happy > sad && happy > angry)
            cout << "Overall Mood: Positive 😊\n";
        else if (sad > happy)
            cout << "Overall Mood: Negative 😢\n";
        else
            cout << "Overall Mood: Neutral 😐\n";
    }
}

// Show all records
void displayAll(const vector<Mood>& moods) {
    cout << "\n----- Mood History -----\n";
    for (const auto& m : moods) {
        cout << m.getDate()
             << " | " << m.getMood()
             << " | " << m.getNote() << endl;
    }
}

// Main function
int main() {
    int choice;

    while (true) {
        cout << "\n===== Mood Tracker =====\n";
        cout << "1. Add Mood\n";
        cout << "2. View Analysis\n";
        cout << "3. View All Records\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            string mood, note;

            cout << "Enter mood (happy/sad/neutral/angry): ";
            cin >> mood;

            // Validation
            if (mood != "happy" && mood != "sad" &&
                mood != "neutral" && mood != "angry") {
                cout << "Invalid mood!\n";
                continue;
            }

            cin.ignore();
            cout << "Enter note: ";
            getline(cin, note);

            Mood m(mood, note, getDate());
            saveMood(m);

            cout << "Mood saved successfully!\n";
        }
        else if (choice == 2) {
            vector<Mood> moods = loadMoods();
            analyze(moods);
        }
        else if (choice == 3) {
            vector<Mood> moods = loadMoods();
            displayAll(moods);
        }
        else if (choice == 4) {
            cout << "Exiting program...\n";
            break;
        }
        else {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}