#include "TimerOne.h"
#include <Wire.h>

const byte MOTOR1 = 2;  // Motor 1 Interrupt Pin - INT 0
const byte MOTOR2 = 3;  // Motor 2 Interrupt Pin - INT 1
 
// Integers for pulse counters
unsigned int counter1 = 0;
unsigned int counter2 = 0;

int resetPin=12;
int CLM[100];
int CRM[100];
String motion[100];
int i = 0;
int j = 0;
int k = 0;
int CC1 = 0;
int BC1 = 0;
int CF1 = 0;
int CC2 = 0;
int BC2 = 0;
int CF2 = 0;

int enA = 5;
int in1 = 6;
int in2 = 7;
int in3 = 8;
int in4 = 9;
int enB = 10;

String ccommand = "";
String pcommand = "";
String psymbolL = "";
String csymbolL = "";
String psymbolR = "";
String csymbolR = "";
int q=0;
int c=0;
int uflag=1;

void forward();
void backward();
void left();
void leftreverse();
void right();
void rightreverse();
void extremeleft();
void extremeright();
void hold();
void returnback();
void lastcommand();
void decodedcommand();
void executeDecodedCommand();
void processCounters();
 
void ISR_count1()  
{
  counter1++;  // increment Motor 1 counter value
} 
 
void ISR_count2()  
{
  counter2++;  // increment Motor 2 counter value
} 

void ISR_timerone()
{
  Timer1.detachInterrupt();  // hold the timer
//  Serial.print("Motor counter 1: ");
//  Serial.print(counter1);
//  Serial.print("       ");
//  Serial.print("Motor counter 2: ");
//  Serial.println(counter2);
  Timer1.attachInterrupt( ISR_timerone );  // Enable the timer
}

int pin1 = A0;
int pin2 = A1;
int pin3 = A2;

void setup(){
  Serial.begin(9600);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);
  digitalWrite(resetPin,HIGH);
  pinMode(resetPin, OUTPUT);

  Timer1.initialize(100000); // set timer for 0.1sec
  attachInterrupt(digitalPinToInterrupt (MOTOR1), ISR_count1, RISING);  // Increase counter 1 when speed sensor pin goes High
  attachInterrupt(digitalPinToInterrupt (MOTOR2), ISR_count2, RISING);  // Increase counter 2 when speed sensor pin goes High
  Timer1.attachInterrupt( ISR_timerone ); // Enable the timer
}

void loop(){
  
  if (uflag>1){
    processCounters();
      while (counter1<100){
        counter1=0;
        ccommand="forward";
        csymbolR=" +";
        csymbolL=" +";
        forward();
      }
      processCounters();
      executeDecodedCommand();
      processCounters();
      uflag=1;
  }else{
    decodedcommand();
  }
       
}

void decodedcommand(){
  int x = digitalRead(pin1);
  int y = digitalRead(pin2);
  int z = digitalRead(pin3);
  
  if (x==1 && y==1 && z==1){ /// forward
    uflag=1;
    ccommand="forward";
    csymbolR=" +";
    csymbolL=" +";
    forward();
  }
  else if (x==1 && y==0 && z==1){  /// left
    uflag=2;
    ccommand="left";
    csymbolR=" +";
    csymbolL=" +";
    left();
  }
  else if (x==0 && y==0 && z==1){  /// right
    uflag=3;
    ccommand="right";
    csymbolR=" +";
    csymbolL=" +";
    right();
  }
  else if (x==1 && y==1 && z==0){  /// extreme left
    uflag=4;
    ccommand="extremeleft";
    csymbolR=" -";
    csymbolL=" +";
    extremeleft();
  }
  else if (x==0 && y==1 && z==1){  /// extreme right
    uflag=5;
    ccommand="extremeright";
    csymbolR=" +";
    csymbolL=" -";
    extremeright();
  } 
  else if (x==0 && y==0 && z==0){ 
    uflag=6;
  }
  else{
    hold(); 
  }
}

void executeDecodedCommand(){
  if (uflag==6){
    lastcommand();
    returnback();
  }
  else{
    if(uflag==2){
      while(counter2>20){
        Serial.print("");
        ccommand="right";
        csymbolR=" +";
        csymbolL=" +";
        left();        
      }
    }
    else if(uflag==3){
      while(counter1>20){
        Serial.print("");
        ccommand="right";
        csymbolR=" +";
        csymbolL=" +";
        right();       
      }
    }
    else if(uflag==4){
      while(counter1>20){
        Serial.print("");
        ccommand="right";
        csymbolR=" +";
        csymbolL=" +";
        extremeleft();        
      }
    }
    else{
      while(counter1>20){
        Serial.print("");
        ccommand="right";
        csymbolR=" +";
        csymbolL=" +";
        extremeright();        
      }
    }
  }
}

void processCounters(){
  CC1=counter1;
  CF1=CC1-BC1;
  BC1=CC1;
  CC2=counter2;
  CF2=CC2-BC2;
  BC2=CC2;
  if (c>0){
    CLM[i]=CF1;
    CRM[j]=CF2;
    motion[k]=pcommand;
    Serial.print(pcommand);
    Serial.print(psymbolR);
    Serial.print(CLM[i]);
    Serial.print(" , ");
    Serial.print(psymbolL);
    Serial.println(CRM[j]);
    pcommand=ccommand;
    psymbolR=csymbolR;
    psymbolL=csymbolL;
    i=i+1;
    j=j+1;
    k=k+1;
    motion[k]=ccommand;
  }else{
    c=1;
    pcommand=ccommand;
    psymbolR=csymbolR;
    psymbolL=csymbolL;
  }
}

void lastcommand(){
  CC1=counter1;
  CF1=CC1-BC1;
  CC2=counter2;
  CF2=CC2-BC2;
  CLM[i]=CF1;
  CRM[j]=CF2;
  Serial.print(pcommand);
  Serial.print(psymbolR);
  Serial.print(CLM[i]);
  Serial.print(" , ");
  Serial.print(psymbolL);
  Serial.println(CRM[j]);
}

void forward(){
  analogWrite(enA, 255);
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH);
  analogWrite(enB, 255);
}

void right(){
  analogWrite(enA, 255);
  digitalWrite(in1, LOW);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH);
  analogWrite(enB, 255);
}
void rightreverse(){
  analogWrite(enA, 255);
  digitalWrite(in1, LOW);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);
  analogWrite(enB, 255);
}
void left(){
  analogWrite(enA, 255);
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  
  digitalWrite(in4, LOW);
  analogWrite(enB, 255);
}
void leftreverse(){
  analogWrite(enA, 255);
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);  
  digitalWrite(in4, LOW);
  analogWrite(enB, 255);
}
void extremeleft(){
  analogWrite(enA, 255);
  digitalWrite(in1, HIGH);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);  
  digitalWrite(in4, LOW);
  analogWrite(enB, 255);
}
void extremeright(){
  analogWrite(enA, 255);
  digitalWrite(in1, LOW);  
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);  
  digitalWrite(in4, HIGH);
  analogWrite(enB, 255);
}
void hold(){
  analogWrite(enA, 255);
  digitalWrite(in1, LOW);  
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  
  digitalWrite(in4, LOW);
  analogWrite(enB, 255);
}

void returnback(){
  hold();
  for (int fori=0; fori<i+1; fori++){
    Serial.print(CLM[fori]);
    Serial.print(" , ");
  }
  Serial.println("");
  for (int forj=0; forj<j+1; forj++){
    Serial.print(CRM[forj]);
    Serial.print(" , ");
  }
  Serial.println("");
  for (int fork=0; fork<k+1; fork++){
    Serial.print(motion[fork]);
    Serial.print(",");
  }
  
  int v=i; 
  for (int p=k; p<k+1 && p>-1; p--){
    Serial.println("");
//    Serial.println(motion[fork]);
    counter1=0;
    counter2=0;
    if(motion[p]=="forward"){
      while(CLM[v] >= counter1){
        Serial.print("forward");
        backward();
      }
    }
    else if(motion[p]=="backward"){
      while(CLM[v] >= counter1){
        Serial.print("backward");
        forward();
      }
    }
    else if(motion[p]=="right"){
      while(CLM[v] >= counter1){
        Serial.print("right");
        rightreverse();
      }
    }
    else if(motion[p]=="left"){ /// this is a lil changed
      while(CRM[v] >= counter2){
        Serial.print("left");
        leftreverse();
      }
    }
    else if(motion[p]=="extremeright"){
      while(CLM[v] >= counter1){
        Serial.print("extremeright");
        extremeleft();
      }
    }
    else if(motion[p]=="extremeleft"){
      while(CLM[v] >= counter1){
        Serial.print("extremeleft");
        extremeright();
      }
    }
    else{
      hold();
      Serial.println("else main hai");
    }
    v--;
    hold();
    delay(400);
  }
  hold();
  Serial.println("");
  Serial.println("returned back!");
  
  digitalWrite(resetPin,LOW); 
}
