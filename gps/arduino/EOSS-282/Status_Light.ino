
 void Status_Light() {                            //  Flashes Status Light a selected number of line numbers
    stringBlink = "";                             //  Clears out any old data (starts a new string)
    int blinkCount = lineNum % flashInterval;     //  Modulo divide, blinkCount holds the remainder of the modulo divide
    if (lineNum < startupFlashTime){              //
      blinkCount = lineNum % startupFlashInterval;//  Flashes every startupFlashInterval sec until startupFlashTime sec after restart 
      }                                           //
                                                  //
     if (blinkCount == 0) {                       //     
          if (GPSposnFlag) {                      //  If GPS Position is good 
            digitalWrite(G_ledPin, HIGH);         //  turn the green LED on (HIGH is the voltage level)
            stringBlink += (", Flash G");         //  Append flag to message
          }                                       //
           else if (GPStimeFlag) {                //  If GPS Position is not good but Time is good
            digitalWrite(B_ledPin, HIGH);         //  turn the blue LED on (HIGH is the voltage level)
            stringBlink += (", Flash B");         //  Append flag to message      
          }                                       //
        else {  stringBlink += (", Flash R");     //  If neither Position or Time are good 
          digitalWrite(R_ledPin, HIGH);           //  turn the red LED on (HIGH is the voltage level)
        }                                         //
    }                                             //
    else {                                        //
        digitalWrite(R_ledPin, LOW);              //  Turns off led next time through loop
        digitalWrite(G_ledPin, LOW);              //  Turns off led next time through loop
        digitalWrite(B_ledPin, LOW);              //  Turns off led next time through loop
      }                                           //
}                                                 //
