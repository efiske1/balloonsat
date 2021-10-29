
/*********************************************************
   SMART DELAY
*********************************************************/
// This custom version of delay() ensures that the      //
// gps objectis being "fed".                            //
                                                        //
static void smartDelay(unsigned long ms)                //
{                                                       //
  unsigned long start = millis();                       //
  do                                                    //
  {                                                     //
    while (GPSSerial.available())                       //
      gps.encode(GPSSerial.read());                     //
  } while (millis() - start < ms);                      //  end do
}                                                       //  end function
/*********************************************************
   END SMART DELAY
*********************************************************/
