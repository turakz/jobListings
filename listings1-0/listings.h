#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cstring>
#include <vector>
#include <fstream>
#include <algorithm>
#include <ncurses.h>
#include <boost/algorithm/string.hpp>

using namespace std;

class Listing{

    private:

        string company;
        string position;
        string job;
        string status;
    

    public:

        //constructors
        Listing()
            :company(""), position(""), job(""), status(""){}
        Listing(string c, string p, string j, string s)
            :company(c), position(p), job(j), status(s){}

        //getters
        string getCompany(){
            return company;
        }
        string getPosition(){
            return position;
        }
        string getJob(){
            return job;
        }
        string getStatus(){
            return status;
        }

        //setters
        void setCompany(string s){
            boost::algorithm::to_upper(s);
            company = s;
        }
        void setPosition(string s){
            boost::algorithm::to_upper(s);
            position = s;
        }
        void setJob(string s){
            boost::algorithm::to_upper(s);
            job = s;
        }
        void setStatus(string s){
            boost::algorithm::to_upper(s);
            status = s;
        }

        //friends and  overloaded operators
        friend ostream& operator<<(ostream& os, Listing listing){
        
            int w = 10;
            os << "Company  :" << setw(listing.getCompany().size() + w) << listing.getCompany() << "\n"
               << "Position :" << setw(listing.getPosition().size() + w) << listing.getPosition() << "\n"
               << "Job      :" << setw(listing.getJob().size() + w) << listing.getJob() << "\n"
               << "Status   :" << setw(listing.getStatus().size() + w) << listing.getStatus() << "\n";

            return os;

        }

        friend bool operator <(Listing& a, Listing& b){
            return (a.getCompany() < b.getCompany());
        }


};

//aux functions
void inFile(vector<Listing>& v);
void outFile(vector<Listing>& v);
void displayMenu();
int displayPrompt();
void displayListings(const vector<Listing>& listings);
void displayListing(const vector<Listing>& listings);
bool addListing(vector<Listing>& listings);
bool removeListing(vector<Listing>& listings);
bool findListings(vector<Listing>& listings);
