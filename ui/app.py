from PyQt5 import QtWidgets, QtGui, QtCore
from PyQt5.QtWidgets import *
from web_scraping import build_driver, build_driver_not_save
import sys
from PyQt5.QtGui import *
from PyQt5.QtCore import *
import os
import db_api
from serial import Serial
import serial
import time
import ui_db


#widget_names = ["Red", "Orange", "Blue", "White", "Green"]

check_in_state = False
temp_tag = ''




class App(QMainWindow):
    def __init__(self):
        #initialize the app
        super().__init__()
        self.title = 'PPPy'
        self.left = 0
        self.top = 0
        self.width = 900
        self.height = 900
        self.setWindowTitle(self.title)
        self.setGeometry(self.left, self.top, self.width, self.height)
        #set the tabs 
        self.table_widget = MyTableWidget(self)
        #apply tabs 
        self.setCentralWidget(self.table_widget)

        #scrollArea
        




        self.show()

class MyTableWidget(QWidget):

    def __init__(self, parent):
        super(QWidget, self).__init__(parent)
        self.layout = QVBoxLayout(self)

        #initialize tab screen
        self.tabs = QTabWidget()
        self.tab1 = QWidget()
        self.tab2 = QWidget()
        self.tab3 = QtWidgets.QWidget()
        self.tabs.resize(300,300)

        #add tabs
        #add QWidget tab to QTabWidget
        self.tabs.addTab(self.tab1, "Tab 1")
        self.tabs.addTab(self.tab2, "Tab 2")
        self.tabs.addTab(self.tab3, "Tab 3")

        #create first tab
        #add a layout to the specific QWidget tab which is QVBoxLayout
        self.tab1.layout = QVBoxLayout(self)
        self.pushButton1 = QPushButton("Scan Rfid")
        self.pushButton2 = QPushButton("Highlight")
        self.pushButton2.setGeometry(50, 50, 50, 50)
        self.pushButton1.clicked.connect(self.scan_and_check_rfid)
        self.pushButton2.clicked.connect(self.scan_and_check_rfid)
        
        #add QPushButton widget to the layout of tab1
        self.tab1.layout.addWidget(self.pushButton1)
        self.tab1.layout.addWidget(self.pushButton2)
        #set the layout of tab1
        self.tab1.setLayout(self.tab1.layout)
        

        #create second tab
        self.tab2.layout = QGridLayout()
        self.tab2.setGeometry(0, 0, 300, 300)
        self.tab2.layout.setSpacing(10)
        #set search
        self.searchbar = QLineEdit()
        books_for_completer = get_books()
        completer = QCompleter(books_for_completer)
        self.searchbar.setCompleter(completer)
        self.searchbarLayout = QVBoxLayout()
        self.container = QWidget()
        self.searchbarLayout.addWidget(self.searchbar)
        self.container.setLayout(self.searchbarLayout)
        
        self.tab2.layout.addWidget(self.container, 0, 0)
        self.tab2.setLayout(self.tab2.layout)

        self.listwidget = QListWidget()
        self.add_books_search_list()
        
        self.listwidget.clicked.connect(self.choose_item)
        self.tab2.layout.addWidget(self.listwidget)
        self.search_button = QtWidgets.QPushButton(self)
        self.search_button.setText("Search")
        self.tab2.layout.addWidget(self.search_button, 0, 100)
        
        self.searchbar.textChanged.connect(self.update_display)
        self.search_button.clicked.connect(self.item_search)       

        #create third tab
        self.photo = QtWidgets.QLabel(self)
        self.photo.setGeometry(0, 0, 650, 650)
        font1 = QtGui.QFont()
        font1.setPointSize(40)
        self.photo.setFont(font1)
        self.photo.setFrameShape(QtWidgets.QFrame.Panel)
        self.photo.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.photo.setLineWidth(5)
        self.photo.setScaledContents(True)
        self.setObjectName("photo2")


        self.photo2 = QtWidgets.QLabel(self)
        self.photo2.setGeometry(700, 0, 650, 650)
        font3 = QtGui.QFont()
        font3.setPointSize(40)
        self.photo2.setFont(font3)
        self.photo2.setFrameShape(QtWidgets.QFrame.Panel)
        self.photo2.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.photo2.setLineWidth(5)
        self.photo2.setScaledContents(True)
        self.photo2.setObjectName("photo2")
        
        
        #availability label
        
        widget = QtWidgets.QWidget()
        self.tab3.layout = QVBoxLayout(self)
        self.tab3.layout.setContentsMargins(0, 0, 0, 0)
        widget.setLayout(self.tab3.layout)

        scroll = QtWidgets.QScrollArea()
        self.frame = QtWidgets.QFrame.Box
        scroll.setFrameShape(self.frame)
        scroll.setVerticalScrollBarPolicy(Qt.ScrollBarAlwaysOn)
        scroll.setHorizontalScrollBarPolicy(Qt.ScrollBarAlwaysOff)
        scroll.setWidgetResizable(True)
        scroll.setWidget(widget)

        scroll_layout = QtWidgets.QVBoxLayout(self)
        scroll_layout.addWidget(scroll)
        scroll_layout.setContentsMargins(0, 0, 0, 0)
        self.tab3.setLayout(scroll_layout)
       
        
        self.tab3.layout.addWidget(self.photo)
        self.tab3.layout.addWidget(self.photo2)
        self.tab3.setLayout(self.tab3.layout)
        


        #Add tabs to widget
        #add to the layout finished QTabWidget and set it
        self.layout.addWidget(self.tabs)
        self.setLayout(self.layout)



        


    def show_predict(self):
            self.photo2.setPixmap(QtGui.QPixmap(os.path.realpath("image/predictions.png")))
    
    def search_tab(self):
        self.tabs.setCurrentIndex(1)

    def data_tab(self):
        self.tabs.setCurrentIndex(2)

    def scan_and_check_rfid(self):
        print('button clicked')
        tag = ""
        tag = scan_rfid()
        tag = seperate_tag(tag)
        print(tag)
        if(db_api.check_rfid(tag.decode("utf-8") )):
            print("tag in db")
            self.data_tab()
            database = ui_db.UiDatabase()
            book_data = ()
            book_data = database.get_location_n_book_path(tag.decode("utf-8"))
            book_data = list(book_data)
            print(book_data)
            self.photo2.setPixmap(QtGui.QPixmap(os.path.realpath(book_data[0][0])))
            self.photo.setPixmap(QtGui.QPixmap(os.path.realpath(book_data[0][1])))
            self.data_tab()
            if database.check_availability(tag.decode("utf-8")):
                database.update_availability(tag.decode("utf-8"), 'no')
            else:
                database.update_availability(tag.decode("utf-8"), 'yes')
                database.close_connection()
        elif tag == b'':
            pass
        else:
            print("tab_changed")
            global check_in_state
            check_in_state = True
            temp_tag = tag.decode("utf-8")
            print(temp_tag)
            self.search_tab()
    
    def add_books_search_list(self):
        books = get_books()
        for book in books:
            self.listwidget.addItem(book)
    
    def choose_item(self, qmodelindex):
        item = self.listwidget.currentItem()
        database = ui_db.UiDatabase()
        book_data = ()
        book_data = database.get_by_name(item.text())
        book_rfid = database.get_rfid_by_name(item.text())
        
        book_rfid = list(book_rfid)
        print(book_rfid)
        if(database.check_availability(book_rfid[0][0])):
            self.available_label = QLabel("Available",self)
            self.available_label.setText("Available")
            self.available_label.move(450, 0)
            self.available_label.setAlignment(Qt.AlignCenter)
            self.available_label.setStyleSheet("border: 1px solid black")
            self.tab3.layout.addWidget(self.available_label)
            self.tab3.setLayout(self.tab3.layout)
        else:
            self.not_available_label = QLabel("Not Available",self)
            self.not_available_label.move(450, 0)
            self.not_available_label.setAlignment(Qt.AlignCenter)
            self.not_available_label.setStyleSheet("border: 1px solid black; background-color: red;")
            self.tab3.layout.addWidget(self.not_available_label)
            self.tab3.setLayout(self.tab3.layout)
        
        book_data = list(book_data)
        print(book_data)
        database.close_connection()
        if book_data[0][1]!=None:
            self.photo2.setPixmap(QtGui.QPixmap(os.path.realpath(book_data[0][1])))
        if book_data[0][0]!=None:
            self.photo.setPixmap(QtGui.QPixmap(os.path.realpath(book_data[0][0])))
        self.data_tab()
        

    def item_search(self, qmodelindex):
        global check_in_state
        books = get_books()
        item = self.searchbar.text()
        print(books)
        if item in books:
            self.update_display
            print("first condition in item_search")
        elif item not in books and check_in_state and item !='':
            global temp_tag
            print(temp_tag)
            book_path = build_driver(item)
            database = ui_db.UiDatabase()
            database.insert_rfid(temp_tag)
            database.update_book(temp_tag, book_path)
            database.update_name(item, temp_tag)
            database.close_connection()
            check_in_state = False
            temp_tag = ''
            print("second condition in item_search")
        else:
            path = build_driver_not_save(item)
            print("third condition in item_search")


    def update_display(self, text):
        for i in range(self.listwidget.count()):
            if self.listwidget.item(i).text() == text:
                self.listwidget.item(i).setHidden(False)
            else:
                self.listwidget.item(i).setHidden(True)
        if(text == ''):
            for i in range(self.listwidget.count()):
                self.listwidget.item(i).setHidden(False)


def get_tag(output_str):
    index = 0
    size = len(output_str)
    print(size)
    while True:
        start = output_str.find(b'\nU', index, size-1)+2
        end = output_str.find(b'\r', start, size-1)
        print(start)
        print(end)
        if(start == 1 or end == -1):
            break
        if(start > size or end > size):
            break
        return output_str[start:end]
     

def scan_rfid():
    ser = serial.Serial(port = 'COM13', baudrate = 38400, parity = serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE,
                        bytesize = serial.EIGHTBITS, timeout = 0)

    try:
        ser.isOpen()
    except:
        print("Error")
        exit()
    time.sleep(0.1)

    command = "\x0A\x55\x0D"
    output = ""

    if(ser.isOpen()):
        ser.write(command.encode())
        time.sleep(0.06)
        output = ser.readall()

        print(output)
        tag = ""
        tag = get_tag(output)
        if(tag == None):
            print("no id scan again")
        print(tag)
        return tag

def get_books():
    books = []
    book_ui = ui_db.UiDatabase()
    books = book_ui.get_book_names()
    book_ui.close_connection()
    return books

def seperate_tag(tag):
    size = len(tag)
    start = tag.find(b'B', 0, size-1)
    end = start + 6
    return tag[start:end]

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = App()
    sys.exit(app.exec_())