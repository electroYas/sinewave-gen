/* 50Hz generator , pure sinewave*/

#define SIG1_PIN 2
#define SIG2_PIN 3
#define period 200
#define SEGMENTS 50

const float table[100]={0.01,0.06,0.13,0.19,0.25,0.31,0.37,0.43,
0.48,0.54,0.59,0.64,0.68,0.73,0.77,0.81,0.84,0.88,
0.90,0.93,0.95,0.97,0.98,0.99,0.99,0.99,0.99,0.99,
0.98,0.97,0.95,0.93,0.90,0.88,0.84,0.81,0.77,0.73,
0.68,0.64,0.59,0.54,0.48,0.43,0.37,0.31,0.25,0.19,
0.13,0.06};

float table1[50]; 
int table2[50];
int table_inv[50];

int state=0;

void setup(){
  Serial.begin(9600);
  pinMode(SIG1_PIN,OUTPUT);
  pinMode(SIG2_PIN,OUTPUT);
  pinMode(13,OUTPUT);
  digitalWrite(SIG1_PIN,LOW);
  digitalWrite(SIG2_PIN,LOW);
  
  for(int i=0;i<SEGMENTS;i++){
    table1[i]=(float)table[i]*(float)period;
  }
  
  for(int i=0;i<SEGMENTS;i++){
    table2[i]=(int)table1[i];
    Serial.print(table2[i]);
    Serial.print(',');
  }
   Serial.println();
  
  for(int i=0;i<SEGMENTS;i++){
    table_inv[i]=period-table2[i];
    Serial.print(table_inv[i]);
    Serial.print(',');
  }
  Serial.println();
  
}

void loop(){
   digitalWrite(13,state);
   state=!state;
  for(int i=0;i<SEGMENTS;i++){
    digitalWrite(SIG1_PIN,HIGH);
    
    delayMicroseconds(table2[i]);
    digitalWrite(SIG1_PIN,LOW);
    
    delayMicroseconds(table_inv[i]);
 
  }
 
  
  for(int i=0;i<SEGMENTS;i++){
    digitalWrite(SIG2_PIN,HIGH);
   
    delayMicroseconds(table2[i]);
    
    digitalWrite(SIG2_PIN,LOW);
  
    delayMicroseconds(table_inv[i]);
 
  }
 // while(1);
 
  
  
}
