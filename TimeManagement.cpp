#include "events.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <ctime>

using namespace std;

// global Events and Periodical events
vector<Event> events;
vector<Recur> recurs;

// import and write to .txt files
void importEvents(){
    ifstream source("events.txt");
    if(source.fail()) return;
    
    string line;
    Event temp;
    while(getline(source,line)){
        sscanf(line.c_str(), "%lld %lld", &temp.begin, &temp.end);

        getline(source,line);
        temp.name = line;

        getline(source,line);
        temp.author = line;

        getline(source,line);
        temp.location = line;

        events.push_back(temp);
    }
}

void importRecurs(){
    ifstream source("recurs.txt");
    if(source.fail()) return;
    
    string line;
    Recur temp;
    while(getline(source,line)){
        sscanf(line.c_str(), "%lld %lld %c", &temp.begin, &temp.end, &temp.type);

        getline(source,line);
        temp.name = line;

        getline(source,line);
        temp.author = line;

        getline(source,line);
        temp.location = line;

        recurs.push_back(temp);
    }
}

void updateEvents(){
    ofstream dest("events.txt");
    for(unsigned int i = 0; i < events.size(); i++){
        dest << events[i].begin << ' ';
        dest << events[i].end << '\n';
        dest << events[i].name << '\n';
        dest << events[i].author << '\n';
        dest << events[i].location << '\n';
    }
    dest.close();
}

void updateRecurs(){
    ofstream dest("recurs.txt");
    for(unsigned int i = 0; i < recurs.size(); i++){
        dest << recurs[i].begin << ' ';
        dest << recurs[i].end << ' ';
        dest << recurs[i].type << '\n';
        dest << recurs[i].name << '\n';
        dest << recurs[i].author << '\n';
        dest << recurs[i].location << '\n';
    }
    dest.close();
}

// miscellaneous functions, newer functions will be added here
string strPeriod(Event period){
    tm temp[2] = {*localtime(&period.begin),*localtime(&period.end)};

    string format[2] = {"%d/%m/%Y  from %H:%M to ","%H:%M"};
    int size = format[0].size() + format[1].size() + 1;
    char buffer[80];

    strftime(buffer                   ,size,format[0].c_str(),&temp[0]);
    strftime(buffer+format[0].size()+2,size,format[1].c_str(),&temp[1]);

    string result = buffer;
    return result;
}

void printEvent(int i){
    cout << left
        << "[" << i+1 << "] : " 
        << strPeriod(events[i]) << "    "
        << "named " << setw(15) << events[i].name
        << "authored by " << setw(15) << events[i].author
        << "at " << events[i].location << '\n';
}

void printRecur(int i){
    tm temp[2] = {*localtime(&recurs[i].begin), *localtime(&recurs[i].end)};

    char buffer[3][20];

    cout << "[" << i+1 << "] : Every ";
    switch(recurs[i].type){
    case 'd':
        strftime(buffer[0],20,"day ",NULL);
        break;
    
    case 'w':
        strftime(buffer[0],20,"%A ",&temp[0]);
        break;
    
    case 'm':
        strftime(buffer[0],20,"month on day %dth",&temp[0]);
        if(temp[0].tm_mday % 10 == 1 && temp[0].tm_mday != 11){
            buffer[0][15] = 's';
            buffer[0][16] = 't';
        }else if(temp[0].tm_mday % 10 == 2 && temp[0].tm_mday != 12){
            buffer[0][15] = 'n';
            buffer[0][16] = 'd';
        }
        break;

    case 'y':
        strftime(buffer[0],20,"%B the %dth",&temp[0]);
        char *p = find(buffer[0], buffer[0]+20, '\0');
        if(temp[0].tm_mday % 10 == 1 && temp[0].tm_mday != 11){
            *(p-2) = 's';
            *(p-1) = 't';
        }else if(temp[0].tm_mday % 10 == 2 && temp[0].tm_mday != 12){
            *(p-2) = 'n';
            *(p-1) = 'd';
        }
        break;
    }

    strftime(buffer[1],20,"from %H:%M ",&temp[0]);
    strftime(buffer[2],20,"to %H:%M",&temp[1]);

    cout << left << setw(20) << buffer[0]
        << buffer[1]
        << buffer[2] << "    "
        << "named " << setw(15) << recurs[i].name
        << "authored by " << setw(15) << recurs[i].author
        << "at " << recurs[i].location << '\n';
}

void sortEvent(){
    sort(events.begin(), events.end(), 
        [](const Event &d1, const Event &d2){return difftime(d2.begin,d1.begin) > 0;});
}

void sortRecur(){
    sort(recurs.begin(), recurs.end(), 
        [](const Recur &d1, const Recur &d2){return difftime(d2.begin,d1.begin) > 0;});
}

//Converting a String to Uppercase
string toupperString(string x)
{
    for_each(x.begin(), x.end(), [](char & c) 
    {
        c = ::toupper(c);
    });
    return x;
}

//Returning index of the maximum value of an array
int maxIdx(int arr[], int size){
    int *max = max_element(arr, arr+size);
    if(count(arr, arr+size, *max) > 1) return size;
    else return (max-arr);
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
    /*
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
    */

    importEvents();
    importRecurs();

    for(unsigned int i = 0; i < recurs.size(); i++) {recurs[i].update();}

    sortEvent();
    sortRecur();

    system("CLS");
    mainMenu();
    system("CLS");

    return 0;

}

void mainMenu(){
    string cmd;
    bool justEnter = true;
    while(true){
        if(justEnter){
            cout << "| To view events             Enter 1    |\n";
            cout << "| To view periodic events    Enter 2    |\n";
            cout << "| To exit                    Enter exit |\n";
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

        }else if(cmd == "EXIT"){
            return;

        }else{
            cout << "\nInvalid input Please try again: ";
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
            cout << "\n| To return to previous page     Enter return |\n";
            cout <<   "| To add a new event             Enter new    |\n";
            cout <<   "| To delete all passed events    Enter pass   |\n";
            if(events.size() != 0) 
                cout << "| To select an event             Enter its index NO. |\n";
            cout << "-----------------------------------------------------------------------\n";
            cout << "Your input : ";
            justEnter = false;
        }

        getline(cin, cmd);
        cmd = toupperString(cmd);
        int number = atoi(cmd.c_str());
        if(!is_number(cmd)) number = 0;
        if(number >= 1 && number <= events.size()){
            system("CLS");
            interactEvent(atoi(cmd.c_str())-1);
            justEnter = true;
        
        }else if(cmd == "NEW"){
            system("CLS");
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
            cout << "\nInvalid input Please try again: ";
        }
        sortEvent();
        updateEvents();
    }
}

void addEvent(){
    Event adding;
    int mark[7] = {INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN};
    //begin hr, begin min, end hr, end min, date, month, year
    int stage;

    cinMark(mark, stage);

    adding = MarkToEvent(mark);

    if(isConflicted(adding,events) || isConflicted(adding,recurs)){
        string ensure;
        cout << "\nThis event is conflicted with others. Are you sure to continue?\n";
        cout << "| For not continuing    Enter no      |\n";
        cout << "| For continuing        Enter any key |\n";
        cout << "-----------------------------------------------------------------------\n";
        getline(cin,ensure);
        ensure = toupperString(ensure);
        
        if(ensure == "NO") return;
    }

    adding.name = cinName();
    adding.author = cinAuthor();
    adding.location = cinLocation();

    events.push_back(adding);
}

void interactEvent(int i){
    string cmd;
    cout << "| Selected event |\n";
    printEvent(i);
    cout << "\n| To return to previous page    Enter return   |\n";
    cout <<   "| To edit selected event        Enter edit     |\n";
    cout <<   "| To delete selected event      Enter del      |\n";
    cout <<   "| To vote the time period       Enter votetime |\n";
    cout <<   "| To vote the location          Enter voteloc  |\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Your input : ";

    while(getline(cin,cmd)){
        cmd = toupperString(cmd);
        if(cmd == "EDIT"){
            system("CLS");
            editEvent(i);
            system("CLS");
            cout << "The selected event has been edited.\n";
            cout << "-----------------------------------------------------------------------\n\n";
            break;

        }else if(cmd == "DEL"){
            deleteEvent(i);
            system("CLS");
            cout << "The selected event has been deleted.\n";
            cout << "-----------------------------------------------------------------------\n\n";
            break;
        
        }else if(cmd == "VOTETIME" || cmd == "VOTE TIME"){
            system("CLS");
            voteTime(i);
            system("CLS");
            cout << "\nThe selected event has been voted.\n";
            cout << "-----------------------------------------------------------------------\n\n";
            break;

        }else if(cmd == "VOTELOC" || cmd == "VOTE LOC" || cmd == "VOTELOCATION" || cmd == "VOTE LOCATION"){
            system("CLS");
            voteLocation(i);
            system("CLS");
            cout << "\nThe selected event has been voted.\n";
            cout << "-----------------------------------------------------------------------\n\n";
            break;

        }else if(cmd == "RETURN"){
            system("CLS");
            break;
        }else{
            cout << "\nInvalid input Please try again: ";
        }
    }
}

void editEvent(int i){

    int number ;
    string str;
    cout << "| Editing event |\n";
    printEvent(i);
    cout << '\n';
    cout << "| To edit time period    Press 1 |" << endl ;
    cout << "| To edit name           Press 2 |" << endl ;
    cout << "| To edit author         Press 3 |" << endl ;
    cout << "| To edit location       Press 4 |" << endl ;
    cout << "-----------------------------------------------------------------------\n";
    cout << "Press number: "  ;
    while(getline(cin,str)){
        number = atoi(str.c_str());
        if(!is_number(str)) number = 0;
        if(number >= 1 && number <= 4) break;
        else cout << "Invalid input Please try again: " ;
    }

    int mark[7] = {INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN};
    //begin hr, begin min, end hr, end min, date, month, year
    int stage;
    Event editing;

    switch(number){
        case 1 :
            cout << "\n\n";
            cinMark(mark,stage);

            editing = MarkToEvent(mark);

            if(isConflicted(editing,events) || isConflicted(editing,recurs)){
                string ensure;
                cout << "\nThis event is conflicted with others. Are you sure to continue?\n";
                cout << "| For not continuing    Enter no      |\n";
                cout << "| For continuing        Enter any key |\n";
                cout << "-----------------------------------------------------------------------\n";
                getline(cin,ensure);
                ensure = toupperString(ensure);
                
                if(ensure == "NO") return;
            }

            events[i].begin = editing.begin;
            events[i].end = editing.end;
            break;

        case 2 :
            cout << "Enter event name that you want to edit: " ;
            getline(cin,str) ;
            events[i].name = str;
            break ;
        case 3 :
            cout << "Enter event author that you want to edit: " ;
            getline(cin,str) ;
            events[i].author = str;
            break ;
        case 4 :
            cout << "Enter event location that you want to edit: " ;
            getline(cin,str) ;
            events[i].location = str;
            break ;
    }
}

void deleteEvent(int i){
    events.erase(events.begin()+i) ;
}

void voteTime(int j){
    vector<int> scorevotetime ;
    vector<Event> periods = {events[j]};

    int number,numchoice ;
    string numchoice_str ;
    Event period;
    cout << "--------------  Vote Time --------------" << endl ;
    printEvent(j);
    cout << "\n" ;
    //สร้างchoiceโดยสามารถสร้างกี่choiceก็ได้ 
        
    cout << "How many choices you want to create? --> " ; 
    while(getline(cin,numchoice_str)){
        numchoice = atoi(numchoice_str.c_str());
        if(!is_number(numchoice_str)) numchoice = 0;
        if(numchoice <= 0){
            cout << "Invalid input, Please try again: ";
        }else{
            break;
        }
    }

    cout << "Please enter periods that you want to vote" << endl;
    int mark[7], stage;
    for(int i = 1 ;i <= numchoice;i++){
        for(int k = 0; k < i; k++) cout << "choice " << k+1 << ": "  << strPeriod(periods[k]) << endl ;
        cout << "choice " << i+1 << ": \n\n";
        stage = 0;
        fill(mark, mark+7, INT_MIN);
        cinMark(mark, stage);
        period = MarkToEvent(mark);

        if(isConflicted(period,events)){
            string ensure;
            cout << "\nThis event is conflicted with others. Are you sure to continue?\n";
            cout << "| For not continuing    Enter no      |\n";
            cout << "| For continuing        Enter any key |\n";
            cout << "-----------------------------------------------------------------------\n";
            getline(cin,ensure);
            ensure = toupperString(ensure);
            
            system("CLS");
            if(ensure != "NO") periods.push_back(period);
            else {cout << "The added period discarded." << endl ; i--;}
        }else periods.push_back(period);
    }
    //เลือกchoice
    system("CLS");
    jump_votetime: ;
    cout << "| -----------------------------------------  |" << endl ;
    for(int i = 0 ;i < periods.size();i++){
        cout << "| choice " << i+1 << " = " << left << setw(32) << strPeriod(periods[i]) << "|" << endl   ;
    }
    cout << "| -----------------------------------------  |" << endl << endl ;
    cout << "----Please enter the number of votes---- " << endl ;  
    do{
        cout << "The number that you choose: " ;  
        getline(cin,numchoice_str);
        number = atoi(numchoice_str.c_str());
        if(!is_number(numchoice_str)) number = 0;
        if(number <= 0){
            cout << "Invalid input, Please try again" << endl ;
        }else break;
    }while(true);

    for(int i = 0; i < number; i++){
        system("CLS");
        cout << "| -----------------------------------------  |" << endl ;
        cout << "| Please choose one of the following choices |" << endl ;
        for(int i = 0 ;i < periods.size();i++){
            cout << "| choice " << i+1 << " = " << left << setw(32) << strPeriod(periods[i]) << "|" << endl   ;
        }
        cout << "| -----------------------------------------  |" << endl << endl ;
        cout << "----Please enter the number for voting---- " << endl ;  
        do{
            cout << "The chosen period: " ;
            getline(cin,numchoice_str);
            numchoice = atoi(numchoice_str.c_str());
            if(!is_number(numchoice_str)) numchoice = 0;
            if(numchoice > periods.size() || numchoice <= 0){
                cout << "Invalid input, Please try again" << endl ;
            }else{
                scorevotetime.push_back(numchoice) ;
                break ;
            }
        }while(true);
    }

    system("CLS");
    cout << "-------------------------------------------" << endl ;
    cout << "\t\tVote Results" << endl ;
    int *votes = new int(periods.size());
    for(int i = 0;i < periods.size();i++){
        cout << "choice " << i+1 << " got " << count(scorevotetime.begin(),scorevotetime.end(),i+1) << endl ;
        votes[i] = count(scorevotetime.begin(),scorevotetime.end(),i+1);
    }
    int idx = maxIdx(votes, periods.size());
    if(idx == periods.size()){
        cout << "There is a tie, Please vote again" << endl << endl ;
        scorevotetime.clear();
        fill(votes, votes+periods.size(), 0);
        goto jump_votetime;
    }
    else{
        cout << "\nThe location with the highest votes is: " << endl ;
        cout << "| choice " << idx+1 << " = " << left << setw(32) << strPeriod(periods[idx]) << "|" << endl   ;
        cout << "-------------------------------------------" << endl ;
        events[j].begin = periods[idx].begin;
        events[j].end = periods[idx].end;
        system("pause");
        delete [] votes;
        return;
    }
}

void voteLocation(int j){
    vector<int> scorevoteloc ;
    vector<string> locations = {events[j].location} ;

    int number,numchoice ;
    string choice,location,letter,numchoice_str ;
    cout << "-----------  Vote Location --------------" << endl ;
    printEvent(j);
    cout << "\n" ;
    //สร้างchoiceโดยสามารถสร้างกี่choiceก็ได้ 
        
    cout << "How many choices you want to create? --> " ; 
    while(getline(cin,numchoice_str)){
        numchoice = atoi(numchoice_str.c_str());
        if(!is_number(numchoice_str)) numchoice = 0;
        if(numchoice <= 0){
            cout << "Invalid input, Please try again: ";
        }else{
            break;
        }
    }

    cout << "Please enter locations that you want to vote" << endl;
    cout << "choice 1: " << locations[0] << endl ;
    for(int i = 1 ;i <= numchoice;i++){
        cout << "choice " << i+1 << ": "  ;
        getline(cin,location);
        locations.push_back(location) ;
    }
    
    //เลือกchoice
    system("CLS");
    jump_voteloc: ;
    cout << "| -----------------------------------------  |" << endl ;
    for(int i = 0 ;i < locations.size();i++){
        cout << "| choice " << i+1 << " = " << left << setw(32) << locations[i] << "|" << endl   ;
    }
    cout << "| -----------------------------------------  |" << endl << endl ;
    cout << "----Please enter the number of votes---- " << endl ;  
    do{
        cout << "The number that you choose: " ;  
        getline(cin,numchoice_str);
        number = atoi(numchoice_str.c_str());
        if(!is_number(numchoice_str)) number = 0;
        if(number <= 0){
            cout << "Invalid input, Please try again" << endl ;
        }else break;
    }while(true);

    for(int i = 0; i < number; i++){
        system("CLS");
        cout << "| -----------------------------------------  |" << endl ;
        cout << "| Please choose one of the following choices |" << endl ;
        for(int i = 0 ;i < locations.size();i++){
            cout << "| choice " << i+1 << " = " << left << setw(32) << locations[i] << "|" << endl   ;
        }
        cout << "| -----------------------------------------  |" << endl << endl ;
        cout << "----Please enter the number for voting---- " << endl ;  
        do{
            cout << "The chosen location: " ;
            getline(cin,numchoice_str);
            numchoice = atoi(numchoice_str.c_str());
            if(!is_number(numchoice_str)) numchoice = 0;
            if(numchoice > locations.size() || numchoice <= 0){
                cout << "Invalid input, Please try again" << endl ;
            }else{
                scorevoteloc.push_back(numchoice) ;
                break ;
            }
        }while(true);
    }

    system("CLS");
    cout << "-------------------------------------------" << endl ;
    cout << "\t\tVote Results" << endl ;
    int *votes = new int(locations.size());
    for(int i = 0;i < locations.size();i++){
        cout << "choice " << i+1 << " got " << count(scorevoteloc.begin(),scorevoteloc.end(),i+1) << endl ;
        votes[i] = count(scorevoteloc.begin(),scorevoteloc.end(),i+1);
    }
    int idx = maxIdx(votes, locations.size());
    if(idx == locations.size()){
        cout << "There is a tie, Please vote again" << endl << endl ;
        scorevoteloc.clear();
        fill(votes, votes+locations.size(), 0);
        goto jump_voteloc;
    }
    else{
        cout << "\nThe location with the highest votes is: " << endl ;
        cout << "| choice " << idx+1 << " = " << left << setw(32) << locations[idx] << "|" << endl   ;
        cout << "-------------------------------------------" << endl ;
        events[j].location = locations[idx];
        system("pause");
        delete [] votes;
        return;
    }
}

void passEvent(){
    time_t currentTime = time(0);
    vector<Event>::iterator ptr = remove_if(events.begin(),events.end(),
        [&currentTime](Event test) {return (difftime(currentTime, test.end) > 0);});
    events.erase(ptr,events.end());
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

            cout << "\n| To return to previous page     Enter return |\n";
            cout <<   "| To add a new periodic event    Enter new    |\n";
            if(recurs.size() != 0) 
                cout << "| To select an event             Enter its index NO. |\n";
            cout << "-----------------------------------------------------------------------\n";
            cout << "Your input : ";
            justEnter = false;
        }

        getline(cin, cmd);
        cmd = toupperString(cmd);
        int number = atoi(cmd.c_str());
        if(!is_number(cmd)) number = 0;
        if(number >= 1 && number <= recurs.size()){
            system("CLS");
            interactRecur(atoi(cmd.c_str())-1);
            justEnter = true;
        
        }else if(cmd == "NEW"){
            system("CLS");
            addRecur();
            system("CLS");
            cout << "Adding new periodic event completed\n";
            cout << "-----------------------------------------------------------------------\n\n";
            justEnter = true;
        
        }else if(cmd == "RETURN"){
            return;
        }else{
            cout << "\nInvalid input Please try again: ";
        }
        sortRecur();
        updateRecurs();
    }
}

void addRecur(){
    Recur adding;

    adding.type = cinType();

    int stage;
    int mark[6] = {INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN};
    //begin hr, begin min, end hr, end min, date, month
    cout << '\n';

    cinMark(mark,stage,adding.type);

    adding = MarkToRecur(mark,adding.type);

    if(isConflicted(adding,recurs)){
        string ensure;
        cout << "\nThis event is conflicted with others. Are you sure to continue?\n";
        cout << "| For not continuing    Enter no      |\n";
        cout << "| For continuing        Enter any key |\n";
        cout << "-----------------------------------------------------------------------\n";
        getline(cin,ensure);
        ensure = toupperString(ensure);
        
        if(ensure == "NO") return;
    }

    adding.name = cinName();
    adding.author = cinAuthor();
    adding.location = cinLocation();

    recurs.push_back(adding);
}

void interactRecur(int i){
    string cmd;
    cout << "| Selected periodic event |\n";
    printRecur(i);
    cout << '\n';
    cout << "| To return to previous page               Enter return |\n";
    cout << "| To edit the selected periodic event      Enter edit   |\n";
    cout << "| To delete the selected periodic event    Enter del    |\n";
    cout << "-----------------------------------------------------------------------\n";
    cout << "Your input : ";

    while(getline(cin,cmd)){
        cmd = toupperString(cmd);
        if(cmd == "EDIT"){
            system("CLS");
            editRecur(i);
            system("CLS");
            cout << "| The selected event has been edited. |\n";
            cout << "-----------------------------------------------------------------------\n\n";
            break;

        }else if(cmd == "DEL"){
            deleteRecur(i);
            system("CLS");
            cout << "| The selected event has been deleted. |\n";
            cout << "-----------------------------------------------------------------------\n\n";
            break;

        }else if(cmd == "RETURN"){
            system("CLS");
            break;
        }else{
            cout << "\nInvalid input Please try again: ";
        }
    }
}

void editRecur(int i){
    
    int number ;
    string str;
    cout << "| Editing event |\n";
    printRecur(i);
    cout << '\n';
    cout << "| To edit time period    Press 1 |" << endl ;
    cout << "| To edit name           Press 2 |" << endl ;
    cout << "| To edit author         Press 3 |" << endl ;
    cout << "| To edit location       Press 4 |" << endl ;
    cout << "-----------------------------------------------------------------------\n";
    cout << "Press number: "  ;
    while(getline(cin,str)){
        number = atoi(str.c_str());
        if(!is_number(str)) number = 0;
        if(number >= 1 && number <= 4) break;
        else cout << "Invalid input Please try again: " ;
    }

    Recur editing;
    int stage;
    int mark[6] = {INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN,INT_MIN};
    //begin hr, begin min, end hr, end min, date, month

    switch(number){
        case 1 :
            // I literally copied this from addRecur, so it ain't much work, prof.
            editing.type = cinType();
            cout << '\n';
            cinMark(mark, stage, editing.type);

            editing = MarkToRecur(mark, editing.type);

            if(isConflicted(editing,recurs)){
                string ensure;
                cout << "\nThis event is conflicted with others. Are you sure to continue?\n";
                cout << "| For not continuing    Enter no      |\n";
                cout << "| For continuing        Enter any key |\n";
                cout << "-----------------------------------------------------------------------\n";
                getline(cin,ensure);
                ensure = toupperString(ensure);
                
                if(ensure == "NO") return;
            }

            recurs[i].type = editing.type;
            recurs[i].begin = editing.begin;
            recurs[i].end = editing.end;
            break;

        case 2 :
            cout << "Enter event name that you want to edit: " ;
            getline(cin,str) ;
            recurs[i].name = str;
            break ;
        case 3 :
            cout << "Enter event author that you want to edit: " ;
            getline(cin,str) ;
            recurs[i].author = str;
            break ;
        case 4 :
            cout << "Enter event location that you want to edit: " ;
            getline(cin,str) ;
            recurs[i].location = str;
            break ;
    }
}

void deleteRecur(int i){
    recurs.erase(recurs.begin()+i) ;
}