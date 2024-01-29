/* sd.cpp: A function that checks it a fkle named meas.txt exists on the SD card
   If yes, it is opened in append mode
   If no, it is created
   Then the time stamp and the measured data are written to the file
*/

#include "sd_card.h"

int sdWriteMeas(char *timeStamp, float temperature, float humidity,
		 float pm_1_0, float pm_2_5, float pm_10) {
  char line[100]; //convert everything into this line
  File measFile;
  if (!SD.begin()) {
    Serial.println("SD card mount failed");
    return -1;
  }
  
  if (SD.exists("/meas.txt")) {
    // Serial.println("Trying to open in append mode");
    measFile = SD.open("/meas.txt",FILE_APPEND);
  }
  else {
    // Serial.println("Trying to open in write mode");
    measFile = SD.open("/meas.txt",FILE_WRITE);
  }
 
  // check if we successfully opened the file
  if (!measFile) {
    Serial.println("Error when trying to open /meas.txt");
    return -1;
  }
  snprintf(line,100,"%s, temperature: %4.2f, humidity: %4.2f, pm 1.0: %5.2f, pm 2.5: %5.2f, pm 10: %5.2f",
	   timeStamp,temperature,humidity,pm_1_0,pm_2_5,pm_10);
  // write to disk
  measFile.println(line);
  Serial.print("Writing: ");
  Serial.println(line);
  measFile.close();
  return 1;
}
