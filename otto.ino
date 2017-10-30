int incomingByte = 0;   // for incoming serial data
int lastCommand = 0;


void act (int command) {
 
                switch (command) {
                  case 49:
                  Serial.println("frente ");
                  lastCommand = 49;
                  break;
                  case 50:
                  Serial.println("tras ");
                  lastCommand = 50;
                  break;
                  case 51:
                  Serial.println("direita ");
                  lastCommand = 53;
                  break;
                  case 52:                  
                  Serial.println("esquerda ");
                  lastCommand = 53;
                  break;
                  case 53:
                  Serial.println("parar");
                  lastCommand = 53;
                  break;
  
}
}

void setup() {
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        //para o robo
        
}

void loop() {

        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();
                
                act (incomingByte);
                              
        } else {

             act (lastCommand);
          
        }
        delay(1000);
}

