  /**************************************************************************************************
  *                                                                                                 *
  *  Balloonsat Delbruck Computer Code                                                              *
  *  by Randy Owen                                                                                  *
  *   Jan 2017                                                                                      *
  *   Oct 2017                                                                                      *
  *   Mar 2018                                                                                      *
  *   Oct 2018                                                                                      *
  *                                                                                                 *
  *   NOTE: This was coded for an ARDUINO MEGA                                                      *
  *   it is too large to run on an ARDUINO UNO                                                      *
  *                                                                                                 *
  *   Code reads:                                                                                   *
  *     -- a pressure sensor                                                                        *
  *     -- OneWire temperature sensors                                                              *
  *     -- GPS receiver breakout miniboard                                                          *
  *    All data is logged to the Serial Monitor                                                     *
  *    GPS altitide is used                                                                         *
  *                                                                                                 *
  **************************************************************************************************/
  
  /**************************************************************************************************
  *                                                                                                 *
  *  Implemented with Adafruit Ultimate GPS Logger Shield - PRODUCT ID: 1272                        *
  *    see www.adafruit.com/products/1272                                                           *
  *                                                                                                 *
  *                                                                                                 *
  *   TinyGPS++  by Mikal Hart used with permission                                                 *
  *   see http://arduiniana.org/libraries/tinygpsplus/                                              *
  *                                                                                                 *
  *                                                                                                 *
  *    Ensure GPS Module TX/RX are connected to Arduino Serial 1 RX/TX                              *
  *                 GPS Module   to   Arduino       *******************************                 *
  *                   Rx   -  Pin 18 (TX1)          *** Note: Connections are   ***                 *
  *                   Tx   -  Pin 19 (RX1)          *** Rx -> TX1  &  Tx -> RX1 ***                 *
  *                                                 *******************************                 *
  *                                                                                                 *
  *     Note: GPS Shield has an Arduino Uno pinout.                                                 *
  *        DO NOT USE Mega pins 7 and 8 (Analog 7 & 8) for anything else                            *
  *        since the GPS shield is using the same pins for TX and RX.                               *
  *        Some Delbruck board GPS shields have pins 7 and 8 removed.                               *
  *                                                                                                 *
  **************************************************************************************************/
  
  /**************************************************************************************************
  *                                                                                                 *
  *   Pressure Sensor Connection:                                                                   *
  *             GY63/GY86  to   Arduino                                                             *
  *   Power       VCC             5v                                                                *
  *   Ground      GND             GND                                                               *
  *   I2C clock   SCL             SCL                                                               *
  *   I2C data    SDA             SDA                                                               *  
  *                                                                                                 *
  **************************************************************************************************/

  /**************************************************************************************************
  *    RGB Status LED outputs controlled in Status_Lights Loop                                      *
  *       Color    Arduino Pin                                                                      *
  *        Red        pin A3                                                                        *
  *        Green      pin A4                                                                        *
  *        Blue       pin A5                                                                        *
  *                                                                                                 *
  **************************************************************************************************/

  /**************************************************************************************************
  * The SD card is attached to SPI bus as follows:                                                  *
  *  Arduino Mega:                                                                                  * 
  *    MOSI - pin 51                                                                                *
  *    MISO - pin 50                                                                                *
  *     CLK - pin 52 and pin #52 (SS) must be an output                                             *
  *      CS - pin 53 (CS pin can be changed)                                                        *
  *                                                                                                 *
  *    Copied from public domain Arduino SD Example code                                            *
  *    original code created 24 Nov 2010 and modified 9 Apr 2012 by Tom Igoe.                       *
  *                                                                                                 *
  **************************************************************************************************/

  /* Previous Versions:
    String SW_Ver = "5.1.1";                            //  1 May 16 - Added UV Sensor
    String SW_Ver = "5.2.1";                            //  2 May 16 - Changed Pressure to String Messaging
    String SW_Ver = "5.2.2";                            //  2 May 16 - Changed checkBell to String Messaging
    String SW_Ver = "5.2.3";                            //  2 May 16 - Changed readUV() to String Messaging
    String SW_Ver = "5.2.4";                            //  2 May 16 - Added GPS Fix to Position String
    String SW_Ver = "5.2.5";                            //  2 May 16 - Changed calcAltitude() to String Messaging
    String SW_Ver = "5.2.6";                            //  2 May 16 - Copy of 5.2.5 for troubleshooting why time has become erratic
    String SW_Ver = "5.2.7";                            //  2 May 16 - Fixed Lat/Lon 4 sig digit issue
    String SW_Ver = "5.3.0";                            //  3 May 16 - Added Line Break to logfile
    String SW_Ver = "5.3.2";                            //  3 May 16 - Added Line Break to Pressure Calibration Message in logfile
    String SW_Ver = "512.1";                            // 12 May 16 - Added HABfile # printout
    String SW_Ver = "512.2";                            // 12 May 16 - Fixed Formating to make data processing easier
    String SW_Ver = "8.6.1";                            //  6 Aug 16 - Localized some variables, removed all bell associated code
    String SW_Ver = "10.20.1";                          // 20 Oct 16 - Removed Matrix display, Removed UV sensor processing, Removed altitude calculation
    String SW_Ver = "10.20.2";                          // 20 Oct 16 - Added HC-SR04 Sonar Processing, Removed Matrix display, Removed UV sensor processing, Removed altitude calculation                                                      //
    String SW_Ver = "10.21.1";                          // 21 Oct 16 - Cleaned up location display accuracy calculations, deleted unused code, fixed some comments
    String SW_Ver = "10.28.1";                          // 28 Oct 16 - Deleted sonar
    String SW_Ver = "1.19.1";                           //  1 Jan 17 - Added SD card reader, removed colons from line numbers (Excel confuses with times, added commas between fields
    String SW_Ver = "2.11.1";                           // 11 Feb 17 - Added real-time clock functionality so time will display when GPS not fixed, deleted GPS time/date manipulation
    String SW_Ver = "2.11.2";                           // 11 Feb 17 - Automatic logfile naming based on the date
    String SW_Ver = "3.10.1";                           // 10 Mar 17 - Changed GPS engine to TinyGPS++
    String SW_Ver = "3.10.2";                           // 10 Mar 17 - Added Sonar Back
    String SW_Ver = "3.14.1";                           // 10 Mar 17 - Added correct date/time for SD Logfile creation
    String SW_Ver = "3.21.1";                           // 10 Mar 17 - Enabled Sonar
    String SW_Ver = "4.08.1";                           //  8 Apr 17 - Repaired readSONARs loop and deleted some unused code
    String SW_Ver = "4.08.2";                           //  8 Apr 17 - Sonar commented out
    String SW_Ver = "4.10.1";                           //  8 Apr 17 - Added function to read and log 6 analog voltages
    String SW_Ver = "4.15.3";                           //  8 Apr 17 - Fixed Analog voltage scaling
    String SW_Ver = "6.11.1";                           //  11 Jun 17 - Commented out Pressure and Removed Sonar
    String SW_Ver = "6.15.3";                           //  15 Jul 17 - Added ROCKBlock Position Output String
    String SW_Ver = "6.15.4";                           //  15 Jul 17 - Added ROCKBlock Code
    String SW_Ver = "6.21.1";                           //  21 Jul 17 - Replaced Time.h  with TimeLib.h and added back the monthStr() calls (which changes a numeric month to a text string)
    String SW_Ver = "6.21.2";                           //  21 Jul 17 - Added control parameter 'RBSep' which is an integer and is used to control how often RockBlock telemeter string is transmitted to ground
    String SW_Ver = "6.22.2";                           //  22 Jul 17 - Added RockBlock
    String SW_Ver = "6.29.2";                           //  22 Jul 17 - Working RockBlock Downlink
    String SW_Ver = "6.29.3";                           //  22 Jul 17 - Reformatted RBPositionGPS
    String SW_Ver = "6.29.4";                           //  22 Jul 17 - Added RockBlock Servo
    String SW_Ver = "7.3.2";                            //  22 Jul 17 - Added RockBlock Servo
    String SW_Ver = "7.3.5_Temp";                       //  22 Jul 17 - RBTemp
    String SW_Ver = "7.23.1";                           //  23 Jul 17 - Added 'Body()' function and RockBLOCK callback to keep data logging while waiting
    String SW_Ver = "Flight_Code-v7-24_C_R";            //  24 Jul 17 - Minimal missiom functionaliy. Callback is disabled.
    String SW_Ver = "7.25.1";                           //  25 Jul 17 - Starting point. Same as previous version
    String SW_Ver = "7.25.2";                           //  25 Jul 17 - Added pressure and Analog (Battery) voltage to RockBLOCK string. Controlled by flags
    String SW_Ver = "7.26.1";                           //  26 Jul 17 - Fixed Logfile name, fix logiing RockBLOCK messages, RockBLOCK Tx/Rx time chnaged to 180 sec
    String SW_Ver = "7.27.9";                           //  26 Jul 17 - Added ServoHeat function
    String SW_Ver = "10.09.1";                          //  09 Oct 17 - Updated for Fall Flight
    String SW_Ver = "10.11.1";                          //  09 Oct 17 - Removed ROCKBlock code
    String SW_Ver = "10.11.2";                          //  09 Oct 17 - Psensor Commented out
    String SW_Ver = "10.18.2";                          //  18 Oct 17 - Added Pressure Sensor 
    String SW_Ver = "10.21.1";                          //  21 Oct 17 - Fixed Problem with time, changed #include "RTClib.h" to #include <RTClib.h>
    String SW_Ver = "10.31.1";                          //  31 Oct 17 - Added logging GPS time when valid, prepended zeros to #Sats and Heading so # digits in data is constant, removed extra spaces around "=" for some lables
    String SW_Ver = "10.31.2";                          //  31 Oct 17 - Fixed update of UTC to = GPS time when GPS is valid
    String SW_Ver = "11.01.2";                          //  01 Nov 17 - Added timeOffset control parameter to adjust time for MDT or MST
    String SW_Ver = "03.18.1";                          //  18 Mar 18 - Copied to Spring_18 Folder
    String SW_Ver = "03.21.1";                          //  21 Mar 18 - Fixed problem displaying time when hour = 00, changed file name to DATA-###.TXT
    String SW_Ver = "03.23.1";                          //  23 Mar 18 - FLIGHT Version - handles file names with three digit extension (0-999)
    String SW_Ver = "10.09.2";                          //  10 Oct 18 - Added Sonar from v4-8-3 back in
    String SW_Ver = "10.24.1A";                         //  24 Oct 18 - TQ131 sensor to A10 and commented out Sonar 
    String SW_Ver = "10.25.1";                          //  25 Oct 18 - DIYmall NEO-6M GPS Module Test Code  
    String SW_Ver = "10.25.2";                          //  25 Oct 18 - Added code to write to standalone SD card data logger 
    String SW_Ver = "18.01.1";                          //  25 Oct 18 - Changed version numbering to just be year followed by version number
    String SW_Ver = "18.01.3";                          //  25 Oct 18 - Added Status Lights (RGB -> A3,A4,A5) and control flags GPSposnFlag and GPStimeFlag
    String SW_Ver = "20.3.14.10";                       //  14 Oct 20 - Renamed Code flown in EOSS 282
  */
    String SW_Ver = "20.3.22.01";                       //  14 Oct 20 - WORKS Configures NEO-6M GPS to Flight Mode so GPS should work up to 50,000km
    String SW_Comment = "\tConfigures NEO-6M GPS to Flight Mode.\n";  //  
                                                        //
  /******************************************************
  *    Include Libraries
  *******************************************************/
  #include <avr/pgmspace.h>                             //
  #include <avr/sleep.h>                                //  25Apr16
  #include <TimeLib.h>                                  //  21Jun17  Replaced 'Time.h' to fix problems with IDE releases after 1.6.1
  #include <math.h>                                     //  needed for the round() function
  #include <Wire.h>                                     // 
  #include <OneWire.h>                                  //  for onewire sensor processing
  #include <SPI.h>                                      //  for datalogger
  #include <SD.h>                                       //  for datalogger
  #include <RTClib.h>                                   //  11Feb17
  #include <TinyGPS++.h>                                //  TinyGPSPlus-1.0.2 - Version: Latest 
  #include <PString.h>                                  // 
  #include <MS5611.h>                                   //  for MS5611 Pressure Sensor Module 
                                                        //
  /*******************************************************
  *    END Include Libraries
  *******************************************************/
                                                        //
                                                        //
  TinyGPSPlus gps;                                      // The TinyGPS++ object 
  MS5611 baro;                                          // barometer object
                                                        //
                                                        //
  /*******************************************************
  *    Definitions
  *******************************************************/
                                                        //
  // **** GPS Definitions ***************************** //  
 /******************************************************
  * For Arduino Nano Uncomment two lines below this box * 
  *                                                     *
  *   GPS to Nano                                       *
  *    Rx - RX                                          * 
  *    Tx - Tx                                          *
  ******************************************************/
  //static const int RXPin=4, TXPin=3;                    // Software Serial Port Pins Setup (Arduino Data Pins)
  //SoftwareSerial GPSSerial(RXPin,TXPin);                // GPS port Object

  /******************************************************
  * For Arduino Mega Uncomment line below this box      *                                                                                                 *
  * Ensure GPS Module TX/RX are connected to Arduino    *
  * Serial 1 RX/TX                                      *
  *                                                     *
  *   GPS to Arduino     *****************************  *
  *    Rx - Pin 18 (TX1) ** Note: Connections are   **  *
  *    Tx - Pin 19 (RX1) ** Rx -> TX1  &  Tx -> RX1 **  *
  *                      *****************************  *
  *******************************************************/
  #define GPSSerial Serial1                             // 
  byte gps_set_sucess = 0 ;                             // GPS Load success flag
                                                        //
                                                        //
  #define GPSECHO  false                                //  Set GPSECHO to 'false' to turn off echoing the GPS data to the Serial console
                                                        //  Set to 'true' if you want to debug and listen to the raw GPS sentences
  #define LOG_FIXONLY false                             //  set to true to only log to SD when GPS has a fix, for debugging, keep it false */
                                                        //  off by default!
  #define chipSelect 53                                 //  ChipSelect pin used by the SD Data Shield 
                                                        //
  File logfile;                                         //  File for logging data
                                                        //
  static const uint32_t GPSBaud = 9600;                 //  GPS Card Baud Rate
                                                        //
  // **** Other Definitions *************************** //        
                                                        //
  int OneWireTempPin   = 4;                             //  Input pin for OneWire Temp Sensors - connect a 4.7K pullup resistor from pin to Arduino +5
                                                        //                                                          
  #define R_ledPin A3                                   //  Red LED Pin Used in Status_Light subrouting
  #define G_ledPin A4                                   //  Green LED Pin Used in Status_Light subrouting
  #define B_ledPin A5                                   //  Blue LED Pin Used in Status_Light subrouting
 
 /***********************************************************************************************************************
  *    String Variables used to accumulate various telemetry parameters.
  *    Strings are concatinated and saved to the SD card and printed on the serial monitor
  ************************************************************************************************************************/
                                                        //
  String positionGPS = "";                              //  String for assembling GPS position, altitude, speed angle, #sats
  String stringPressure = "";                           //  used to concatenate Pressure data into an output string
  String timeString;                                    //  String for assembling Real Time Clock time
  String dateString;                                    //  String for assembling Real Time Clock date
  String nameString;                                    //  String for assembling filename
  String stringAllTemps = "";                           //  used to concatenate all OneWire temps into a string
  //String stringTempHead = "Temp=";                    //  Temperature printout preamble
  //String stringTempTail = " F";                       //  Temperature printout postamble
  String stringPresHead = "Pres=";                      //  Pressure printout preamble
  String stringPresTail = " Pa";                        //  Pressure printout postamble
  String dataString = "";                               //  make a string for assembling the data to log:
  String start = "";                                    //  make a string for assembling the date to log:
  String stringOzoneVoltage = "";                       //  used to concatenate Solar Panel vol data into an output string
  String stringBlink = "";                              //  used to print Blink Counter
                                                        //
  int GPSposnFlag = 0;                                  //  Flag to signal if GPS Position is good
  int GPStimeFlag = 0;                                  //  Flag to signal if GPS Time is good
                                                        //
  int SolarValue = 0;                                   //  variable to store the solar panel voltages (if used in Analog data capture module)
  int SCount = 0;                                       //  Counter in ServoHeat
                                                        //
  OneWire  ds(OneWireTempPin);                          //  OneWire object set up
  long lineNum = 0;                                     //  Keeps track of how many data lines are written
  long flashNumTracker = 0;                             //  Used in Status_Light  
                                                        //
  RTC_Millis rtc;                                       //  Define the real time clock object
                                                        //
                                                        //
  void dateTime(uint16_t* date, uint16_t* time)         //   
  {                                                     //
  DateTime now = rtc.now();                             //
  *date = FAT_DATE(now.year(), now.month(), now.day()); //  returns date using FAT_DATE macro to format correctly
  *time = FAT_TIME(now.hour(), now.minute(), now.second()); //  returns time using FAT_TIME macro to format correctly
  }                                                     //
                                                      
  /******************************************************
  *    END Definitions
  *******************************************************/

  /******************************************************
  *    Control Parameters:
  *    Adjust to control program behavior
  *******************************************************/
                                                        //
  const int delayTime = 1000;                           //  time delay between samples in msec
  const int delayAdjust = 119;                          //  msec subtracted from delay time for smart delay
  const int tIDPrint = 1;                               //  Set = 1 to print OneWire Temperature Sensor IDs. Useful if using more than one sensor
                                                        //
  const int offsetUTC = 6;                              //  Local offset from UTC, Set = 6 for MDT, 7 for MST      
                                                        //                                     
  const int startupFlashInterval = 2;                   //  "startupFlashInterval" is the flash frequency of the status light immediately following startup. 
  const int startupFlashTime = 30;                      //  after "startupFlashTime" have elapsed the flash frequency is changed to "flashInterval" seconds.
  const int flashInterval = 20;                         //  
                                                        //
  /*******************************************************
  *    End Control Parameters                           //
  *******************************************************/

  /*******************************************************
  *    MAIN SET UP                                      //
  *******************************************************/
  void setup() {                                        //
                                                        //
  Wire.begin();                                         //
  Serial.begin(115200);                                 //
  GPSSerial.begin(GPSBaud);                             // GPS Serial Connection
                                                        //
  baro = MS5611();                                      // Start barometer
  baro.begin();                                         //
                                                        //
                                                        //                                                
  Serial.println();                                     //
  Serial.println();                                     //
  Serial.println("************* RESTART *************");//
  Serial.print("\r\n Flight Code Version ");            //
  Serial.println(SW_Ver);                               //
  Serial.print(SW_Comment);                             //
  logfile.print("\r\nFlight Code Version ");            //
  logfile.println(SW_Ver);                              //
  logfile.println(SW_Comment);                          //
  Serial.print("\tdelayTime = ");                       //
  Serial.print(delayTime);                              //
  Serial.println(" msec\n");                            //
  //Serial.println();                                   //
  logfile.print("\n,delayTime=");                       //
  logfile.print(delayTime);                             //
  logfile.print(" msec.");                              //
  logfile.println();                                    //
                                                        //
  pinMode(R_ledPin, OUTPUT);                            //  Red LED Pin
  pinMode(G_ledPin, OUTPUT);                            //  Green LED Pin
  pinMode(B_ledPin, OUTPUT);                            //  Blue LED Pin
                                                        //
                                                        //
  rtc.begin(DateTime(F(__DATE__), F(__TIME__)));        //  Start Realtime Clock. Sets to date and time code was compiled. Used for time source when GPS is inactive
  DateTime now = rtc.now();                             //  Read RTC
                                                        //
  /*****************  SD Card Set Up  *******************/
                                                        //
  if (!SD.begin(chipSelect, 51, 50, 52)) {              //  see if the SD card is present and can be initialized:
    Serial.println("Card init. failed!");               //
    //  error(2);                                       //
  }                                                     //  end if
  char filename[15];                                    //  Character array used to transfer filename to
  nameString = "";                                      //  ensure string is empty
                                                        //
  /***** Assemble File Name   ***************************/
                                                        //
  nameString = "DATA-000.TXT" ;                         //  Set default name string to nameString
  nameString.toCharArray(filename, 15);                 //  copy string to character array
                                                        //
  for (int j = 0; j < 1000; j++) {                      //  sequentially looks through  "DATA" two digit extensionsflies 
    filename[5] = '0' + j / 100;                        //  on SD card until
    filename[6] = '0' + (j / 10)% 10;                   //  it finds an unused number.
    filename[7] = '0' + j % 10;                         //  
    if (! SD.exists(filename)) {                        //  Creates  it if it does not exist, do not open existing, write, sync after write
      break;                                            //
    }                                                   //  end if
  }                                                     //  end for
                                                        //
  SdFile::dateTimeCallback(dateTime);                   // 
  logfile = SD.open(filename, FILE_WRITE);              //
  if ( ! logfile ) {                                    //
    Serial.print("Could not create ");                  //
    Serial.println(filename);                           //
    // error(3);                                        //
  }                                                     //  end if
  else{                                                 //
  Serial.print(" Writing to ");                         //  Write filename onto Serial Monitor
  Serial.println(filename);                             //
  Serial.println();                                     //
  }                                                     //
  FlightMode();
}                                                       //
                                                        //
  /*******************************************************
  **************   END MAIN SET UP   *********************
  ********************************************************/


  /*******************************************************
  **************   Code to Execute Once After Setup  *****
  *******************************************************/
                                                        //
  /*****************  OneWire Set UP ********************/
  byte i;                                               //  used by OneWire temp sensor read
  byte present = 0;                                     //  used by OneWire temp sensor read
  byte type_s;                                          //  used by OneWire temp sensor read
  byte data[12];                                        //  used by OneWire temp sensor read
  byte addr[8];                                         //  used by OneWire temp sensor read
  float celsius, fahrenheit;                            //  used by OneWire temp sensor read
                                                        //
  /*******************************************************  
  *************   END Code to Execute Once    ************
  *******************************************************/

  /*******************************************************
  *************   MAIN LOOP   ****************************
  *******************************************************/
                                                        //
  void loop(){                                          //
                                                        //
 /** Assembles Data String 1/sec and writes to SD card **/
                                                        //
  logfile.print(++lineNum);                             //  Increment line number and write at start of each data line in data file
  logfile.print("\t");                                  //  Write line number at start of each data line in data file
  Serial.print(lineNum);                                //  Write line number at start of each data line
  Serial.print("\t");                                   //
                                                        //
  readRTC();                                            //  Prints time to screen and log file
  Serial.print(timeString);                             //  Write to screen
  logfile.print(timeString);                            //  Write to data file
                                                        //
  //readSONARs();                                       //
  //Serial.print(distanceSONAR);                        //
  //logfile.print(distanceSONAR);                       //
                                                        //
                                                        //
  processTemp();                                        //  Reads OneWire Temperature Sensors
  Serial.print(stringAllTemps);                         //
  logfile.print(stringAllTemps);                        //
                                                        //                                                        
  readPressureSensor();                                 //  Reads Pressure Sensor
  Serial.print(stringPressure);                         //
  logfile.print(stringPressure);                        //
                                                        //
//  readOzoneVoltage();                                 //  Reads MQ131 sensor Analog voltage from pin A10
//  Serial.print(stringOzoneVoltage);                   //  readAnalogVoltages() is set up to process up to 6 analog voltages  
//  logfile.print(stringOzoneVoltage);                  //
                                                        //
  TinyGPS();                                            //  Assembles position and motion data into string
  Serial.print(positionGPS);                            //
  logfile.print(positionGPS);                           //
                                                        //
  Status_Light();                                       //
  Serial.print(stringBlink);                            //
  logfile.print(stringBlink);                           //
                                                        //
  logfile.println();                                    //  Write end of line to data file
  logfile.flush();                                      //  Ensure all data is written from buffer to SD card
  Serial.println();                                     //  Write end of line to screen
  smartDelay(delayTime - delayAdjust);                  //  Adjustment to make actual delay = delayTime msec - this may need updated if code is substantially
}                                                       //  End of function
                                                        //
  /*******************************************************
  **************   END MAIN LOOP   ***********************
  ********************************************************/
