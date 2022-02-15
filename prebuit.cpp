#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
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
    time_t currentTime = time(0);
    tm temp = *localtime(&begin);
    tm currentTM = *localtime(&currentTime);
    int diff;

    temp.tm_year = currentTM.tm_year;
    switch(type){
    case 'w':
        diff = currentTM.tm_wday - temp.tm_wday;
        if(diff > 0) diff -= 7;
        temp.tm_mon = currentTM.tm_mon;
        temp.tm_mday = currentTM.tm_mday - diff;
        if(diff == 0 && temp.tm_hour+(temp.tm_min/60.) < currentTM.tm_hour+(currentTM.tm_min/60.)) temp.tm_mday += 7;
        break;

    case 'd':
        temp.tm_mon = currentTM.tm_mon;
        temp.tm_mday = currentTM.tm_mday;
        if(temp.tm_hour+(temp.tm_min/60.) < currentTM.tm_hour+(currentTM.tm_min/60.)) temp.tm_mday += 1;
        break;
    
    case 'm':
        temp.tm_mon = currentTM.tm_mon;
        if (temp.tm_mday < currentTM.tm_mday) temp.tm_mon += 1;
        else if (temp.tm_mday == currentTM.tm_mday){
            if (temp.tm_hour+(temp.tm_min/60.) < currentTM.tm_hour+(currentTM.tm_min/60.)) temp.tm_mon += 1;
        }
        break;
    
    case 'y':
        if (temp.tm_mon < currentTM.tm_mon) temp.tm_year += 1;
        else if (temp.tm_mon == currentTM.tm_mon){
            if (temp.tm_mday < currentTM.tm_mday) temp.tm_year += 1;
            else if (temp.tm_mday == currentTM.tm_mday){
                if (temp.tm_hour+(temp.tm_min/60.) < currentTM.tm_hour+(currentTM.tm_min/60.)) temp.tm_year += 1;
            }
            break;
        }
    }

    diff = difftime(end, begin);
    begin = mktime(&temp);
    end = begin + diff;
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
void sortRecur();

// ก่อนเรียกใช้ให้input data from txt เก็บในVector 
//และหาความยาวจากint x = sizeof(arr)/sizeof(arr[0]);
void printRecur(vector<string> d,int N)
{
    map<string, int> freqMap;
       
        for (auto& element : d) {
            auto res
                = freqMap.insert(pair<string, int>(element, 1));
            if (res.second == false)
                res.first->second++;
                
        }

        for (auto& element : freqMap) 
        {
            if (element.second == N) 
            {
                cout << element.first << " " ;
            }
            
        }

}



struct Date
{
    int day, month, year;
    string event;
};

bool compare(const Date &d1, const Date &d2)
{
    
    if (d1.year < d2.year)
        return true;
    if (d1.year == d2.year && d1.month < d2.month)
        return true;
    if (d1.year == d2.year && d1.month == d2.month &&
                              d1.day < d2.day)
        return true;
  
    return false;
}

// ก่อนเรียกใช้ให้input data from txt เก็บในลิส 
//และให้รับค่าinputค่าจำนวนคนในกลุ่มจากผู้ใช้เก็บในค่า n;
void sortEvent(Date arr[],int n)
{
    
    sort(arr, arr+n, compare);
}

void printEvent(Date arr[],int n)
{
    
    
    cout << "Sorted event : " << endl;
    for (int i=0; i<n; i++)
    {
       cout << arr[i].day << " " << arr[i].month
            << " " << arr[i].year << " " << arr[i].event;
       cout << endl;
    }
}


//Converting a String to Upper
string toupperString(string x)
{
    for_each(x.begin(), x.end(), [](char & c) 
    {
        c = ::toupper(c);
    });
    return x;
}

bool is_number(const string& s){
    return !s.empty() && find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !(c >= 48 && c <= 57);}) == s.end();
}

//print Date the result of matching 
//จะลบก็ได้นะซ้ำกับRecur
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
    void helpPage();

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

/*
    importEvents();
    importRecurs();

    for(unsigned int i = 0; i < recurs.size(); i++) {recurs[i].update();}

    sortEvent();
    sortRecur();

    system("CLS");
    mainMenu();
    system("CLS");

    return 0;
*/

}

void mainMenu(){
    string cmd;
    bool justEnter = true;
    while(true){
        if (justEnter){
            cout << left;
            cout << setw(31) << "| To view events"          << "Enter 1    |\n";
            cout << setw(31) << "| To view periodic events" << "Enter 2    |\n";
            cout << setw(31) << "| To exit"                 << "Enter exit |\n";
            cout << "-----------------------------------------------\n";
            cout << "Your input : ";
            justEnter = false;
        }

        getline(cin, cmd);
        cmd = toupperString(cmd);

        if(cmd == "1"){
            system("CLS");
            eventPage();
            system("CLS");
            justEnter = true;

        }else if(cmd == "2"){
            system("CLS");
            recurPage();
            system("CLS");
            justEnter = true;

        }else if(cmd == "HELP"){
            system("CLS");
            helpPage();
            system("CLS");            
            justEnter = true;

        }else if(cmd == "EXIT"){
            return;

        }else{
            cout << "\nInvalid input, please enter again : ";
        }
    }
}

void eventPage(){
    string cmd;
    bool justEnter = true;
    while(true){
        if(justEnter){
            if(events.size() != 0){
                cout << "| All events |\n";
                for(unsigned int i = 0; i < events.size(); i++) printEvent(i);
            }else{
                cout << "There are no any events.\n";
            }
            cout << '\n';
            cout << setw(45) << "| To return to previous page"  << "Enter return |\n";
            cout << setw(45) << "| To add a new event"          << "Enter new    |\n";
            cout << setw(45) << "| To delete all passed events" << "Enter pass   |\n";
            if(events.size() != 0) cout << setw(45) << "| To select an event"   << "Enter its index NO. |\n";
            cout << "-----------------------------------------------------------------------\n";
            cout << "Your input : ";
            justEnter = false;
        }


        getline(cin, cmd);
        cmd = toupperString(cmd);    
        if(atoi(cmd.c_str()) > 0 && atoi(cmd.c_str()) <= events.size()){
            system("CLS");
            interactEvent(atoi(cmd.c_str())-1);
            justEnter = true;
        
        }else if(cmd == "NEW"){
            addEvent();
            system("CLS");
            cout << "| Adding new event completed |\n";
            cout << "-----------------------------------------------------------------------\n\n";
            justEnter = true;

        }else if(cmd == "PASS"){
            passEvent();
            system("CLS");
            cout << "| All passed events have been deleted. |\n";
            cout << "-----------------------------------------------------------------------\n\n";
            justEnter = true;
        
        }else if(cmd == "RETURN"){
            return;
        }else{
            cout << "\nInvalid input, please enter again : ";
        }
        sortEvent();
        updateEvents();
    }
}

void addEvent(){
    tm temp;
    int mark[7] = {INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN};
    //begin hr, begin min, end hr, end min, date, month, year
    int stage;
    Event adding;
    string element;
    stringstream sso;
    cout << "\n\n";
    while(true){
        for(int i = 0; i < 7; i++){
            if(mark[i] == INT_MIN){
                stage = i;
                break;
            }
        }

        // recieving inputs
        switch(stage){
        case 0:
            cout << "|  Enter beginning hour  | : ";
            break;
        case 1:
            cout << "| Enter beginning minute | : ";
            break;
        case 2:
            cout << "|   Enter ending hour    | : ";
            break;
        case 3: 
            cout << "|  Enter ending minute   | : ";
            break;
        case 4:
            cout << "|       Enter date       | : ";
            break;
        case 5:
            cout << "|       Enter month      | : ";
            break;
        case 6:
            cout << "|       Enter year       | : ";
            break;    
        }

        element.clear();
        sso.clear();
        getline(cin,element);

        if(!is_number(element)){
            cout << "Input must not contain letters.\n";
            continue;
        }

        sso << element;
        for(int i = stage; sso >> mark[i] && stage < 7; i++) stage++;

        // checking invalid inputs
        cout << "element : " << element << '\n';
        for(int i = 0; i < stage; i++){
            if(i == 4 || i == 5) {if(mark[i] > 0) continue;}
            else if(i == 6) {if(mark[6] > 1970) continue;}
            else if(mark[i] >= 0) continue;
            switch(i){
            case 0:
                cout << "Beginning hour must be a number more or equal to 0.\n";
                break;
            case 1:
                cout << "Beginning minute must be a number more or equal to 0.\n";
                break;
            case 2:
                cout << "Ending hour must be a number more or equal to 0.\n";
                break;
            case 3:
                cout << "Ending minute must be a number more or equal to 0.\n";
                break;
            case 4:
                cout << "Event date must be a number more than 0.\n";
                break;
            case 5:
                cout << "Event month must be a number more than 0.\n";
                break;
            case 6:
                cout << "Event year must be a number more than 1970.\n";
                break; 
            }
            stage = i;
            for(int j = i; i < 6; i++) mark[j] = INT_MIN;
        }

        // checking if the program can break the loop
        if(stage > 6) goto exit_loop0;
    }
    exit_loop0: ;

    // converting to Event
    temp.tm_sec = 0;
    temp.tm_hour = mark[0];
    temp.tm_min = mark[1];
    temp.tm_mday = mark[4];
    temp.tm_mon = mark[5];
    temp.tm_year = mark[6];
    temp.tm_mon--;
    temp.tm_year -= 1900;
    adding.begin = mktime(&temp);

    if(mark[0] + mark[1]/60. > mark[2] + mark[3]/60.) mark[4] += 1;
    temp.tm_hour = mark[2];
    temp.tm_min = mark[3];
    adding.end = mktime(&temp);

    cout << "|   Enter name   | : ";
    getline(cin, element);
    adding.name = element;

    cout << "|  Enter author  | : ";
    getline(cin, element);
    adding.author = element;

    cout << "| Enter location | : ";
    getline(cin, element);
    adding.location = element;

    events.push_back(adding);
}

void interactEvent(int i){
    string cmd;
    cout << "| Selected event |\n";
    printEvent(i);
    cout << '\n' << left;
    cout << setw(45) << "| To return to previous page" << "Enter return   |\n";
    cout << setw(45) << "| To edit selected event"     << "Enter edit     |\n";
    cout << setw(45) << "| To delete selected event"   << "Enter del      |\n";
    cout << setw(45) << "| To vote the time period"    << "Enter votetime |\n";
    cout << setw(45) << "| To vote the location"       << "Enter voteloc  |\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Your input : ";

    while(true){
        getline(cin,cmd);
        cmd = toupperString(cmd);
        if(cmd == "EDIT"){
            system("CLS");
            editEvent(i);
            system("CLS");
            cout << "The selected event has been edited.\n";
            cout << "-----------------------------------------------------------------------\n\n";
            break;

        }else if(cmd == "DEL"){
            system("CLS");
            deleteEvent(i);
            system("CLS");
            cout << "The selected event has been deleted.\n";
            cout << "-----------------------------------------------------------------------\n\n";
            break;
        
        }else if(cmd == "VOTETIME" || cmd == "VOTE TIME"){
            system("CLS");
            voteTime(i);
            system("CLS");
            cout << "The selected event has been voted.\n";
            cout << "-----------------------------------------------------------------------\n\n";
            break;

        }else if(cmd == "VOTELOC" || cmd == "VOTE LOC" || cmd == "VOTELOCATION" || cmd == "VOTE LOCATION"){
            system("CLS");
            voteLocation(i);
            system("CLS");
            cout << "The selected event has been voted.\n";
            cout << "-----------------------------------------------------------------------\n\n";
            break;

        }else if(cmd == "RETURN"){
            system("CLS");
            break;
        }else{
            cout << "\nInvalid input, please enter again : ";
        }
    }
}

// If possible, add these functions here!
void editEvent(int i){

    int number ;
    string name,author,location ;
    Event event ;
    cout << "| To edit name     Press 1 |" << endl ;
    cout << "| To edit author   Press 2 |" << endl ;
    cout << "| To edit location Press 3 |" << endl ;
   
    cout << "Press number: "  ;
    cin >> number ;
    cin.ignore() ;

    switch(number){
        case 1 :
            cout << "Enter event name that you want to edit: " ;
            getline(cin,name) ;
            event.name = name ;
            break ;
        case 2 :
            cout << "Enter event author that you want to edit: " ;
            getline(cin,author) ;
            event.author = author ;
            break ;
        case 3 :
            cout << "Enter event author that you want to edit: " ;
            getline(cin,location) ;
            event.location = location ;
            break ;
        default :
            cout << "Invalid input Please try again" ;

    }
    
    for(int b = 0;b < events.size(); b++){
        if(b == i){
            events.erase(events.begin()+i) ;
            events.insert(events.begin()+i,event) ;
        }
    }  

}

void deleteEvent(int i){
    
    for(int a = 0;a < events.size(); a++){
        if(a == i){
            events.erase(events.begin()+i) ;
        }
    }  

}

void voteTime(int i){
}

void voteLocation(int i){
}

void passEvent(){
    time_t currentTime = time(0);
    for(unsigned int i = 0; i < events.size(); i++){
        if(difftime(currentTime, events[i].end) > 0) {
            events.erase(events.begin() + i);
            i--;
        }
    }
}

void recurPage(){
    string cmd;
    bool justEnter = true;
    while(true){
        if(justEnter){
            if(recurs.size() != 0){
                cout << "| All periodic events |\n";
                for(unsigned int i = 0; i < recurs.size(); i++) printRecur(i);
            }else{
                cout << "There are no any periodic events.\n";
            }

            cout << left << '\n';
            cout << setw(45) << "| To return to previous page" <<  "Enter return |\n";
            cout << setw(45) << "| To add a new periodic event" << "Enter new    |\n";
            cout << "-----------------------------------------------------------------------\n";
            cout << "Your input : ";
            justEnter = false;
        }

        getline(cin, cmd);
        cmd = toupperString(cmd);    
        if(atoi(cmd.c_str()) >= 1 && atoi(cmd.c_str()) <= recurs.size()){
            system("CLS");
            interactRecur(atoi(cmd.c_str())-1);
            justEnter = true;
        
        }else if(cmd == "NEW"){
            system("CLS");
            addRecur();
            system("CLS");
            cout << "Adding new periodic event completed\n\n";
            justEnter = true;
        
        }else if(cmd == "RETURN"){
            return;
        }else{
            cout << "\nInvalid input, please enter again : ";
        }
        sortRecur();
        updateRecurs();
    }
}

void addRecur(){
    time_t currentTime = time(0);
    tm temp = *localtime(&currentTime);
    Recur adding;
    string element;
    stringstream sso;

    cout << left;
    cout << "| Enter recursion type |\n\n";
    cout << setw(15) << "| For daily,"   << "enter 1 |\n";
    cout << setw(15) << "| For weekly,"  << "enter 2 |\n";
    cout << setw(15) << "| For monthly," << "enter 3 |\n";
    cout << setw(15) << "| For yearly,"  << "enter 4 |\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Your input : ";
    while(true){
        getline(cin,element);
        switch(atoi(element.c_str())){
        case 1:
            adding.type = 'd';
            goto exit_loop1;
        
        case 2:
            adding.type = 'w';
            goto exit_loop1;

        case 3:
            adding.type = 'm';
            goto exit_loop1;

        case 4:
            adding.type = 'y';
            goto exit_loop1;
        
        default:
            cout << "\nInvalid input, please enter again : ";
        }
    }
    exit_loop1: ;

    int stage;
    int mark[6] = {INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN};
    //begin hr, begin min, end hr, end min, date, month
    cout << '\n';

    while(true){
        for(int i = 0; i < 6; i++){
            if(mark[i] == INT_MIN){
                stage = i;
                break;
            }
        }

        // recieving inputs
        switch(stage){
        case 0:
            cout << setw(30) << "| Enter beginning hour |" << " : ";
            break;
        case 1:
            cout << setw(30) << "| Enter beginning minute |" << " : ";
            break;
        case 2:
            cout << setw(30) << "| Enter ending hour |" << " : ";
            break;
        case 3: 
            cout << setw(30) << "| Enter ending minute |" << " : ";
            break; 
        case 4:
            switch(adding.type){
            case 'w':
                cout << left;
                cout << "| Enter weekday |\n";
                cout << setw(15) << "| For Sunday"    << "Enter 1 |\n";
                cout << setw(15) << "| For Monday"    << "Enter 2 |\n";
                cout << setw(15) << "| For Tuesday"   << "Enter 3 |\n";
                cout << setw(15) << "| For Wednesday" << "Enter 4 |\n";
                cout << setw(15) << "| For Thursday"  << "Enter 5 |\n";
                cout << setw(15) << "| For Friday"    << "Enter 6 |\n";
                cout << setw(15) << "| For Saturday"  << "Enter 7 |\n";
                cout << "-----------------------------------------------------------------------\n";
                cout << "Your input : ";
                break;

            case 'm':
            case 'y':
                cout << "| Enter date  | : ";
            }
            break;
        case 5:
            cout <<     "| Enter month | : ";
            break;
        }

        getline(cin,element);

        if(!is_number(element)){
            cout << "Input must not contain letters.\n";
            continue;
        }

        sso.clear();
        sso << element;
        for(int i = stage; sso >> mark[i] && stage < 6; i++) stage++;

        // checking invalid inputs
        for(int i = 0; i < stage; i++){
            if(i == 4 && adding.type == 'w'){
                if(mark[4] >= 1 && mark[4] <= 7) continue;
                else{
                    cout << "Event weekday must be a number between 1 to 7.\n";
                    stage = 4;
                    for(int j = 4; j < 6; j++) mark[j] = INT_MIN;
                    break;
                }
            }
            else if(i == 4 || i == 5) {if(mark[i] > 0) continue;}
            else if(mark[i] >= 0) continue;
            switch(i){
            case 0:
                cout << "Beginning hour must be a number more or equal to 0.\n";
                break;

            case 1:
                cout << "Beginning minute must be a number more or equal to 0.\n";
                break;

            case 2:
                cout << "Ending hour must be a number more or equal to 0.\n";
                break;

            case 3:
                cout << "Ending minute must be a number more or equal to 0.\n";
                break;
            
            case 4:
                if(adding.type == 'd') break;
                cout << "Event date must be a number more than 0.\n";
                break;

            case 5:
                if(adding.type != 'y') break;
                cout << "Event month must be a number more than 0.\n";
                break;
            }
            stage = i;
            for(int j = i; j < 6; j++) mark[j] = INT_MIN;
        }

        switch(adding.type){
        case 'd':
            if(stage > 3) goto exit_loop2;
            break;

        case 'w':
        case 'm':
            if(stage > 4) goto exit_loop2;
            break;

        case 'y':
            if(stage > 5) goto exit_loop2;
            break;
        }
    }
    exit_loop2: ;

    // converting to Recur  
    temp.tm_sec = 0;
    temp.tm_hour = mark[0];
    temp.tm_min = mark[1];
    if(adding.type != 'd' && adding.type != 'w') temp.tm_mday = mark[4];

    else if(adding.type == 'w'){
        int weekday = mark[4] - 1;
        int diff = temp.tm_wday - weekday;
        temp.tm_mday -= diff;
    }

    if(adding.type == 'y'){
        temp.tm_mon = mark[5];
        temp.tm_mon--;
    }

    adding.begin = mktime(&temp);

    temp.tm_hour = mark[2];
    temp.tm_min = mark[3];
    adding.end = mktime(&temp);
    adding.update();

    cout << "|   Enter name   | : ";
    getline(cin, element);
    adding.name = element;

    cout << "|  Enter author  | : ";
    getline(cin, element);
    adding.author = element;

    cout << "| Enter location | : ";
    getline(cin, element);
    adding.location = element;

    recurs.push_back(adding);
}

void interactRecur(int i){
    string cmd;
    cout << left;
    cout << "| Selected periodic event |\n";
    printRecur(i);
    cout << '\n';
    cout << setw(45) << "| To return to previous page"            << "Enter return |\n";
    cout << setw(45) << "| To edit the selected periodic event"   << "Enter edit   |\n";
    cout << setw(45) << "| To delete the selected periodic event" << "Enter del    |\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Your input : ";

    while(true){
        getline(cin,cmd);
        cmd = toupperString(cmd);
        if(cmd == "EDIT"){
            system("CLS");
            editRecur(i);
            system("CLS");
            cout << "| The selected event has been edited. |\n";
            cout << "-----------------------------------------------------------------------\n\n";
            break;

        }else if(cmd == "DEL"){
            system("CLS");
            deleteRecur(i);
            system("CLS");
            cout << "| The selected event has been deleted. |\n";
            cout << "-----------------------------------------------------------------------\n\n";
            break;

        }else if(cmd == "RETURN"){
            system("CLS");
            break;
        }else{
            cout << "\nInvalid input, please enter again : ";
        }
    }
}

// If possible, add these functions here!
void editRecur(int i){
    
    int number ;
    string name,author,location ;
    Recur recur ;
    cout << "| To edit name     Press 1 |" << endl ;
    cout << "| To edit author   Press 2 |" << endl ;
    cout << "| To edit location Press 3 |" << endl ;
   
    cout << "Press number: "  ;
    cin >> number ;
    cin.ignore() ;

    switch(number){
        case 1 :
            cout << "Enter event name that you want to edit: " ;
            getline(cin,name) ;
            recur.name = name ;
            break ;
        case 2 :
            cout << "Enter event author that you want to edit: " ;
            getline(cin,author) ;
            recur.author = author ;
            break ;
        case 3 :
            cout << "Enter event location that you want to edit: " ;
            getline(cin,location) ;
            recur.location = location ;
            break ;
        default :
            cout << "Invalid input Please try again" ;

    }
    
    for(int f = 0;f < recurs.size(); f++){
        if(f == i){
            recurs.erase(recurs.begin()+i) ;
            recurs.insert(recurs.begin()+i,recur) ;
        }
    }  


}

void deleteRecur(int i){

    for(int e = 0;e < recurs.size(); e++){
        if(e == i){
            recurs.erase(recurs.begin()+i) ;
        }
    }  

}

void helpPage(){
    //มาแก้ด่วย เราทำมั่วมากๆ 🤦‍♂️
    cout << "What can you do with this program?\n";
    cout << "This program manages events and let the users to create, delete, and even vote for events details.\n";
    cout << "There are two types of events, normal events and periodic events.\n";
    cout << "1. Normal events are events which start at a time end end at another time.\n";
    cout << "2. Periodic events, are events which occur periodically, including dialy, weekly, monthly, and yearly.\n";

    cin.get();
    cin.ignore();
    cout << "\nPress Enter to continue\n";
}