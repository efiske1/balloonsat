/*********************************************************
  READ OZONE VOLTAGE
  Reads voltage A10 pins and reports it back in a string.

  MQ131 Ozone Gas  Sensor Module connected to Pin A10 
  (Yellow wire on Aux Connector)

 ********************************************************/
                                                        //
void readOzoneVoltage() {                              //
  float OzoneVolts;                                     //
  int sensorValue;                                      //
  stringOzoneVoltage = "";                              //  Clears out any old data (starts a new string)
                                                        //
  /*  Create string containing pressure sensor data     //
      by concatenating labels and data                  //
      into a single string                              //
  */                                                    //
                                                        //
                                                        //
     sensorValue = analogRead(A10);                     // Analog pin data is reported as an integer in the range of 0-1023
     OzoneVolts = sensorValue*5.0/1023.0;               //
     stringOzoneVoltage += (", (MQ131 V) = ");          //
     stringOzoneVoltage += (OzoneVolts);                //
     stringOzoneVoltage += ("V");                       //
                                                        //
}                                                       //  end function
                                                        //
/*********************************************************
  END READ ANALOG VOLTAGES
*********************************************************/
