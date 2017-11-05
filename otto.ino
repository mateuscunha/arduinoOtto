#include <Servo.h>
#include <Oscillator.h>


int incomingByte = 0;   // for incoming serial data
int lastCommand = 0;
#define N_SERVOS 4
#define PIN_RR 5
#define PIN_RL 4
#define PIN_YR 3
#define PIN_YL 2

#define ECHOPIN 9       // Pin to receive echo pulse
#define TRIGPIN 8 



#define INTERVALTIME 10.0 

Oscillator servo[N_SERVOS];


void walk(int steps, int T=500);
void backyard(int steps, int T=500);

void turnLeft(int steps, int T=500);
void turnRight(int steps, int T=500);
int getDistance();

void stop( );


void act (int command) {
 
                switch (command) {
                  case 49:
                  //frente
                  if (getDistance() > 8) {
                    walk(3);
                    lastCommand = 49;
                  } else {
                     lastCommand = 53;
                     stop();
                  }
                  
                  break;
                  case 50:
                  
                  backyard(3);
                  //traz
                  lastCommand = 50;
                  break;
                  case 51:
                  //direita
                  turnRight(5);
                  lastCommand = 53;
                  break;
                  case 52: 
                  turnLeft(5);                 
                  //esquerda
                  lastCommand = 53;
                  break;
                  case 53:
                  //parar
                  lastCommand = 53;
                  stop();
                  break;
  
}
}

void setup() {

  
        servo[0].attach(PIN_RR);
        servo[1].attach(PIN_RL);
        servo[2].attach(PIN_YR);
        servo[3].attach(PIN_YL);
  
        Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
        //para o robo
        for(int i=0;i<4;i++) servo[i].SetPosition(90);
        pinMode(ECHOPIN, INPUT);
        pinMode(TRIGPIN, OUTPUT);
         
        void stop( );

 
  
        
}

int t=495;
double pause=0;

void loop() {

  
       
        // send data only when you receive data:

        
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingByte = Serial.read();
                
                act (incomingByte);
                              
        } else {

             act (lastCommand);
          
        }
        delay(100);

      


        
}
int getDistance () {
  
        digitalWrite(TRIGPIN, LOW);
        delayMicroseconds(2);
        digitalWrite(TRIGPIN, HIGH);
        delayMicroseconds(10);
        digitalWrite(TRIGPIN, LOW);
  // Compute distance
       float distance = pulseIn(ECHOPIN, HIGH);
       distance= distance/58;

       return distance;
}
void stop () {

  for(int i=0;i<4;i++) servo[i].SetPosition(90);
}

void backyard(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(-90), DEG2RAD(-90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void walk(int steps, int T){
    int A[4]= {15, 15, 30, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)};
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}


void oscillate(int A[N_SERVOS], int O[N_SERVOS], int T, double phase_diff[N_SERVOS]){
  for (int i=0; i<4; i++) {
    servo[i].SetO(O[i]);
    servo[i].SetA(A[i]);
    servo[i].SetT(T);
    servo[i].SetPh(phase_diff[i]);
  }
  double ref=millis();
   for (double x=ref; x<T+ref; x=millis()){
     for (int i=0; i<4; i++){
        servo[i].refresh();
     }
  }
}

void turnLeft(int steps, int T){
    int A[4]= {20, 20, 10, 30};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

void turnRight(int steps, int T){
    int A[4]= {20, 20, 30, 10};
    int O[4] = {0, 0, 0, 0};
    double phase_diff[4] = {DEG2RAD(0), DEG2RAD(0), DEG2RAD(90), DEG2RAD(90)}; 
    
    for(int i=0;i<steps;i++)oscillate(A,O, T, phase_diff);
}

