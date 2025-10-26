#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits> 
#include <ctime>
#include <set>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, MAX_AGE = 20;
int N_NAMES = 0;
int N_COLORS = 0;


int select_goat(set<Goat> &trip);
void delete_goat(set<Goat> &trip);
void add_goat(set<Goat> &trip, string names[], string colors[], int nNames, int nColors);
void display_trip(set<Goat> &trip);
int main_menu();

int main() {
    srand(time(0));

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (N_NAMES < SZ_NAMES && (fin >> names[N_NAMES])) N_NAMES++;
    fin.close();

    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (N_COLORS < SZ_COLORS && (fin1 >> colors[N_COLORS])) N_COLORS++;
    fin1.close();

    set<Goat> trip;

    while (true){
        int choice = main_menu();

        switch (choice) {
            case 1:

                add_goat(trip, names, colors, N_NAMES, N_COLORS);
                break;
            case 2:
                delete_goat(trip);
                break;
            case 3:
                display_trip(trip);
                break;
            case 4:
                cout << "\nGoodbye! Thanks for using GOAT MANAGER 3001.\n";
                return 0;

        }
    }
}

int main_menu() {
    cout << "\n*** GOAT MANAGER 3001 ***\n"
         << "[1] Add a goat\n"
         << "[2] Delete a goat\n"
         << "[3] List goats\n"
         << "[4] Quit\n"
         << "Choice --> ";

        int choice;

        while (!(cin >> choice) || choice < 1 || choice > 4){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number between 1 and 4: ";
        }
    return choice;
}

void display_trip(set<Goat> &trip){
    cout << "\nCurrent Trip (" << trip.size() << " goat" 
        << (trip.size() == 1 ? "" : "s") << "):\n";
    
    if (trip.empty()) {
        cout << "  (empty)\n";
        return;
    }


    cout << left << setw(5)  << "#"
         << left << setw(16) << "Name"
         << left << setw(8)  << "Age"
         << left << setw(12) << "Color" << "\n";
    cout << string(40, '-') << "\n";

    int idx = 1;
    for (const auto& g : trip) {
        cout << left << setw(5)  << idx++
             << left << setw(16) << g.get_name()
             << left << setw(8)  << g.get_age()
             << left << setw(12) << g.get_color()
             << "\n";
    }
}

int select_goat(set<Goat> &trip) {
    if (trip.empty()) {
        cout << "\nNo goats to select.\n";
        return -1;
    }

    cout << "\n";
    int i = 1;
    for (const auto& g : trip) {
        cout << "[" << i << "] "
             << g.get_name() << " ("
             << g.get_age()  << ", "
             << g.get_color() << ")\n";
        i++;
    }
    cout << "Select #: ";

    int pick;
    while (!(cin >> pick) || pick < 1 || pick >= i) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter 1–" << (i - 1) << ": ";
    }
    return pick;
}

void delete_goat (set<Goat> &trip){
    int pick = select_goat(trip);
    if (pick == -1) return;

    int i = 1;
    for (auto it = trip.begin(); it != trip.end(); it++, i++){
        if (i == pick){
            cout << "Removed: " << it->get_name()
                << " (" << it->get_age() << ", " << it->get_color() << ")\n";
            trip.erase(it);
            return;
        }
    }
}

void add_goat(set<Goat> &trip,string names[], string colors[], int nNames, int nColors) {
    if (nNames == 0 || nColors == 0){
        cout << "\n(No names/colors loaded, cannot add.)\n";
        return;
    }
    int namei = rand() % nNames;
    int colori = rand() % nColors;
    int age = rand() % (MAX_AGE + 1);

    Goat g(names[namei], age, colors[colori]);
    trip.insert(g);

    cout << "Added: " << g.get_name()
         << " (" << g.get_age() << ", " << g.get_color() << ")\n";
}