#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
#include <bits/stdc++.h>
#include <map>

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

//Converting a String to Upper
string toupperString(string x)
{
    for_each(x.begin(), x.end(), [](char & c) 
    {
        c = ::toupper(c);
    });
    return x;
}

//print Date the result of matching 
void PrintDate(vector<string> d,int N)
{
    map<string, int> freqMap;
       
        for (auto& element : d) {
            auto res
                = freqMap.insert(pair<string, int>(element, 1));
            if (res.second == false)
                res.first->second++;
                
        }
        
        cout << "The date of appointment : ";
        
        
        
        for (auto& element : freqMap) 
        {
            if (element.second == N) 
            {
                cout << element.first << " " ;
            }
            
        }
}


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

int main()
{
    int N;
    
    vector<string> Date;
    string InputDate;
    fstream infile("filedateforprintdate.txt");
    
    //Input number of groups.
    cout << "Input the number of groups : ";
    cin >> N;
    cin.get();
    
    //txt to vector
    while (getline(infile,InputDate))
    {
        Date.push_back(InputDate);
    }

    
    cout << "-----------------------------------------------" << endl;

    cout << "Matching Time !!!" << endl;
    
    PrintDate(Date,N);



}