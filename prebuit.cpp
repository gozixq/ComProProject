#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;

class Event{
    public:
        time_t begin, end; // [start,stop)
        string name, author, location;
};

class Recur{
    //Periodical events
    public:
        time_t begin, end;
        char type; // 'd' = daily, 'w' = weekly, 'm' = monthly, 'y' = yearly
        string name, author, location;

        void update();
};

void Recur::update(){

}


// global Events and Periodical events
vector<Event> events;
vector<Recur> recurs;

// import and write to .txt files
void importEvents();
void importRecurs();
void updateEvents();
void updateRecurs();

// miscellaneous functions, newer functions will be added here
void printEvent(int);
void printRecur(int);
void sortEvent();
void sortRecur();
string toupperString(string);

// interface : pages and menus
void mainMenu();
    void eventPage();
        void addEvent();
        void interactEvent(int);
            void deleteEvent(int);
            void editEvent(int);
            void voteTime(int);
            void voteLocation(int);
        void passEvent();
    void recurPage();
        void addRecur();
        void interactRecur(int);
            void deleteRecur(int);
            void editRecur(int);

int main(){

}