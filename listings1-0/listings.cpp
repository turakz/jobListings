#include "listings.h"

void inFile(vector<Listing>& v){

    /*instantiates Listing objects the program can operate on*/
   
    if (v.size() > 0){
        v.erase(v.begin(), v.end());
    }

    //open file
    ifstream ifs("listings.txt");
    //does file exist?
    if (!ifs){
        cerr << "inFile() - input filestream corrupted or not found\n";
    }
    else{
        string input = "", company = "", job = "", type = "", status = "";
        int field = 0; 
        //force filestream to try and read passed last line (in case a blank line does not come after last line of file)
        while(!ifs.eof() && ifs.good()){
            getline(ifs, input);
            if (input.empty()){
                field = 0;
                boost::algorithm::to_upper(company);
                boost::algorithm::to_upper(job);
                boost::algorithm::to_upper(type);
                boost::algorithm::to_upper(status);
                Listing listing(company, job, type, status);
                v.push_back(listing);
            }
            else{
                if (field == 0){
                    company = input;
                }
                else if (field == 1){
                    job = input;
                }
                else if (field == 2){
                    type = input;
                }
                else if (field == 3){
                    status = input;
                }
                field++;
            }
        }
    }

}

void outFile(vector<Listing>& v){

    /*dumps listings to a file so that information can persist*/

    ofstream ofs("listings.txt");
    
    if (!ofs){
        cerr << "error: outFile() - output filestream corrupt\n";
    }
    else{
        unsigned int count = 0;
        for (Listing& listing : v){
            if (count == v.size()-1){
                ofs << listing.getCompany() << "\n"
                    << listing.getJob() << "\n"
                    << listing.getPosition() << "\n"
                    << listing.getStatus();
            }
            else{
                ofs << listing.getCompany() << "\n"
                    << listing.getJob() << "\n"
                    << listing.getPosition() << "\n"
                    << listing.getStatus() << "\n" << endl;
            }
            ++count;
        }
    }

}

void displayMenu(){

    vector<string> menu = {
        
        "Load Applications         ",
        "Save Applications         ",
        "Add Application           ",
        "Remove Application        ",
        "Find Application(s)       ",
        "Print Current Applications",
        "Exit Program              ",
    
    };

    //get center position via ncurses.h globals
    int y = (LINES - 1)/2;
    int x = (COLS)/2;
    string tmp_msg = "Job Application Tracker v1.0";
    mvprintw(y, x - (tmp_msg.size()/2), tmp_msg.c_str());
    y+=2;
    for (unsigned int i = 0; i < menu.size(); i++){
        mvprintw(y, (x - (menu[i].size()/2)), "[%d]  -  %s", i+1, menu[i].c_str());
        ++y;
    }
    
}

int displayPrompt(){

    int y = LINES-1;
    string prompt = "[input]: ";
    mvprintw(y, 0, "%s", prompt.c_str());
    
    return prompt.size();

}

void displayListings(const vector<Listing>& listings){

    /*prints contents of listings and keeps track of how it looks on screen*/

    if(listings.empty()){
        //consider making youre own error msg function
        mvprintw(LINES - 1, 0, "error: database is empty");
        return; 
    }
    move(0, 0);
    int linecount = 0;
    unsigned int i = 0;
    for (Listing l : listings){
        //we've exceeded screen resolution
        if (linecount > LINES - 6){
            mvprintw(LINES - 1, 0, "press enter for MORE...");
            getch();
            linecount = 0;
            clear();
            refresh();
        }
        if (i == listings.size()-1){
            printw("Company : %s\n", l.getCompany().c_str());
            printw("Position: %s\n", l.getPosition().c_str());
            printw("Job     : %s\n", l.getJob().c_str());
            printw("Status  : %s", l.getStatus().c_str());
            mvprintw(LINES - 1, 0, "END of listings, press ENTER to return to MENU...");
        }
        else{
            printw("Company : %s\n", l.getCompany().c_str());
            printw("Position: %s\n", l.getPosition().c_str());
            printw("Job     : %s\n", l.getJob().c_str());
            printw("Status  : %s\n\n", l.getStatus().c_str());
        }
        linecount += 5;
        ++i;
    }

}

void displayListing(Listing l){

    printw("Company : %s\n", l.getCompany().c_str());
    printw("Position: %s\n", l.getPosition().c_str());
    printw("Job     : %s\n", l.getJob().c_str());
    printw("Status  : %s\n\n", l.getStatus().c_str());

}

bool addListing(vector<Listing>& listings){

    clear();
    
    if(listings.empty()){
        return false; 
    }
    const size_t size = 100;
    char charbuffer[size];
    Listing l;
    string input_cpy = "";

    
    int n = displayPrompt();
    mvprintw(0, 0, "Please enter a COMPANY");
    mvgetstr(LINES - 1, n, charbuffer);
    input_cpy = string(charbuffer);
    l.setCompany(input_cpy);
    refresh();
    
    clear();
    n = displayPrompt();
    mvprintw(0, 0, "Please enter a POSITION");
    mvgetstr(LINES - 1, n, charbuffer);
    input_cpy = string(charbuffer);
    l.setPosition(input_cpy);
    refresh();
    
    clear();
    n = displayPrompt();
    mvprintw(0, 0, "Please enter a JOB");
    mvgetstr(LINES - 1, n, charbuffer);
    input_cpy = string(charbuffer);
    l.setJob(input_cpy);
    refresh();
    
    clear();
    n = displayPrompt();
    mvprintw(0, 0, "Please enter a STATUS");
    mvgetstr(LINES - 1, n, charbuffer);
    input_cpy = string(charbuffer);
    l.setStatus(input_cpy);
    refresh();
    
    listings.push_back(l); 
    sort(listings.begin(), listings.end());
    
    return true;

}

bool removeListing(vector<Listing>& listings){

    if (listings.empty()){
        return false;
    }
    
    clear();
    int x = 0, y = 0;
    mvprintw(y, x, "Please enter a COMPANY");
    int n = displayPrompt();
    const size_t size = 100;
    char charbuffer[size];
    mvgetstr(LINES - 1, n, charbuffer);
    string local_company = string(charbuffer);
    boost::algorithm::to_upper(local_company);
    refresh();
    
    clear();
    n = displayPrompt();
    mvprintw(0, 0, "Please enter a JOB");
    mvgetstr(LINES - 1, n, charbuffer);
    string local_job = string(charbuffer);
    boost::algorithm::to_upper(local_job);
    refresh();


    for (unsigned int i = 0; i < listings.size(); i++){
        if ((listings[i].getCompany() == local_company)
                && (listings[i].getJob() == local_job)){
                    listings.erase(listings.begin() + i);
                    return true;
        }
    }
    return false;

}

bool findListings(vector<Listing>& listings){
    
    bool display_flag = false;
    if (listings.empty()){
        display_flag = false;
    }
    
    clear();
    const size_t size = 100;
    char charbuffer[size];
    string local_company = "", local_position = "";

    int n = displayPrompt();
    mvprintw(0, 0, "Please enter a COMPANY");
    mvgetstr(LINES - 1, n, charbuffer);
    local_company = string(charbuffer);
    boost::algorithm::to_upper(local_company);
    refresh();
    
    clear();
    int linecount = 0;
    for (unsigned int i = 0; i < listings.size(); i++){
        if (listings[i].getCompany() == local_company){
            display_flag = true;
            if (linecount > LINES - 6){
                mvprintw(LINES - 1, 0, "press enter for MORE...");
                getch();
                linecount = 0;
                clear();
                refresh();
            }
            else{
                displayListing(listings[i]); 
                linecount += 5;
            }
        }
    }
    if (display_flag){
        mvprintw(LINES - 1, 0, "END of listing(s), press ENTER to return to MENU...");
        refresh();
        getch();
        return true;
    }
    else{
        return false;
    }

}
