/*********************************************************
  READ PRESSURE SENSOR
    Retrieves raw temp and pressure data from
        GY-63 MS5611-01BA03 Atmosphere Pressure Meter 
        Altimeter Sensor Module
    Converts temp to deg F and pressure to Pa
*********************************************************/
                                                        //
 void readPressureSensor() {                            //
   String PTemp = "" ;                                  //  Temporary variables to hold data. 
   String Prsur = "" ;                                  //  Allows sensor to only be read once, ensures both data strings have the same data
   int32_t pressure;                                    //
   stringPressure = "";                                 // Clears out any old data (starts a new string)
                                                        //
  /* Create string containing pressure sensor data by   //
   * concatenating labels and data into a single string */
                                                        //
   PTemp += (baro.getTemperature()*0.01*9/5+32);        //  Read Pressure Sensor Temp. 
   Prsur += (baro.getPressure()*0.01);                  //  Read Pressure 
   stringPressure += (", PSenT=");                      //
   stringPressure += (PTemp);                           //
   stringPressure += (", Pressure(Pa)=");               //  Comma between values makes it easier to manipulate data in Excel
   stringPressure += (Prsur);                           //
                                                        //
}                                                       //
                                                        //  end function
/********************************************************
  END READ PRESSURE SENSOR
*********************************************************/
