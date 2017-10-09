#include "listings.h"

int main(){

    initscr();
    refresh();
    keypad(stdscr, TRUE);

    vector<Listing> listings;

    bool display_flag = true;

    while(display_flag){
  
        clear();
        int x = displayPrompt(); 
        displayMenu();
        refresh();
        int ch = mvgetch(LINES - 1, x);

        switch(ch){
        
            //load listings - 1
            case 49:
                {
                    inFile(listings);
                    clear();
                    string msg = "Listings LOADED, press ENTER to return to MENU...";
                    mvprintw(LINES - 1, 0, msg.c_str());
                    refresh();
                    while(mvgetch(LINES - 1, msg.size()) != '\n'){
                        mvprintw(LINES - 1, 0, msg.c_str());
                        refresh();
                    }
                    break;
                }

            //save listings - 2
            case 50:
                {
                    outFile(listings);
                    clear();
                    string msg = "Listings SAVED, press ENTER to return to MENU...";
                    mvprintw(LINES - 1, 0, msg.c_str());
                    refresh();
                    while(mvgetch(LINES - 1, msg.size()) != '\n'){
                        mvprintw(LINES - 1, 0, msg.c_str());
                        refresh();
                    }
                    break;
                }
            //add listing - 3
            case 51:
                {
                    clear();
                    string msg = "";
                    if (addListing(listings)){
                        clear();
                        msg = "Listing ADDED, press ENTER to return to MENU...";
                        mvprintw(LINES - 1, 0, msg.c_str());
                    }
                    else{
                        clear();
                        msg = "Error: listing failed to be added, database might be empty - press ENTER to return to MENU...";
                        mvprintw(LINES - 1, 0, msg.c_str());
                    }
                    while(mvgetch(LINES - 1, msg.size()) != '\n'){
                        mvprintw(LINES - 1, 0, msg.c_str());
                        refresh();
                    }
                }
                break;

            //remove listing - 4
            case 52:
                {
                    clear();
                    string msg = "";
                    if (removeListing(listings)){
                        clear();
                        msg = "Listing has been REMOVED, press ENTER to return to MENU...";
                        mvprintw(LINES - 1, 0, msg.c_str());
                    }
                    else{
                        //consider writing an error function
                        clear();
                        msg = "Error: listing does not exist, database might be empty - press ENTER to return to MENU...";
                        mvprintw(LINES - 1, 0, msg.c_str());
                    }
                    while(mvgetch(LINES - 1, msg.size()) != '\n'){
                        mvprintw(LINES - 1, 0, msg.c_str());
                        refresh();
                    }
                }
                break;
            
            //find a listing or listings - 6
            case 53:
                {
                    clear();
                    if (!findListings(listings)){
                        clear();
                        string msg = "Error: listing(s) does not exist, database might be empty - press ENTER to return to MENU...";
                        mvprintw(LINES - 1, 0, msg.c_str());
                        while(mvgetch(LINES - 1, msg.size()) != '\n'){
                            mvprintw(LINES - 1, 0, msg.c_str());
                            refresh();
                        }
                    }

                }
                break;

            //print current listings - 7
            case 54:
                clear();
                displayListings(listings);
                refresh();
                getch();
                break;

            //exit program - 8
            case 55:
                display_flag = false;
                break;

        
        }
    }
    endwin();

    return 0;
}
