//PC should send signal to MASTER nrf. nrf SLAVE recieves signal and SCANS. if Bluetooth recieved signal, START READING untill the data was SENT. There are 2 cases:
//FIRST CASE: The last packet of data was sent NOT in maximum payload
//SECOND CASE: The last packet of data was sent in maximum payload
//SOLUTION:
//First case is sloved automatically because we can put a flag in the timeout handeling function
//SECOND case be handles if we put condition: we didnt sent NOT maximum payload AND bluetooth NOT AVAILABLE
//WE NEE SIGNALS
//1. RECEIVED SIGNAL from master
//2. 
 



#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SoftwareSerial.h>


SoftwareSerial BTSerial(4, 7); // RX | TX


#define CE_PIN   9
#define CSN_PIN 10
#define ENABLE 8
#define XDIR 5
#define XSTEP 2
#define YDIR 6
#define YSTEP 3

const byte thisSlaveAddress[5] = {'R', 'x', 'A', 'A', 'A'};

RF24 radio(CE_PIN, CSN_PIN);
unsigned char c;

 

 

int route_arr[13][4] = {{55, 240, 0, 0},
  {145, 185, 0, 0},
  {160, 200, 0, 0},
  {195, 140, 0, 0},
  {200, 130, 0, 0},
  {215, 110, 0, 0},
  {265, 0, 0, 430},
  {0, 0, 215, 55},
  {0, 0, 165, 100},
  {0, 0, 85, 195},
  {0, 0, 135, 125},
  {0, 0, 130, 160},
  {0, 0, 40, 205},
};
 

int segment=0;

#define PACKET_SIZE 32
int location[2] = {15,1};
char packet[PACKET_SIZE] = {0};
int packet_index = 0;
int x_index=1;
int y_index=1;

//counting steps
int count_x=0;
int count_y=0;


//FM-505
void sendIdentifyCmd() {
  BTSerial.write (0x0A);
  BTSerial.write (0x55);
  BTSerial.write (0x0D);
}


//JRD-100
//void sendIdentifyCmd(){
//  unsigned char cmd[7] = {0xBB, 0x00, 0x22, 0x00, 0x00, 0x22, 0x7E};
//
//  for (int i = 0; i < 7; i++)
//  {
//    Serial.write(cmd[i]);
//  }
//  
//}


void setup(void)
{
  Serial.begin(38400);
  BTSerial.begin(38400);
  //set steppers pins
  pinMode(ENABLE, OUTPUT);
  digitalWrite(ENABLE, LOW);
  
  pinMode(XDIR, OUTPUT);
  pinMode(YDIR, OUTPUT);
  
  pinMode(XSTEP, OUTPUT);
  pinMode(YSTEP, OUTPUT);
  //radio settings
  Serial.println("SimpleRxAckPayload Starting");
  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.openReadingPipe(1, thisSlaveAddress);
  radio.enableAckPayload();
  radio.startListening();


  //read_multi();
}

unsigned long bt_timeout = 0;



void loop()
{
  //BLOCK 1
  if (radio.available()) //if SIGNAL was RECIEVED, SCAN rfid tags. (could be sparated into cases which activate different sigments of the system)
  {
    radio.read(&c, 1);
    if (c == 'k')
    {
      
      Serial.println("k command recieved");
      radio.writeAckPayload(1,  &packet, packet_index);
      
      //Serial.println("multi read send");
      //read_multi();
      sendIdentifyCmd();
      int current_millis = millis();
      while(millis() - current_millis<300){
      }
      //Serial.println("multi read stopped");
      //stop_read();
      
    }else if(c == 'n'){
      move_right_x(route_arr[segment][0]);
      move_right_y(route_arr[segment][1]);
      move_left_x(route_arr[segment][2]);
      move_left_y(route_arr[segment][3]);
      if(route_arr[segment][2]==0 && route_arr[segment][3]==0){
        x_index++;
        location[0]=15*x_index;  
      }
      if(route_arr[segment][0]==0 && route_arr[segment][1]==0){
        x_index--;
        location[0]=15*x_index;
      }
      if(route_arr[segment][1]==0 && route_arr[segment][2]==0){
        y_index++;
        location[1] = 1*y_index; 
      }
      segment++;
    }else if( c == 'h'){
      counting();
      homing();
      
      packet_index = 0;
      x_index=1;
      y_index=1;
      count_x=0;
      count_y=0;
      location[0] = 15;
      location[1] = 1;
      segment = 0;
    }
  
  }

  
  
  //BLOCK 2
  while (BTSerial.available()) //if TAGS were scanned and RECIEVED from bluetooth, check what is AVAILABLE
  {
    
    bt_timeout = millis(); //start the timeout from the moment that tags are available

    char in = BTSerial.read();
    Serial.println(in);
    packet[packet_index] = in;

    packet_index++;
    if (packet_index == PACKET_SIZE)//if we reached maximum payload, we will SEND the tag and EMPTY the packet
    {
      radio.writeAckPayload(1,  &packet, PACKET_SIZE);
      
      packet_index = 0;
      
      Serial.println("Middle packet");
    }
  }
  //BLOCK 3
  if ((bt_timeout > 0) &&( millis() - bt_timeout > 1000) && (packet_index!=0)) //if we START to count the TIME from bluetooth AND reached the TIMEOUT, we SEND THE PACKET
  {
    Serial.println("Sent");
    radio.writeAckPayload(1,  &packet, packet_index);    
    packet_index = 0;
    bt_timeout = 0;
    
  }
  //BLOCK 4. SEND LOCATION
  //BLOCK 5. MOVE STEPPER TO NEXT LOCATION
}


void counting() {
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 4; j++) {
      if (j == 0) {
        count_x += route_arr[i][j];
      } else if (j == 2) {
        count_x -= route_arr[i][j];
      }

    }
  }
  for (int i = 0; i < 13; i++) {
    for (int j = 0; j < 4; j++) {
      if (j == 1) {
        count_y += route_arr[i][j];
      } else if (j == 3) {
        count_y -= route_arr[i][j];
      }

    }
  }
}


void homing(){
  if(count_x>=0){
    digitalWrite(XDIR, LOW);
  }else{
    count_x=count_x*(-1);
    digitalWrite(XDIR, HIGH);
  }
  if(count_y>=0){
    digitalWrite(YDIR, LOW);
  }else{
    count_y = count_y*(-1);
    digitalWrite(YDIR, HIGH);
  }
  delay(100);
  if(count_x>=count_y){
      for(int i=0; i<count_y; i++){
        digitalWrite(XSTEP, HIGH);
        digitalWrite(YSTEP, HIGH);  
        delayMicroseconds(5000);
        digitalWrite(XSTEP, LOW);
        digitalWrite(YSTEP, LOW); 
        delayMicroseconds(5000);
      }
      int remaining_x = count_x - count_y;
      for(int i=0; i<remaining_x; i++){
        digitalWrite(XSTEP, HIGH); 
        delayMicroseconds(5000);
        digitalWrite(XSTEP, LOW);
        delayMicroseconds(5000);         
      }
      
    }else{
      for(int i=0; i<count_x; i++){
        digitalWrite(XSTEP, HIGH);
        digitalWrite(YSTEP, HIGH);  
        delayMicroseconds(5000);
        digitalWrite(XSTEP, LOW);
        digitalWrite(YSTEP, LOW); 
        delayMicroseconds(5000);
      }
      int remaining_y = count_y - count_x;
      for(int i=0; i<remaining_y; i++){
        digitalWrite(YSTEP, HIGH); 
        delayMicroseconds(5000);
        digitalWrite(YSTEP, LOW);
        delayMicroseconds(5000);         
      }
      
    }
}

void move_right_x(int steps){
  digitalWrite(XDIR, HIGH);
  for(int i=0; i<steps; i++){
    digitalWrite(XSTEP, HIGH);
    delayMicroseconds(5000);
    digitalWrite(XSTEP, LOW);
    delayMicroseconds(5000);
  }
}


void move_right_y(int steps){
   digitalWrite(YDIR, HIGH);
  for(int i=0; i<steps; i++){
    digitalWrite(YSTEP, HIGH);
    delayMicroseconds(5000);
    digitalWrite(YSTEP, LOW);
    delayMicroseconds(5000);
  }
}


void move_left_x(int steps){
  digitalWrite(XDIR, LOW);
  for(int i=0; i<steps; i++){
    digitalWrite(XSTEP, HIGH);
    delayMicroseconds(5000);
    digitalWrite(XSTEP, LOW);
    delayMicroseconds(5000);
  }
}


void move_left_y(int steps){
   digitalWrite(YDIR, LOW);
  for(int i=0; i<steps; i++){
    digitalWrite(YSTEP, HIGH);
    delayMicroseconds(5000);
    digitalWrite(YSTEP, LOW);
    delayMicroseconds(5000);
  }
}

//void read_multi()
//{
//  unsigned int reads = 0xffff;
//  byte rh = highByte(reads);
//  byte rl = lowByte(reads);
//  char cs = 0x27 + 0x03 + 0x22 + rh + rl;
//  char cmd[10] = {0xBB, 0x00, 0x27 , 0x00 , 0x03 , 0x22 , rh , rl , cs , 0x7E};
//
//  for (int i = 0; i < 10; i++)
//  {
//    BTSerial.write(cmd[i]);
//  }
//}
//
//
//void stop_read()
//{
//  char cmd[7] = {0xBB, 0x00, 0x28 , 0x00 , 0x00 , 0x28 , 0x7E};
//
//  for (int i = 0; i < 7; i++)
//  {
//    BTSerial.write(cmd[i]);
//  }
//
//}
