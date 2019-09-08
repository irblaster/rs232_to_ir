/* send.ino Example sketch for IRLib2
 *  Illustrates how to send a code.
 */
//#include <IRLibSendBase.h>    // First include the send base
//Now include only the protocols you wish to actually use.
//The lowest numbered protocol should be first but remainder 
//can be any order.
//#include <IRLib_P01_NEC.h>    
//#include <IRLib_P02_Sony.h>   
#include <IRLibAll.h >
#include <IRLib_HashRaw.h>    //Only use raw sender
#include <IRLibCombo.h>     // After all protocols, include this
// All of the above automatically creates a universal sending
// class called "IRsend" containing only the protocols you want.
// Now declare an instance of that sender.

IRsend mySender;
IRsendRaw mySenderRaw;



//String incoming="";   // for incoming serial string data
const byte numChars = 512;
char incoming_array[512];
//char output_buffer[80];
char ir_type[16];
//uint32_t ir_code;
//uint8_t ir_len;

//unsigned int ir_code;
uint32_t ir_code;
unsigned int ir_len;
unsigned int ir_type_int;

uint16_t rawData[128];
unsigned int rawDataLen;


char sendKnown = 0;
char sendRaw = 0;


void setup() {
  Serial.begin(9600);
  while (!Serial); //delay for Leonardo
  Serial.println ("irblaster.info RS232 IR TX 0.2");
  }


void recvWithEndMarker() {
    uint16_t ndx = 0;
    //char endMarker = '\n';
    char rc;
    bool done = false;

    while (done == false )
    {
        if (Serial.available() > 0 ) {
          rc = Serial.read();
          if (rc != '\n' && rc != '\r') {
             incoming_array[ndx] = rc;
             ndx++;
//             if (ndx > 512 ) { 
//                Serial.println ("buffer overflow");
//                Serial.println (ndx);
//             }
          }  else {
            incoming_array[ndx] = '\0'; // terminate the string
            done = true;
//            Serial.println ("indx =");
//            Serial.println (ndx);
         }
      }
    }
    
}



void loop() {
    while (Serial.available()==0) { }
//    incoming = Serial.readString();
    // say what you got:
    //Serial.println(incoming);    
//    incoming.toCharArray(incoming_array, 1024);

    recvWithEndMarker();

//    Serial.println("incoming_array=");
//    Serial.println(incoming_array);

    sscanf (incoming_array, "%[A-Z0-9],%d,%lx", ir_type, &ir_len, &ir_code);

//    Serial.println(ir_type);
//    Serial.println(ir_code);
//    Serial.println(ir_len);
    

    //sprintf (output_buffer, "received: %s,%lx,%d", ir_type, ir_len, ir_code);
    //Serial.println(output_buffer);

    if(strcmp(ir_type, "UNKNOWN") == 0) {
        ir_type_int = UNKNOWN;
        sendKnown = 1;
    } else if(strcmp(ir_type, "NEC") == 0) {
        ir_type_int = NEC; 
        sendKnown = 1;
    } else if(strcmp(ir_type, "SONY") == 0) {
        ir_type_int = SONY;
        sendKnown = 1;
    } else if (strcmp(ir_type, "RC5") == 0) {
        ir_type_int = RC5;
        sendKnown = 1;
    } else if (strcmp(ir_type, "RC6") == 0) {
        ir_type_int = RC6;
        sendKnown = 1;
    } else if (strcmp(ir_type, "PANASONIC_OLD") == 0) {
        ir_type_int = PANASONIC_OLD;
        sendKnown = 1;
    } else if (strcmp(ir_type, "JVC") == 0) {
        ir_type_int = JVC;
        sendKnown = 1;
    } else if (strcmp(ir_type, "NECX") == 0) {
        ir_type_int = NECX;
        sendKnown = 1;
    } else if (strcmp(ir_type, "SAMSUNG36") == 0) {
        ir_type_int = SAMSUNG36;
        sendKnown = 1;
    } else if (strcmp(ir_type, "GICABLE") == 0) {
        ir_type_int = GICABLE; 
        sendKnown = 1;
    } else if (strcmp(ir_type, "DIRECTV") == 0) {
        ir_type_int = DIRECTV;
        sendKnown = 1;
    } else if (strcmp(ir_type, "RCMM") == 0) {
        ir_type_int = RCMM;
        sendKnown = 1;
    } else if (strcmp(ir_type, "CYKM") == 0) {
       ir_type_int = CYKM;  
       sendKnown = 1;
    } else if (strcmp(ir_type, "RAW") == 0) {
       sendRaw = 1;
         char *ptr = NULL;
         char token[16];
         byte index = 0;
         ptr = strtok(incoming_array, ",");  // takes a list of delimiters
         while(ptr != NULL)
         {        
          if (index == 1) {
            rawDataLen = atoi(ptr);
          } else if (index >= 2) {
            rawData[index-2] = atoi(ptr);
          }
              
          //Serial.println(ptr);
          ptr = strtok(NULL, ",");  // takes a list of delimiters
          index++;
         }
      
         
    } else {
      //sprintf (output_buffer, "ERROR: %s is an invalid remote type", ir_type);
      Serial.println ("invalid type");      
    }
    
    if (sendKnown ==1 ) {
//      Serial.println(ir_code);
      mySender.send(ir_type_int,ir_code, ir_len);//Sony DVD power A8BCA, 20 bits
      Serial.println("IR Sent");
    } else if ( sendRaw ==1 ) {
//      Serial.println("raw data len =");
//      Serial.println(rawDataLen);
//      for (int i = 0; i < rawDataLen; i++) {      
//        Serial.println(rawData[i]);
//      }
      mySenderRaw.send(rawData,rawDataLen,36);//Pass the buffer,length, optionally frequency
      Serial.println("RAW IR Sent");
    }
    sendRaw = 0;
    sendKnown = 0;
  
}
