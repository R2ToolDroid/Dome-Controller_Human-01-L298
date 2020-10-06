#include <Arduino.h>       

void resetM(){
   digitalWrite(ledPin1, LOW); 
   digitalWrite(ledPin2, LOW); 
   ledState1 = LOW;
   ledState2 = LOW;
   analogWrite(links, 0);  
   analogWrite(rechts, 0);  
}

int center(String dir) {
    /// Fuert den Dome in die Ausgangsposition //
   centerState = digitalRead(sensorCenter);  
   if (debug) {   
    Serial.print(F("CenterMode "));
    Serial.println(centerState);
   }
    analogWrite(rechts, 0); 
    analogWrite(links, 0); 
      
      while ( centerState == 0){

                 centerState = digitalRead(sensorCenter);  
                
                if (dir == "L" ) {
                  analogWrite(links, Rtempo); 
                  digitalWrite(ledPin2, HIGH);                  
                } 
                
                if (dir == "R") {
                  analogWrite(rechts, Rtempo); 
                  digitalWrite(ledPin1, HIGH); 
                }
                
                if (debug){Serial.println(F("try to get center"));Serial.print(sensorCenter);}
              
 
      }
   digitalWrite(ledPin1, LOW); 
   digitalWrite(ledPin2, LOW); 
   analogWrite(links, 0);  
   analogWrite(rechts, 0);  
   
   delay(200);
   durchlauf = 0;
   
   //Mode = 0; 
}

void FindRoTime(){
    //int rotime;
    center("L");
    if (debug){Serial.println(F("Dome ist Center"));}  
    delay(1000);
    zeit1 = millis();
    center("L");
    zeit2 = millis();
    if (debug){Serial.print(F("Zeit1_"));Serial.println(zeit1); Serial.print(F("Zeit2_")); Serial.println(zeit2);}
    rotime = zeit2-zeit1;
    if (debug){Serial.print(F("rotime_")); Serial.println(rotime);}
    Rpos = rotime/360; ///Rpos ist dann Winkel in Zeit Variable  90° also SUM*90;
    center("R");
    if (debug){Serial.print(F("Rpos_")); Serial.println(Rpos);}
}


void rotateR( int Rpos) {
  
     digitalWrite(ledPin1, HIGH); 
     analogWrite(links, 0); 
     analogWrite(rechts, Rtempo);
     delay (Rpos);
     digitalWrite(ledPin1, LOW); 
     analogWrite(links, 0); 
     analogWrite(rechts, 0);
          
}

void rotateL( int Rpos) {

     digitalWrite(ledPin2, HIGH); 
     analogWrite(rechts, 0); 
     analogWrite(links, Rtempo);
     delay (Rpos);
     digitalWrite(ledPin2, LOW); 
     analogWrite(links, 0); 
     analogWrite(rechts, 0);
    
  
}


int rcMove() {

    int sensorValue = pulseIn(sensorRC,HIGH);
    
    if (sensorValue >=800){ ///Check if Sensor is Connectet an RC on

    
    if (sensorValue < 1350){
      
     
      int Rtempo = map (sensorValue, 1460, 530,50,254);
     
      if (Rtempo >= 180) {Rtempo=255;}
         
     digitalWrite(ledPin2, HIGH); 
     analogWrite(links, 0); 
     analogWrite(rechts, Rtempo); 

     if (debug){ 
        Serial.println(F("Rechts"));
         Serial.print(F("RTempo "));Serial.println(Rtempo);
      } 
    
    
    } else if (sensorValue > 1650) {
          
     // set the LED with the ledState of the variable:
      digitalWrite(ledPin1, HIGH); 
      //tempo = sensorValue ;////6;
      int Ltempo = map(sensorValue, 1450,2400,50,254);
      //tempo = tempo /5;
      
      analogWrite(rechts, 0);  
      analogWrite(links, Ltempo); 
      if (debug) {
      Serial.println(F("Links"));
      Serial.print(F("LTempo "));Serial.println(Ltempo);
      }   
     
    }  else {
      analogWrite(links, 0);  
      digitalWrite(ledPin1, LOW); 
      analogWrite(rechts, 0); 
      digitalWrite(ledPin2, LOW);     
      //delay (zeit);    
    }

    }///End Sensor Check
    
  if (debug) { 
    //Serial.print(F("Tempo "));Serial.println(tempo);
    //Serial.print(F("Value "));Serial.println(sensorValue);
    }
  
}

void randomMove() {
 
   // print a random number from 0 to 299
  zeit = random(3000, 6000)+(temp-20)*faktor;
  
  // print a random number from 10 to 19
  randNumber = random(10, 40);
  //Speed
  tempo = random(90,120);
  //Moving länge
  moving = random(500,1500);
 
  if (randNumber < 20){     ///Drehung Links
    if (debug){
    Serial.println(F("Links"));
     Serial.println(randNumber);
    }
     // set the LED with the ledState of the variable:
     digitalWrite(ledPin2, HIGH);
     analogWrite(links, tempo);  
     delay(moving);
     analogWrite(links, 0);  
     digitalWrite(ledPin2, LOW);
     delay(500);
    
    } else if (randNumber > 20 && randNumber <= 30) {  ///Rechts Drehung

     if (debug) {
      Serial.println(F("rechts"));
      Serial.println(randNumber);
     }
     // set the LED with the ledState of the variable:
      digitalWrite(ledPin1, HIGH);   
      analogWrite(rechts, tempo); 
      delay(moving);      
      digitalWrite(ledPin1, LOW); 
      analogWrite(rechts, 0); 
      delay(500);
      
    }  else {
      
      analogWrite(links, 0);  
      analogWrite(rechts, 0); 
      digitalWrite(ledPin1, LOW); 
      digitalWrite(ledPin2, LOW); 
      delay (zeit);  
    }

  if (debug) {
      Serial.print(F("Zeit "));
      Serial.println(zeit);
      Serial.print(F("Druchlauf "));
      Serial.println(durchlauf);
      Serial.print(F("Temp0 "));
      Serial.println(tempo);
      Serial.print(F("Temp "));
      Serial.println(temp);
      Serial.print(F("Faktor "));
      Serial.println(temp*faktor);
  }
 
}


void human(){
     if (movementSensor.dataReady()) {
        ir1 = movementSensor.getRawIR1();
        ir2 = movementSensor.getRawIR2();
        ir3 = movementSensor.getRawIR3();
        ir4 = movementSensor.getRawIR4();
        temp = movementSensor.getTMP();
        movementSensor.startNextSample();
        Sdiff = ir2 - ir4 ; ///Differenz

        int gap = 250;  /// Lücke wo nichts verfolgt wird

        int range = ir2+ir4;  /// Abstand

        if (range < 0 ) {
           // gap = 200;
            } else {
           //   gap = 400;
            }

      // if (range > 3000) { //here}
        
        if (debug)
        {  
        //Serial.print(F("1:BOT["));
        //Serial.print(ir1);
        Serial.print(F(" 2:RH["));
        Serial.print(ir2);
        //Serial.print(F("], 3:TOP["));
        //Serial.print(ir3);
        Serial.print(F("], 4:LH["));
        Serial.print(ir4);
        //Serial.print(F("], temp["));
        //Serial.print(temp);
        Serial.print(F("], diff["));
        Serial.print(Sdiff);    
        Serial.print(F("]"));
        //Serial.print(F("], millis["));
        //Serial.print(millis());
        //Serial.print(F("]"));

        Serial.print("----range");
        Serial.print(range);
        Serial.print("----gap");
        Serial.print(gap);
        Serial.println();
        }        
        ///////////////////////////////////////
        //Bewegungs Kalkulation
        ///////////////////////////////////////
        //Bei RH Impulse nach rechts drehen bis LH Impuls gleich ist
           
        byte diff = false;

        

        if ((vpos > 1800) || (vpos < 500)){
          vpos = 1000;        
        }

        if ((Sdiff >= gap)||(Sdiff <= -gap)){ diff = true;}

        if (diff){

           if (ir4 > ir2){ ////turn right
                Serial.println("Dreh nach Rechts");
                digitalWrite(ledPin2, HIGH);  //Dreh nach R
                analogWrite(links,Htempo); 
                servoDispatch.moveTo(0,50,0,500);
           }    
           
            if (ir2 > ir4){ ////turn left
                Serial.println("Dreh nach links");
                digitalWrite(ledPin1, HIGH);  //Dreh nach L
                analogWrite(rechts,Htempo); 
                servoDispatch.moveTo(0,50,0,1200);
           } 
        } else {
          analogWrite(rechts, 0); 
          analogWrite(links, 0); 
          digitalWrite(ledPin2, LOW);  //Dreh nach L
          digitalWrite(ledPin1, LOW);  //Dreh nach R
          
          Serial.println("--Mitte--");
          
          
        }
        
        //servoDispatch.moveTo(0,0,0,1000);
      
    }
    
  
}
