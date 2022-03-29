int ledPin=8;
int ldr=10;
int ldrVal1;
int ldrVal2;
bool isPrint=false;
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int delayTime=150;
bool isFirstbit;
String bytesText="";
String bytes;
String text="";
bool isrun=true;
bool isSecond=true;
bool startProcess=false;

#define SPTR_SIZE   30
char   *sPtr [SPTR_SIZE];

int
separate (
    String str,
    char   **p,
    int    size )
{
    int  n;
    char s [1000];

    strcpy (s, str.c_str ());

    *p++ = strtok (s, " ");
    for (n = 1; NULL != (*p++ = strtok (NULL, " ")); n++)
        if (size == n)
            break;

    return n;
}



void setup(){
  Serial.begin(9600);
  pinMode(ledPin,OUTPUT);
  pinMode(ldr,INPUT);
  isFirstbit=true;
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("LIFI message");
  
  
}
void loop(){
  if(isFirstbit){
    clockbit();  
  }

  if(isSecond==true){
     bytesFormate();
     
  }
}




void bytesFormate(){
  while(bytes!="00001010"&& isrun && startProcess){
    bytes="";
     for(int i=0;i<8;i++){
         
         ldrVal1=digitalRead(ldr);
    
         if(ldrVal1==0){
            digitalWrite(ledPin,HIGH);
            Serial.print("0");
            
            bytes+=0;
         }
         else if(ldrVal1==1){
              digitalWrite(ledPin,LOW);
              Serial.print("1");
                bytes+=1;
         }
       
         delay(delayTime);
      }
      
    bytesText+= bytes;
    Serial.print(" ");
    bytesText+=" ";
    
    
    
    if(bytes=="00001010" || bytes=="00000000"){
       isSecond=false;
       isrun=false;
       
    }
    
  }
  if(bytes=="00001010"){
  
  String str=bytesText;
 int N = separate (str, sPtr, SPTR_SIZE);
    for (int n = 0; n < N; n++){
    long value = strtol(sPtr [n], NULL, 2);
    
//        Serial.println (sPtr [n]);

    text+=String(char(value));
    
    }  
    isPrint=true;
    
}
if(isPrint){
  Serial.println("");
Serial.print(text);
lcd.setCursor(0, 1);
  
  lcd.print(text);
 
}}

void clockbit(){
  ldrVal1=digitalRead(ldr);
  
     while(ldrVal1==0){
      digitalWrite(ledPin,HIGH);
        ldrVal2=digitalRead(ldr);
        
        if(ldrVal2==1){
          digitalWrite(ledPin,LOW);
           
           delay(delayTime/2);
           isFirstbit=false;
           startProcess=true;
           
           break;
      
        }
    
      
     }
  
}
