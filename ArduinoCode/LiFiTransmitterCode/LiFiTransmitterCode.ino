String myText;
int delayTime=150;
int laserPin=12;

void setup() {
  
  pinMode(laserPin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter text you want to send .. or type exit");
  
  while(Serial.available()==0){
    
  }
  myText=Serial.readString();
  
  while(myText!="exit"){
    digitalWrite(laserPin,HIGH);
    delay(1000);
    digitalWrite(laserPin,LOW);
  for(int i=0;i<myText.length();i++){
    char myChar=myText[i];
    for(int i=7;i>=0;i--){
      byte bytes=bitRead(myChar,i);
      Serial.print(bytes);
      if(bytes==1){
        digitalWrite(laserPin,HIGH);
        
        delay(delayTime);
      }
      else if(bytes==0){
        digitalWrite(laserPin,LOW);
        delay(delayTime);
      }
      
    
    
      }
      
      
    Serial.print(" ");
  }
  Serial.println("");
  Serial.println("the end");
  
   digitalWrite(12,LOW);
  Serial.println("Enter text you want to send .. or type exit");
  
  while(Serial.available()==0){
    
  }
  myText=Serial.readString();
  }
}


void loop() {
  
              
}
