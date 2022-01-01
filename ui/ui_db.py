
# -*- coding: utf-8 -*-

import sqlite3
from sqlite3 import Error
import db_api
import web_scraping
import cv2
import numpy as np


image = cv2.imread('C:/Users/Valery/Desktop/vs/shelve.jpg')



def create_connection(db_file):
    conn = None
    try:
        conn = sqlite3.connect(db_file)
    except Error as e:
        print(e)
    
    return conn


def fetch_book(pk):
    cursor.execute(f"SELECT * FROM ui WHERE id = %s", (pk,))
    return cursor.fetchall()

def insert_book(rfid, name):
    insert_id_query = """INSERT INTO ui (rfid, name, availability, book, location)
                        VALUES (?, ?, NULL, NULL, NULL);"""
    book_tuple = (rfid, name)
    
    cursor.executemany(insert_id_query, book_tuple)



    

def update_db():
    book_list = []
    table_list = []
    table_list = db_api.get_data()
    ui_dataBase = UiDatabase()
    for row in table_list:
        print(row[1])
        rfid_name = (row[0], row[1])
        path_book = web_scraping.build_driver(row[1])
        path_location = draw(row[1], row[4], row[5])
        ui_dataBase.insert_book(row[0], row[1])
        ui_dataBase.update_location(row[0], path_location)
        ui_dataBase.update_book(row[0], path_book)
        ui_dataBase.update_availability(row[0], 'yes')
    
    book_list = ui_dataBase.get_table_data()

    print(book_list)    
    
        

    print("database updated")
    
    ui_dataBase.close_connection()


def draw(query, x, y):
    real_width = 105
    real_height = 3
    scale_precent = 50
    width = int(image.shape[1]*scale_precent/100)
    height = int(image.shape[0]*scale_precent/100)
    dim = (width, height)
    resized = cv2.resize(image, dim, interpolation = cv2.INTER_AREA)
    gray = cv2.cvtColor(resized, cv2.COLOR_BGR2GRAY)
    image2 = np.zeros_like(resized)
    image2[:, :, 0] = gray
    image2[:, :, 1] = gray
    image2[:, :, 2] = gray
    

    
    #mask = np.ones(resized.shape[:2], dtype="uint8") * 255
    mask = np.ones(image2.shape[:2], dtype = "uint8")*255
    interpolated_width = int((x/real_width)*width)
    interpolated_height = int((y/real_height)*height)
    cv2.circle(image2,(interpolated_width, interpolated_height), 25, (0,0,255), 3)
    print('Original Dimensions : ',image.shape)
    resized = cv2.bitwise_and(image2, image2, mask=mask)

    cv2.imwrite(f'book_location/{query}-location.png', resized)

    #cv2.imshow('mask', mask)
    #cv2.imshow('after', resized)
    cv2.waitKey(0)
    cv2.destroyAllWindows()
    return f'C:/Users/Valery/Desktop/vs/book_location/{query}-location.png'



class UiDatabase:
    def __init__(self, dbname = r"C:\Users\Valery\Desktop\vs\ui_db.db"):
        self.dbname = dbname
        
        self.conn = None
        try:
            self.conn = sqlite3.connect(dbname)
        except Error as e:
            print(e)
    
    def setup(self):
        print("creating tables")
        table = """CREATE TABLE IF NOT EXISTS ui (
                                rfid text PRIMARY KEY,
                                name text,
                                availability text,
                                book text,
                                location text
                            );"""
        print(table)
        self.conn.execute(table)
        self.conn.commit()


    def get_table_data(self):
        data_list = []
        for row in self.conn.execute("SELECT * FROM ui"):
            data_list.append(row)
        
        return data_list
        
    def insert_book(self, rfid, name):
        insert_id_query = """INSERT OR IGNORE INTO ui (rfid, name, availability, book, location)
                        VALUES (?, ?, NULL, NULL, NULL);"""
        book_tuple = (rfid, name)
        self.conn.execute(insert_id_query, book_tuple)
        self.conn.commit()
    
    def insert_rfid(self, rfid):
        insert_rfid_query = """INSERT OR IGNORE INTO ui (rfid) VALUES (?);"""
        rfid_tuple = (rfid, )
        self.conn.execute(insert_rfid_query, rfid_tuple)
        self.conn.commit()
    
    def get_location_n_book_path(self, rfid):
        get_data = "SELECT book, location FROM ui WHERE rfid = (?)"
        return self.conn.execute(get_data, (rfid,))

    def get_by_name(self, name):
        get_data = "SELECT book, location FROM ui WHERE name = (?)"
        return self.conn.execute(get_data, (name,))
    
    def update_location(self, rfid, image_path):
        update_location_query = """UPDATE ui SET location = (?) WHERE rfid = (?)"""
        args = (image_path, rfid)
        self.conn.execute(update_location_query, args)
        self.conn.commit()
    
    def update_book(self, rfid, book_path):
        update_book_query = """UPDATE ui SET book = (?) WHERE rfid = (?)"""
        args = (book_path, rfid)
        self.conn.execute(update_book_query, args)
        self.conn.commit()

    def update_name(self, name, rfid):
        update_name_query = """UPDATE ui SET name = (?) WHERE rfid = (?)"""
        args = (name, rfid)
        self.conn.execute(update_name_query, args)
        self.conn.commit()
    
    def is_book_exist(self, rfid):
        check_query = """SELECT EXISTS(SELECT * FROM ui WHERE rfid = (?));"""
        return self.conn.execute(check_query, (rfid,))
    
    def get_book_names(self):
        get_query = """SELECT name FROM ui"""
        return [x[0] for x in self.conn.execute(get_query)]
    
    def update_availability(self, rfid, availability):
        update_availability_query = """UPDATE ui SET availability = (?) WHERE rfid = (?)"""
        args = (availability, rfid)
        self.conn.execute(update_availability_query, args)
        self.conn.commit()
    
    def check_availability(self, rfid):
        select_query = """SELECT availability FROM ui WHERE rfid = (?);"""
        args = (rfid,)
        data = self.conn.execute(select_query, args)
        data = list(data)
        if data[0][0] == 'yes':
            return True
        else: 
            return False

    def get_rfid_by_name(self, name):
        select_rfid_query = """SELECT rfid FROM ui WHERE name = (?);"""
        args = (name,)
        data = self.conn.execute(select_rfid_query, args)
        return data

    def close_connection(self):
        self.conn.close()




def main():
    db = UiDatabase()
    while True:
        x = input()
        if(x == '0'):
            create_table = UiDatabase()
            create_table.setup()
        if(x == '1'):
            update_db()
        if(x == '2'):
            q = 'mega'
            draw(q, 15, 1)
        if(x == '3'):
            data_list = []
            data_list = db.get_table_data()
            print(data_list)
        

if __name__ == '__main__':
    main()







