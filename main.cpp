// Library.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Book.h"
#include "BooksDataBase.h"
#include "SerialPort.h"
#include <string.h>
#include <cctype>
#include <algorithm>


using std::cout;
using std::cin;
using std::endl;
using std::string;

char port_slave[5];
char* c=strcpy(port_slave, "COM4");



char output[MAX_DATA_LENGTH];
char incoming[MAX_DATA_LENGTH];


string tags[27] = {"B2000A", "B20006", "B20004", "B20009", "B20007", "B20005", "B20008", "B20003", "B20001", "B20002", "B20010", "B20020",
                   "B20030", "B20040", "B20050", "B20060", "B20070", "B20080", "B20090", "B200A0", "B200B0", "B200C0", "B200D0", "B200E0",
                   "B200F0", "B20100", "B20200"};
string books[27] = {"wave generation", "GSM", "reference data", "electronics tech", "osnovi izmereni", "circuit analysis",
                    "theory and design", "isto4niki", "intro 1", "intro 2", "microelectronics", "communication systems",
                    "electromagnetic transmission", "standard mathematical", "circuits devices and systems", "statistics toolbox", "introduction to electronics",
                    "logic design hebrew", "fundamentals of pulse", "data transmission", "notes on analog", "communications blockset", "notes on digital",
                    "electrical fundamentals direct", "electrical fundamentals alternating", "basic theory and application", "logic design hebrew second"};

int hist[27] = {0};

bool isSubstring(string s1, char* s2);
void check_tags(char* output);
void print_hist();
void print_output(char* output);

int main(int argc, char *argv[]) {

    SerialPort arduino_slave(port_slave);
    // SerialPort arduino_valeri(port_valeri);
    if (arduino_slave.isConnected()) {
        cout << "Connection is Established for slave" << endl;
    } else {
        cout << "Error in port name for slave" << endl;
    }
    char strin[700] = "";
    BooksDataBase *new_db = new BooksDataBase();
    new_db->read_record("../DataBase/BookSAmples.csv");
    if (!new_db) {
        return -1;
    }
    char command[28] = {'k','n','k','n','k','n','k','n','k','n','k','n','k','n','k','n','k','n','k','n','k','n','k','n','k','n','h','f'};
    int command_index=0;
    while(arduino_slave.isConnected() ){

        string command;
        //----------------slave part-----------------------------------
        cin>>command;
        if(command[command_index]=='0'){
            return 0;
        }
        if(command[command_index] == 'f'){
            for(auto book : *new_db->get_books_map()){
                book.second->resetNumOfLocationsToZero();
            }
            print_hist();
            break;
        }
        if(command[command_index] == 'k'){
            new_db->getBooks();
            string db_books = "";
            char *charArray_slave = new char[command.size() +1];
            copy(command.begin(), command.end(), charArray_slave);
            charArray_slave[command.size()]='\0';
            for(int i=0; i<15; i++){
                arduino_slave.writeSerialPort(charArray_slave,command.size());

                Sleep(600);

                arduino_slave.readSerialPort(output, MAX_DATA_LENGTH);

                print_output(output);

                check_tags(output);
                string output_str(output);
                output_str.erase(std::remove_if(output_str.begin(),
                                                output_str.end(),
                                              [](unsigned char x){return std::isspace(x);}),output_str.end());
                std::string delimiter = "start";
                if (output_str.find(delimiter) != string::npos){
                    std::size_t pos = output_str.find(delimiter);
                    std::string location_and_tag = output_str.substr (pos + delimiter.length());
                    std::size_t semi_colon_pos = location_and_tag.find(";");
                    std::string location = location_and_tag.substr(0, semi_colon_pos);
                    std::string tag_and_end = location_and_tag.substr(semi_colon_pos + 1);
                    std::size_t end_pos = tag_and_end.find("end");
                    std::string tag = tag_and_end.substr(0, end_pos);
                    std::size_t comma_pos = location.find(",");
                    std::string x = location.substr(0, comma_pos);
                    std::string y = location.substr(comma_pos+1, semi_colon_pos);
                    cout << "x: " << x << endl;
                    cout << "y: " << y << endl;
                    cout << "read tag: " << tag << endl;
                    fstream new_file;
                    new_file.open("../DataBase/tags.txt",ios::in); //open a file to perform read operation using file object
                    if (new_file.is_open()){   //checking whether the file is open
                        string db_tag;
                        while(getline(new_file, db_tag)){ //read data from file object and put it into string.
                            if (tag.find(db_tag) != string::npos){
                                new_db->updateBook(db_tag, x, y);
                                cout << "updating tag: " << db_tag << " with location: " << x << "," << y << "\n"; //print the data of the string
                            }
                        }
                        new_file.close(); //close the file object.
                    }
                }
                memset(output, 0, sizeof(output));

            }
            remove( "../DataBase/tags.txt" );
        }

        char *charArray_slave = new char[1+1];
        charArray_slave[0] = command[command_index];
        copy(command.begin(), command.end(), charArray_slave);
        charArray_slave[command.size()]='\0';

        arduino_slave.writeSerialPort(charArray_slave,command.size());
        arduino_slave.readSerialPort(output, MAX_DATA_LENGTH);

        check_tags(output);

        memset(output, 0, sizeof(output));
        delete [] charArray_slave;
        command.clear();
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

bool isSubstring(string s1, char* s2)
{
    int M = s1.length();
    int N = (int)strlen(s2);

    /* A loop to slide pat[] one by one */
    for (int i = 0; i <= N - M; i++) {
        int j;

        /* For current index i, check for
 pattern match */
        for (j = 0; j < M; j++)
            if (s2[i + j] != s1[j])
                break;

        if (j == M)
            return true;
    }

    return false;
}

void check_tags(char* output){
    for(int i=0; i<27; i++){
        if(isSubstring(tags[i], output)) {
            hist[i]++;
        }
    }

}

void clear_hist(){
    for(int i=0; i<27; i++){
        hist[i] = 0;
    }
}

void print_hist(){
    for(int i=0; i<27; i++){
        cout<<hist[i];
        cout<<' ';
        cout<<books[i]<<endl;
    }

    for(int i=0; i<27; i++){
        hist[i] = 0;
    }
}

void print_output(char* output){
    for(int i=0; i<MAX_DATA_LENGTH; i++){
        cout<<output[i];
    }
    cout<<endl;
}