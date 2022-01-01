
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

const byte slaveAddress[5] = {'R', 'x', 'A', 'A', 'A'};

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

char dataToSend = 'k'; //signal that activates the Slave
int segment = 0;
bool k_flag = false;
int location[2] = {15, 1};
int x_index = 1;
int y_index = 1;

void setup() {
  Serial.begin(115200);
  Serial.println("SimpleTxAckPayload Starting");

  radio.begin();
  radio.setDataRate( RF24_250KBPS );
  radio.maskIRQ(1, 1, 0); //mask the recieving signal
  radio.enableAckPayload();
  radio.setRetries(5, 5);
  radio.openWritingPipe(slaveAddress);
}

#define REQUEST_PERIOD 5000
#define SLAVE_BUFF_SIZE 256

unsigned long request_timer = 0;


bool rslt = false;

void loop()
{

  while(Serial.available()) //WAIT for COMMAND from pc to START communication
  {
    char x = Serial.read();

    if(x=='k')
    {
       //Serial.println("k command was sent");
       rslt = radio.write( &x, sizeof(dataToSend)); //rslt check if signal was written and acked
       k_flag = true;
       
       //Serial.println(rslt);
    }else if(x == 'n'){
        segment++;
        rslt = radio.write( &x, sizeof(dataToSend));
        if(segment == 7){
          y_index++;
          location[1] = 1*y_index; 
        }else if(segment<7){
          x_index++;
          location[0] = 15*x_index;
        }else if(segment>7){
          x_index--;
          location[0] = 15*x_index;
        }
    }else if(x == 'h'){
        rslt = radio.write( &x, sizeof(dataToSend));
    }
  }

  if (radio.isAckPayloadAvailable())//RECIEVE DATA and print or transfer to pc to divide to packets
  {
    //Serial.println("available packets");
    if(k_flag){
      Serial.println("start");
      Serial.print(location[0]);
      Serial.print(',');
      Serial.print(location[1]);
      Serial.println(';');
    }
    int packet_size  = radio.getDynamicPayloadSize();
    //Serial.println(packet_size);
    char tmp[32];
    radio.read(tmp , sizeof(tmp));
    
    tmp[packet_size] = 0;
    //Serial.println(tmp);
    print_packet(tmp, packet_size);
    if(k_flag){
      Serial.println();
      Serial.println("end");
      k_flag = false;
    }
  }

}


void print_packet(char *tmp, int lenght){
  for(int i=0; i<lenght; i++){
    Serial.print(tmp[i]);
  }
  Serial.println();
}
