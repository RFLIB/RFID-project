#pragma once
#include "Book.h"
#include <map>
/* Standard C++ includes */
#include <stdlib.h>
#include <iostream>
#include <cassert>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "sqlite3.h"
#include <fstream>
#include <sstream>





using namespace std;

class BooksDataBase
{
public:
	BooksDataBase();
	~BooksDataBase();

	/*
	@requires: every book insert on 0,0 location
	@affect: insert new book to the the map with key of rfid and value of Book*
	@return: true if succeed, else false.
	*/
	bool insertBook(string rfid, string name, string author, string version, string x_str, string y_str);

	/*
	@requires: rfid
	@affect: remove book from DB
	@result: true if successfully removed, false if doesnt exist.
	*/
	bool removeBook(string rfid);

	/*
	@requiers: rfid
	@return : the book with the requested rfid, or nullptr if no such book.
	*/
	int getBooks();

    /*
    @requiers: none
    @affect : read csv to db.
    */
    void read_record(std::string csv_file);

    /*
    @requiers: none
    @return : the book with the requested rfid, or nullptr if no such book.
    */
    int updateBook(std::string rfid, std::string x, std::string y);

	//diaplay DB
	std::ostream& print(std::ostream& os) const {
		for (auto it = map.begin(); it != map.end(); ++it) {
			os << *(it->second) << std::endl;
		}
		return os;
	}

	static string quotesql( const string& s ) {
        return string("'") + s + string("'");
    }

    std::map<string, Book*>* get_books_map(){
	    return &this->map;
	}

private:
	std::map<string, Book*> map;
    sqlite3 *db;
};

static int callback(void *data, int argc, char **argv, char **azColName){
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for(i = 0; i<argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}


static int get_books_callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    FILE * pFile;
    int n;
    char name [100];

    pFile = fopen ("../DataBase/tags.txt","a+");
    for(i = 0; i<argc; i++) {
        fprintf(pFile,"%s\n", argv[i] ? argv[i] : "NULL");
    }
    fclose(pFile);
    printf("\n");
    return 0;
}

BooksDataBase::BooksDataBase()
{
    char *zErrMsg = 0;
    int rc;
    rc = sqlite3_open("test.db", &this->db);
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }
    /* Create SQL statement */
    const char *sql = "CREATE TABLE IF NOT EXISTS LIBRARY("  \
                    "RFID           CHAR(50) PRIMARY KEY   NOT NULL," \
                    "NAME           TEXT    NOT NULL," \
                    "AUTHOR         TEXT     NOT NULL," \
                    "VERSION        CHAR(50),"\
                    "X              REAL,"\
                    "Y              REAL)";
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Records created successfully\n");
    }
    sqlite3_close(db);
    return;
}


BooksDataBase::~BooksDataBase()
{
	for (auto it = map.begin(); it != map.end(); ++it) {
		delete it->second;
	}
    sqlite3_close(db);
}

bool BooksDataBase::insertBook(string rfid, string name, string author, string version, string x_str, string y_str) {
	try {
        sqlite3_stmt * stmt;
        string sql_statement = "INSERT INTO LIBRARY (RFID, NAME, AUTHOR, VERSION, X, Y) VALUES ("
                + quotesql(rfid) + ","
                + quotesql(name) + ","
                + quotesql(author) + ","
                + quotesql(version) + ","
                + x_str + ","
                + y_str +");";
        if (sqlite3_open("test.db", &db) == SQLITE_OK)
        {
            sqlite3_prepare( db, sql_statement.c_str(), -1, &stmt, NULL );//preparing the statement
            sqlite3_step( stmt );//executing the statement
        }
        else
        {
            cout << "Failed to open db\n";
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
	}
	catch (std::exception e) {
		e.what();
		return false;
	}
	return true;
}


bool BooksDataBase::removeBook(string rfid) {
	auto it = map.find(rfid);
	if (it == map.end()) {
		return false;
	}
	delete it->second;
	map.erase(rfid);
	return true;
}

int BooksDataBase::getBooks() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("test.db", &db);

    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } else {
        fprintf(stderr, "Opened database successfully\n");
    }

    /* Create SQL statement */
    const char *sql = "SELECT RFID from LIBRARY";

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, get_books_callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);
    return 0;
}

void BooksDataBase::read_record(std::string csv_file)
{

    // File pointer
    fstream fin;

    // Open an existing file
    fin.open(csv_file, ios::in);

    // Get the roll number
    // of which the data is required

    // Read the Data from the file
    // as String Vector
    vector<string> row;
    string line, word;

    while (!fin.eof()) {

        row.clear();

        // read an entire row and
        // store it in a string variable 'line'
        getline(fin, line);

        // used for breaking words
        stringstream s(line);

        // read every column data of a row and
        // store it in a string variable, 'word'
        while (getline(s, word, ',' )) {

            // add all the column data
            // of a row to a vector
            row.push_back(word);
        }

        // convert string to integer for comparision
        this->insertBook(row[0], row[1], row[2], row[3], row[4], row[5]);
        Book* new_book = new Book(row[0]);
        this->map.insert(std::pair<string, Book*>(row[0], new_book));
    }
}



int BooksDataBase::updateBook(std::string rfid, std::string x, std::string y){
    try {
        std::string::size_type sz;     // alias of size_t
        double x_double = std::stod (x,&sz);
        double y_double = std::stod (y,&sz);
        this->map[rfid]->insertLocation(x_double, y_double);
        double average_x = this->map[rfid]->getX();
        double average_y = this->map[rfid]->getY();
        sqlite3_stmt * stmt;
        string sql_statement = "UPDATE LIBRARY set X=" +
                quotesql(to_string(average_x)) + ",Y=" +quotesql(to_string(average_y)) +
                "where RFID=" +quotesql(rfid)
                + "; SELECT * from LIBRARY";
        if (sqlite3_open("test.db", &db) == SQLITE_OK)
        {
            sqlite3_prepare( db, sql_statement.c_str(), -1, &stmt, NULL );//preparing the statement
            sqlite3_step( stmt );//executing the statement
        }
        else
        {
            cout << "Failed to open db\n";
        }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
    }
    catch (std::exception e) {
        e.what();
        return false;
    }
    return true;
}


std::ostream& operator<<(std::ostream& os, BooksDataBase& book_db) {
	return book_db.print(os);
}