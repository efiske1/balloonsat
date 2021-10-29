
/********************************************************
  PROCESS ONEWIRE TEMPERATURE SENSORS
*********************************************************/
                                                        //
void  processTemp() {                                   //
  stringAllTemps = "";                                  //  Clear old Temp data
                                                        //
  while ( ds.search(addr))                              //  Looks for invalid temp sensor address
  {                                                     //
                                                        //
    if (tIDPrint)                                       //  Print out temp sensor ID
    {                                                   //
      stringAllTemps += (", T(");                       //  Add each sensor's data to data string
      stringAllTemps += (addr[7]);                      //
      stringAllTemps += (")=");                       //
    }                                                   //  end if
                                                        //
    if (OneWire::crc8(addr, 7) != addr[7])              //
    {                                                   //
      Serial.println("CRC is not valid!");              //
      return;                                           //
    }                                                   //  end if
                                                        //
    ds.reset();                                         //
    ds.select(addr);                                    //
    ds.write(0x44, 1);                                  //
                                                        //
    present = ds.reset();                               //
    ds.select(addr);                                    //
    ds.write(0xBE);                                     //  Read Scratchpad
    for ( i = 0; i < 9; i++) {                          //  we need 9 bytes
      data[i] = ds.read();                              //
    }                                                   //  end for
                                                        //
    int16_t raw = (data[1] << 8) | data[0];             //  Convert the data to actual temperature because the result is a 16 bit
                                                        //  signed integer, it should be stored to an "int16_t" type, which is
                                                        //  always 16 bits even when compiled on a 32 bit processor.
    if (type_s) {                                       //
      raw = raw << 3;                                   //  9 bit resolution default
      if (data[7] == 0x10) {                            //
// "count remain" gives full 12 bit resolution          //
        raw = (raw & 0xFFF0) + 12 - data[6];            //
      }                                                 //  end if
    }                                                   //  end if
    else {                                              //
      byte cfg = (data[4] & 0x60);                      //  At lower res, the low bits are undefined, so let's zero them
      if (cfg == 0x00) raw = raw & ~7;                  //  9 bit resolution, 93.75 ms
      else if (cfg == 0x20) raw = raw & ~3;             //  10 bit res, 187.5 ms
      else if (cfg == 0x40) raw = raw & ~1;             //  11 bit res, 375 ms
// default is 12 bit resolution, 750 ms conversion time //
    }                                                   //  end else
    celsius = (float)raw / 16.0;                        //
    fahrenheit = celsius * 1.8 + 32.0;                  //
 //Uncomment to select Celsius and/or Farenheiht data   //
    //stringAllTemps+=(celsius);                        //
    //stringAllTemps+=(" C");                           //
    stringAllTemps += (fahrenheit);                     //
    //stringAllTemps += ("F");                          //
  }                                                     //  end while
  ds.reset_search();                                    //  After last valid temp is read reset for next time
}                                                       //  end function
                                                        //
/*********************************************************
  END PROCESS ONEWIRE TEMPERATURE SENSORS
*********************************************************/
