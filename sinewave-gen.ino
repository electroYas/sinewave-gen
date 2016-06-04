/* 50Hz generator , pure sinewave*/

#define SIG1_PIN 2
#define SIG2_PIN 3
#define SEGMENTS 50
#define DIVITIONS SEGMENTS*2

float table[50];
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
    table[i] = sin(i*(2*PI/DIVITIONS));
  }
  changeFrequency(50);
  
 
  
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
  
  
}

void changeFrequency(float freq){
  float sub_period = 1000000.0/(freq*DIVITIONS);
  
   for(int i=0;i<SEGMENTS;i++){
    table1[i]=(float)table[i]* sub_period;
  }
  
  for(int i=0;i<SEGMENTS;i++){
    table2[i]=(int)table1[i];
    if(table2[i]== 0) table2[i]=1;
    Serial.print(table2[i]);
    Serial.print(',');
  }
   Serial.println();
  
  for(int i=0;i<SEGMENTS;i++){
    table_inv[i]=(int)sub_period-table2[i];
    Serial.print(table_inv[i]);
    Serial.print(',');
  }

}
