/*********************************************************
  READ REALTIME CLOCK
  Note: RTC is updated continuously when GPS is present,
        otherwise GPS shield updates internally.
*********************************************************/
                                                        //
void readRTC() {                                        //
  timeString = "";                                      //  clear old data
  dateString = "";                                      //  clear old data
                                                        //
  DateTime now = rtc.now();                             //  Read RTC
  if (gps.date.isUpdated())                             //  if GPS is valid update rtc
    {                                                   //
    rtc.adjust(DateTime(gps.date.year(),                //  
                        gps.date.month(),               //
                        gps.date.day(),                 //
                        gps.time.hour(),                //
                        gps.time.minute(),              //
                        gps.time.second()));            //
    }                                                   //
                                                        //
  if (((now.hour()-offsetUTC) < 10) && ((now.hour()-offsetUTC) > 0)) timeString += "0"; //  Add leading zero if needed
  if ((now.hour()-offsetUTC) ==0) timeString += "0"; //  Add another zero if hour is 00
  if ((now.hour()-offsetUTC) < 0) timeString += (now.hour()+24-offsetUTC); //

  else timeString += (now.hour()-offsetUTC);
  timeString += ":";                                    //
  if (now.minute() < 10)timeString += "0";              //  Add leading zero if needed
  timeString += (now.minute());                         //
  timeString += ":";                                    //
  if (now.second() < 10)timeString += "0";              //  Add leading zero if needed
  timeString += (now.second());                         //
                                                        //
  dateString += (now.day());                            // 
  dateString += (now.month());                          //
  dateString += (now.year());                           //                                              
}                                                       //  end function
                                                        //
/*********************************************************
  END READ REALTIME CLOCK
*********************************************************/
