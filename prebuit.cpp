#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Event{
    public:
        time_t begin, end; // [start,stop)
        string name, author, location;
        //bool isNotified;
};

class Recur{
    //Periodical events
    public:
        // 'd' = daily, 'w' = weekly, 'm' = monthly, 'y' = yearly
        time_t begin, end;
        char type;
        string name, author, location;
};

//main Events and Periodical events
vector<Event> events;
vector<Recur> recurs;

// import and write to .txt files
void importEvents();
void importRecurs();
void updateEvents();
void updateRecurs();

// pages and menus
void mainMenu();
    void eventPage();
        void addEvent();
        void interactEvent(int);
            void deleteEvent(int);
            void editEvent(int);
    void recurPagr();
        void addRecur();
        void interactRecur(int);
            void deleteRecur(int);
            void editRecur(int);

int main(){

}