import sqlite3

dbfile = 'C:/Users/Valery/Desktop/vs/test.db'

def create_connection(db):

    con = sqlite3.connect(db)
    cur = con.cursor()
    return con, cur

def close_connection(con):
    con.close()

def get_location(rfid):
    con, cur = create_connection(dbfile)
    for row in cur.execute("SELECT X, Y FROM LIBRARY WHERE RFID=?", (rfid,)):
        print(row)
    close_connection(con)


def check_rfid(rfid):
    con, cur = create_connection(dbfile)
    for row in cur.execute("SELECT RFID FROM LIBRARY;"):
        if rfid in row:
            return True
    close_connection(con)
    return False
    

def get_rfid(name):
    con, cur = create_connection(dbfile)
    for row in cur.execute("SELECT RFID FROM LIBRARY WHERE NAME=?", (name,)):

        print(row[0])
        print(type(row[0]))
    close_connection(con)

def get_data():
    con, cur = create_connection(dbfile)
    data_list = []
    for row in cur.execute("SELECT * FROM LIBRARY"):
        data_list.append(row)
    close_connection(con)
    return data_list




