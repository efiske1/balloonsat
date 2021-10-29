
/*********************************************************
   TINYGPS
*********************************************************/
                                                        //
void  TinyGPS() {                                       //
    GPStimeFlag = 0;                                    //  Clear Status Flags
    GPSposnFlag = 0;                                    //
                                                        //
  positionGPS = ", GPS_Age=Old";                        //  Clear old data and default for time NOT valid
   if (gps.time.age()<2000)                             //  if GPS time is valid update rtc and print to file
    {                                                   //
    GPStimeFlag=1;                                      //  Set Time Status Flag
    positionGPS = ", UT(GPS)=,";                        //
    if (gps.time.hour() < 10) positionGPS += "0";       //  If hour < 10 add leading 0
    positionGPS += gps.time.hour();                     // 
    positionGPS += ":";                                 //
    if (gps.time.minute() < 10) positionGPS += "0";     //  If minute < 10 add leading 0
    positionGPS += gps.time.minute();                   //  
    positionGPS += ":";                                 //
    if (gps.time.second() < 10) positionGPS += "0";     //  If second < 10 add leading 0
    positionGPS += gps.time.second();                   //
    }                                                   //
                                                        //
  positionGPS += ", #Sats=,";                           //
  if (gps.satellites.isUpdated())                       //
    { if (gps.satellites.value()<10) positionGPS += "0";//  prepend a 0 if # Sats is <10
      positionGPS += gps.satellites.value();            //
    }                                                   //
  else positionGPS += "**";                             //  
  if (gps.location.isValid())                           //
   {                                                    //
    GPSposnFlag = 1;                                    //  Set Position Status Flag
    positionGPS += ", Lat(deg)=,";                      //
    positionGPS += (String(gps.location.lat(), 5));     //  If gps.location.lat and gps.location.lon are just appended to the string they
    positionGPS += ", Lon(deg)=,";                      //
    positionGPS += (String(gps.location.lng(), 5));     //  converting to a string with 5 decimal places before concatination.
    positionGPS += ", Alt(ft)=,";                       //
    positionGPS += gps.altitude.feet();                 //
    positionGPS += ", (m)=,";                           //  Uncomment desired units
    positionGPS += gps.altitude.meters();               //
//    positionGPS += ", V(mph)=,";                        //
//    positionGPS += gps.speed.mph();                     //
//    positionGPS += ", Heading(deg)=,";                  //
//    if (gps.course.deg() < 10) positionGPS += "0";      //  If heading < 10 add leading 0
//    if (gps.course.deg() < 100) positionGPS += "0";     //  If heading < 100 add leading 0
//    positionGPS += gps.course.deg();                    //
  }                                                     //  end if
                                                        //
  if(0){                                                // Turn on/off status flags 
    positionGPS += ",Time/Position Flags=, ";           //
    positionGPS += GPStimeFlag;                         //
    positionGPS += GPSposnFlag;                         //
  }                                                     //
                                                        //
 }                                                      //  end function
/*********************************************************
   End TINYGPS
*********************************************************/
