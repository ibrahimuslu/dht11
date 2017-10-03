#include <SimpleDHT.h>

#include <EEPROM.h>


// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 2
int pinDHT11 = 18;
int relay1 = 8;
int relay2 = 9;
SimpleDHT11 dht11;
int tempUpTreshold = EEPROM.read(0);
int humUpTreshold = EEPROM.read(1);
int tempDownTreshold = EEPROM.read(2);
int humDownTreshold = EEPROM.read(3);
String newVal=""; 
void setup() {
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  Serial.begin(115200);
  Serial.println("=================================");
  Serial.println("Sicaklik ve Nem Takibi ...");
  Serial.println("=================================");
  Serial.print("Sicaklik Ust Esik Degeri : ");
  Serial.println((int)tempUpTreshold);
  Serial.print("Sicaklik Alt Esik Degeri : ");
  Serial.println((int)tempDownTreshold);
  Serial.print("Nem Ust Esik Degeri : ");
  Serial.println((int)humUpTreshold);
  Serial.print("Nem Alt Esik Degeri : ");
  Serial.println((int)humDownTreshold);
  Serial.println("=================================");
  Serial.println("Mevcut sicaklik degerini gormek icin          '1' girin ");
  Serial.println("Mevcut nem degerini gormek icin               '2' girin ");
  Serial.println("Sicaklik Ust Esik Degeri degistirmek icin     '3' ile birlikte esik degerini girin Ornek:( 3 35 ) ");
  Serial.println("Sicaklik Alt Esik Degeri degistirmek icin     '4' ile birlikte esik degerini girin Ornek:( 4 12 ) ");
  Serial.println("Nem Ust Esik Degeri degistirmek icin          '5' ile birlikte esik degerini girin Ornek:( 5 35 ) ");
  Serial.println("Nem Alt Esik Degeri degistirmek icin          '6' ile birlikte esik degerini girin Ornek:( 6 15 ) ");
  Serial.println("Sicaklik ve Nem Esik Degerlerini gormek icin  '7' girin ");
  Serial.println("=================================");
}

void loop() {
  // start working...
  //Serial.println("=================================");
  //Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  if (dht11.read(pinDHT11, &temperature, &humidity, NULL)) {
    Serial.print("Read DHT11 failed.");
    
    return;
  }
  
  //Serial.print("Sample OK: ");
  //Serial.print((int)temperature); Serial.print(" *C, "); 
  //Serial.print((int)humidity); Serial.println(" %");
  while (Serial.available()) 
        {  
          char input = Serial.read();
          switch(input){
            case '1':
              Serial.print((int)temperature); Serial.print(" *C, "); 
              break;
            case '2':
               Serial.print((int)humidity); Serial.println(" %");
               break;
            case '3':
              Serial.print(" Sicaklik ust esik degeri girin: ");
              while (Serial.available()) 
              {  
                 newVal = Serial.readString();
                
                if(newVal.toInt()==0){
                  Serial.println(" Bir deger girmediniz!");
                  return;
                }else{
                  Serial.println(newVal.toInt());
                  tempUpTreshold = newVal.toInt();
                   EEPROM.write(0, tempUpTreshold);
                }
              }
              break;
            case '4':
              Serial.println(" Sicaklik alt esik degeri girin: ");
              while (Serial.available()) 
              {  
                 newVal = Serial.readString();
                Serial.print(newVal);
                 if(newVal.toInt()==0){
                  Serial.println(" Bir deger girmediniz!");
                  return;
                }else{
                  Serial.println(newVal.toInt());
                  tempDownTreshold = newVal.toInt();
                  
                   EEPROM.write(2, tempDownTreshold);
                }
              }
              break;
              case '5':
              Serial.println(" Nem ust esik degeri girin: ");
              while (Serial.available()) 
              {  
                 newVal = Serial.readString();
                Serial.print(newVal);
                if(newVal.toInt()==0){
                  Serial.println(" Bir deger girmediniz!");
                  return;
                }else{
                  Serial.println(newVal.toInt());
                  humUpTreshold = newVal.toInt();
                   EEPROM.write(1, humUpTreshold);
                }
              }
              break;
              case '6':
              Serial.println(" Nem alt esik degeri girin: ");
              while (Serial.available()) 
              {  
                 newVal = Serial.readString();
                Serial.print(newVal);
                if(newVal.toInt()==0){
                  Serial.println(" Bir deger girmediniz!");
                  return;
                }else{
                  Serial.println(newVal.toInt());
                  humDownTreshold = newVal.toInt();
                   EEPROM.write(3, humDownTreshold);
                }
              }
              break;
            case '7' :
                  Serial.print("Sicaklik Ust Esik Degeri : ");
                  Serial.println((int)tempUpTreshold);
                  Serial.print("Sicaklik Alt Esik Degeri : ");
                  Serial.println((int)tempDownTreshold);
                  Serial.print("Nem Ust Esik Degeri : ");
                  Serial.println((int)humUpTreshold);
                  Serial.print("Nem Alt Esik Degeri : ");
                  Serial.println((int)humDownTreshold);
                  break;
          }
        }
        // =================================================
        Serial.print((int)temperature); Serial.print(" *C, "); Serial.print((int)humidity); Serial.println(" %");
  if((int)temperature > tempUpTreshold){
    
    digitalWrite(relay1,HIGH);
  }
 else  if((int)temperature <= tempUpTreshold){
    if((int)temperature < tempDownTreshold){
    
    digitalWrite(relay1,HIGH);
  }
 else  if((int)temperature >= tempDownTreshold){ // her ikisi de degilse 
  
    digitalWrite(relay1,LOW);
 }
 }
 
        // =================================================
 if((int)temperature < tempDownTreshold){
    
    digitalWrite(relay1,HIGH);
  }
 else  if((int)temperature >= tempDownTreshold){
   if((int)temperature > tempUpTreshold){
    
    digitalWrite(relay1,HIGH);
  }
 else  if((int)temperature <= tempUpTreshold){
    digitalWrite(relay1,LOW);
    }
 }
 
        // =================================================
        
 if((int)humidity > humUpTreshold){
    
    digitalWrite(relay2,HIGH);
  }
 else  if((int)humidity <= humUpTreshold){
  
    if((int)humidity < humDownTreshold){
    
    digitalWrite(relay2,HIGH);
  }
 else  if((int)humidity >= humDownTreshold){
  
    digitalWrite(relay2,LOW);
 }
 }
 
        // =================================================
 if((int)humidity < humDownTreshold){
    
    digitalWrite(relay2,HIGH);
  }
 else  if((int)humidity >= humDownTreshold){
  if((int)humidity > humUpTreshold){
    
    digitalWrite(relay2,HIGH);
  }
 else  if((int)humidity <= humUpTreshold){
    digitalWrite(relay2,LOW);
 }
 }
  // DHT11 sampling rate is 1HZ.
  delay(1000);
}
