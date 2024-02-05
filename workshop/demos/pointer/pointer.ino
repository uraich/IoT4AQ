/* 
 * Trying to answer the question on 2 pointers to "Hello World!"
 * 
 * Copyright (c) U. Raich) Jan. 2024
 */

void setup() {
  char *h1 = "Hello World!";
  char *h2 = "Hello World!";
  char h3[] = "Hello World!";
  char h4[] = "Hello World!";

  char valTxt[50];

  Serial.begin(115200);
  while (!Serial)
    delay(10);

  sprintf(valTxt,"%p",(void *) h1);
  Serial.print("h1: ");
  Serial.print(valTxt);
  sprintf(valTxt,"%p",(void *) h2);
  Serial.print(", h2: ");
  Serial.println(valTxt);   
  if (h1 == h2)
    Serial.println("The strings h1 and h2 are equal");
  else
    Serial.println("The strings h1 and h2 are not equal");

  sprintf(valTxt,"%p",(void *) h3);
  Serial.print("h3: ");
  Serial.print(valTxt);
  sprintf(valTxt,"%p",(void *) h4);
  Serial.print(", h4: ");
  Serial.println(valTxt);   
  if (h3 == h4)
    Serial.println("The strings h3 and h4 are equal");
  else
    Serial.println("The strings h3 and h4 are not equal");
}
  
void loop() {
}
