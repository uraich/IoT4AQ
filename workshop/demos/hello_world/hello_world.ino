/* 
 * hello_world.ino: Demonstrates basic string handling functions
 * and some pointer handling
 *
 * Copyright (c) U. Raich) Feb. 2024
 * This program is part ot the IoT4AQ workshop held in March 2024 at
 * the University Alioune Diop, Bambey, Sénégal
 * It is released under the MIT license
 */

void setup() {
  Serial.begin(115200);
  if (!Serial)
    delay(10);
}

void loop() {
  char hello[] = "Hello World!";
  char *helloPtr = hello;
  char bye[]   = "Good Bye World!";
  char hello2[100]; // we do not know yet how much space we will need
                    // we therefore make the array simply big enough
  Serial.print("Print the full string");
  Serial.println(hello);

  Serial.println("hello has ");
  Serial.print(strlen(hello));
  Serial.println(" characters");

  Serial.println("Print the string character by character");
  for (int i=0; i<strlen(hello)+1; i++) // the terminating zero is not counted, therefore we have to
                                        // 1 to the length in order to print all the characters
    Serial.print(hello[i]);
  Serial.println();                     // go to the next line

  strcpy(hello2,hello);
  Serial.print("hello2: ");
  Serial.println(hello2);

  // compare strings
  if (strcmp(hello,hello2) == 0)
    // you could also write:
    // if (!strcmp(hello,hello2))
    // since 0 is interpreted as false and therefore (not) !strcmp(hello,hello2) is true
    Serial.println("hello and hello2 contain the same string");
  else
    Serial.println("hello2 and hello are different");

  if (strcmp(hello,bye) == 0)
    Serial.println("hello and bye contain the same string");
  else
    Serial.println("hello and bye are different");  

  helloPtr = hello2;           // point to the first character of hello2
  Serial.print("First character of hello2: ");
  Serial.println(*helloPtr++); // print the first character of hello2 which is 'H'
                               // increment the pointer, it now points to 'e'
  Serial.print("Second character of hello2: ");
  Serial.println(*helloPtr);   // we print the second character but do not increment the pointer
                               // it still points to 'e'
  *helloPtr = 'a';             // now we write 'a' to the location where hellePtr points to
                               // overwriting the 'e' by a 'a'
  Serial.print("hello2 after replacement of the 'e' by 'a': ");
  Serial.println(hello2);   

  Serial.println();  
  delay(1000);
}
