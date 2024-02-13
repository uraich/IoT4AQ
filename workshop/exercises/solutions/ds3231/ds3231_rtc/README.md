# Programs to access the ds1307 RTC
This folder contains programs that access the ds1307 RTC without passing through the RTCLib.
* date_time_macros: Written to figure out what the __DATE__ and __TIME__ macros are. The program shows that these are constant text strings containing the date and the time, when the program was compiled
* write_ds1307RAM: writes the non-volatile (battery backed up) RAM in the ds1307 with some text
* read_ds1307RAM: Reads the ds1307 RAM and prints its contents (in ASCII)
* set_ds1307_ntp: gets time and date from the network using the NTP protocol. The result is used to set the ESP32 internal RTC. Then the values are read back from the ESP32 RTC to set the time and date registers in the ds1307
* set_ds1307_manual: You may define time and date in the format

"17:36:25 Tue, Jan 09 2024"

The string is parsed and the ds1307 time registers set correspondingly
* read_ds1307_date_time: Reads the ds1307 registers and prints their contents
