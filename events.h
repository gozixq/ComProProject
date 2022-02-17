#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

bool is_number(const string& s){
    return !s.empty() && find_if(s.begin(), s.end(), 
        [](unsigned char c) { return !(c >= '0' && c <= '9' || c == ' ' || c == '-');}) == s.end();
}

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

void cinMark(int mark[7], int &stage){
    string element;
    stringstream sso;

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
        for(int i = 0; i < stage; i++){
            switch(i){
            case 0:
                if(mark[0] < 0)
                    cout << "Beginning hour must be a number more or equal to 0.\n";
                else if(mark[0] >= 24) 
                    cout << "Beginning hour must be a number less than 24.\n";
                else
                    goto jump_event;
            break;

            case 1:
                if(mark[1] < 0)
                    cout << "Beginning minute must be a number more or equal to 0.\n";
                else if(mark[1] >= 60) 
                    cout << "Beginning hour must be a number less than 60.\n";
                else
                    goto jump_event;
            break;

            case 2:
                if(mark[2] < 0)
                    cout << "Ending hour must be a number more or equal to 0.\n";
                else if(mark[2] >= 24) 
                    cout << "Ending hour must be a number less than 24.\n";
                else
                    goto jump_event;
            break;

            case 3:
                if(mark[3] < 0)
                    cout << "Ending minute must be a number more or equal to 0.\n";
                else if(mark[3] >= 60) 
                    cout << "Ending hour must be a number less than 60.\n";
                else
                    goto jump_event;
            break;

            case 4:
                if(mark[4] <= 0)
                    cout << "Event date must be a number more than 0.\n";
                else
                    goto jump_event;
            break;

            case 5: 
                if(mark[5] <= 0)
                    cout << "Event month must be a number more than 0.\n";
                else
                    goto jump_event;
            case 6:
                if(mark[6] < 1970) // Unix timestamp starts in 1970.
                    cout << "Event year must be a number more than 1969.\n";
                else if(mark[6] > 2037) // Unix timestamp ends in 2038!
                    cout << "Event year must be a number less than 2038.\n";
                else
                    goto jump_event;
            break;
            }
            stage = i;
            for(int j = i; i < 6; i++) mark[j] = INT_MIN;
            jump_event: ;
        }

        // checking if the program can break the loop
        if(stage > 6) return;
    }
}

void cinMark(int mark[6], int &stage, const char type){
    string element;
    stringstream sso;

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
            switch(type){
            case 'w':
                cout << "| Enter weekday |\n";
                cout << "| For Sunday       Enter 1 |\n";
                cout << "| For Monday       Enter 2 |\n";
                cout << "| For Tuesday      Enter 3 |\n";
                cout << "| For Wednesday    Enter 4 |\n";
                cout << "| For Thursday     Enter 5 |\n";
                cout << "| For Friday       Enter 6 |\n";
                cout << "| For Saturday     Enter 7 |\n";
                cout << "-----------------------------------------------------------------------\n";
                cout << "Your input : ";
                break;

            case 'm':
            case 'y':
                cout << "|       Enter date       | : ";
            }
            break;
        case 5:
            cout << "|       Enter month      | : ";
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
            switch(i){
            case 0:
                if(mark[0] < 0)
                    cout << "Beginning hour must be a number more or equal to 0.\n";
                else if(mark[0] >= 24) 
                    cout << "Beginning hour must be a number less than 24.\n";
                else
                    goto jump_recur;
                break;

            case 1:
                if(mark[1] < 0)
                    cout << "Beginning minute must be a number more or equal to 0.\n";
                else if(mark[1] >= 60) 
                    cout << "Beginning hour must be a number less than 60.\n";
                else
                    goto jump_recur;
                break;

            case 2:
                if(mark[2] < 0)
                    cout << "Ending hour must be a number more or equal to 0.\n";
                else if(mark[2] >= 24) 
                    cout << "Ending hour must be a number less than 24.\n";
                else
                    goto jump_recur;
                break;

            case 3:
                if(mark[3] < 0)
                    cout << "Ending minute must be a number more or equal to 0.\n";
                else if(mark[3] >= 60) 
                    cout << "Ending hour must be a number less than 60.\n";
                else
                    goto jump_recur;
                break;
            
            case 4:
                if(type == 'w' && mark[4] < 1 && mark[4] > 7)
                    cout << "Event weekday must be a number between 1 to 7.\n";
                else if((type == 'm' || type == 'y') && mark[4] <= 0)
                    cout << "Event date must be a number more than 0.\n";
                else 
                    goto jump_recur;
                break;

            case 5:
                if(type == 'y' && mark[5] < 1970)
                    cout << "Event month must be a number more than 0.\n";
                else
                    goto jump_recur;
                break;
            }
            stage = i;
            for(int j = i; j < 6; j++) mark[j] = INT_MIN;
            jump_recur: ;
        }

        switch(type){
        case 'd':
            if(stage > 3) return;
            break;

        case 'w':
        case 'm':
            if(stage > 4) return;
            break;

        case 'y':
            if(stage > 5) return;
        }
    }
}

// converting to Event
Event MarkToEvent(const int mark[7]){
    tm temp;
    Event event;

    temp.tm_sec = 0;
    temp.tm_hour = mark[0];
    temp.tm_min = mark[1];
    temp.tm_mday = mark[4];
    temp.tm_mon = mark[5];
    temp.tm_year = mark[6];
    temp.tm_mon--;
    temp.tm_year -= 1900;
    event.begin = mktime(&temp);

    if(mark[0] + mark[1]/60. > mark[2] + mark[3]/60.) temp.tm_mday += 1;
    temp.tm_hour = mark[2];
    temp.tm_min = mark[3];
    event.end = mktime(&temp);

    return event;
}

// converting to Recur
Recur MarkToRecur(const int mark[6], const char type){
    time_t currentTime = time(0);
    tm temp = *localtime(&currentTime);
    Recur recur;

    recur.type = type;
    temp.tm_sec = 0;
    temp.tm_hour = mark[0];
    temp.tm_min = mark[1];
    if(type != 'd' && type != 'w') temp.tm_mday = mark[4];

    else if(type == 'w'){
        int weekday = mark[4] - 1;
        int diff = temp.tm_wday - weekday;
        temp.tm_mday -= diff;
    }

    if(type == 'y'){
        temp.tm_mon = mark[5];
        temp.tm_mon--;
    }

    recur.begin = mktime(&temp);

    temp.tm_hour = mark[2];
    temp.tm_min = mark[3];
    recur.end = mktime(&temp);
    recur.update();

    return recur;
}

char cinType(){
    string element;
    char type;

    cout << "| Enter recursion type |\n\n";
    cout << "| For daily      Enter 1 |\n";
    cout << "| For weekly     Enter 2 |\n";
    cout << "| For monthly    Enter 3 |\n";
    cout << "| For yearly     Enter 4 |\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Your input : ";
    while(getline(cin,element)){
        if(element == "1")
            return 'd';
        else if(element == "2")
            return 'w';
        else if(element == "3")
            return 'm';
        else if(element == "4")
            return 'y';
        else
            cout << "\nInvalid input Please try again: ";
    }
}

string cinName(){
    string element;
    cout << "|   Enter name   | : ";
    getline(cin, element);
    return element;
}

string cinAuthor(){
    string element;
    cout << "|  Enter author  | : ";
    getline(cin, element);
    return element;
}

string cinLocation(){
    string element;
    cout << "| Enter location | : ";
    getline(cin, element);
    return element;
}

bool isConflicted(const Event& test, const vector<Event> events){
    return any_of(events.begin(),events.end(),
    [&test](Event sieve) {return (max(test.begin,sieve.begin) <= min(test.end,sieve.end));});
}

bool isConflicted(const Recur& test, const vector<Recur> recurs){
    return any_of(recurs.begin(),recurs.end(),
    [&test](Recur sieve) {return (max(test.begin,sieve.begin) <= min(test.end,sieve.end));});
}