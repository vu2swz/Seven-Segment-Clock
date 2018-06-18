/*

Pin Connections : 
      2   -->  a
      3   -->  b
      4   -->  c
      5   -->  d
      6   -->  e
      7   -->  f
      8   -->  g
      9   -->  Set button
      10  -->  Inc button
      11  -->  Blinking LEDs
      A0  -->  Hour ten's place digit
      A1  -->  Hour one's place digit
      A2  -->  Minute ten's place digit
      A3  -->  Minute one's place digit
      A4  -->  Second ten's place digit
      A5  -->  Second one's place digit

*/




#define S2 A5
#define S1 A4
#define M2 A3
#define M1 A2
#define H2 A1
#define H1 A0
#define SET 9
#define INC 10
  byte digitArray[11][7] = { { 0,0,0,0,0,0,1 }, // = 0
                           { 1,0,0,1,1,1,1 }, // = 1
                           { 0,0,1,0,0,1,0 }, // = 2
                           { 0,0,0,0,1,1,0 }, // = 3
                           { 1,0,0,1,1,0,0 }, // = 4
                           { 0,1,0,0,1,0,0 }, // = 5
                           { 0,1,0,0,0,0,0 }, // = 6
                           { 0,0,0,1,1,1,1 }, // = 7
                           { 0,0,0,0,0,0,0 }, // = 8
                           { 0,0,0,1,1,0,0 }, // = 9
                           { 1,1,1,1,1,1,1 } // = off
                         };
long previousMillis = 0;                         
long previousMillis2 = 0;                         
long interval = 1000; 
long interval2 = 500;
int led=0;
int hh=00,mm=54,ss=00;
int set=0;
void setup()
{
  Serial.begin(9600);
  int i;
  for(i=2;i<9;i++)
  {
    pinMode(i,OUTPUT);// inputs a-g of seven segment display
  }
  pinMode(9,INPUT); // set button
  pinMode(10,INPUT); // increment button
  pinMode(11,OUTPUT); // flashing LED
  pinMode(A0,OUTPUT);// ten's place of hour
  pinMode(A1,OUTPUT);// one's place of hour
  pinMode(A2,OUTPUT);// ten's place of minute
  pinMode(A3,OUTPUT);// one's place of minute
  pinMode(A4,OUTPUT);// ten's place of second
  pinMode(A5,OUTPUT);// one's place of second
}
void loop()
{
  if(digitalRead(SET)==HIGH) // check for set button press
    {
      set=(set+1)%4;
      delay(500);
    }
  if(set==0)      // normal mode. replace with time sync code if RTC is used
  {
  unsigned long currentMillis = millis();

      if(currentMillis - previousMillis2 > interval2) 
        {
          previousMillis2 = currentMillis;
          analogWrite(11,led);  // blinking LEDs
          if(led==0)
          led=8;
          else
          led=0;
        }
        if(currentMillis - previousMillis > interval) 
        {
          previousMillis = currentMillis;
          ss++;
          if(ss/60!=0)
          {
            ss%=60;
            mm++;
          }
          if(mm/60!=0)
          {
            mm%=60;
            hh++;
          }
          if(hh%12==0)
          {
            hh%=12;
          }
        }
        
      }
   if(set==1)                        // hour set mode
   {   if(digitalRead(INC)==HIGH)
       {
           hh=(hh+1)%12;
          delay(200);
       }
   }
   if(set==2)                      // minute set mode
   {
      if(digitalRead(INC)==HIGH)
      {    
          mm=(mm+1)%60;
         delay(200);
      }
   }
   if(set==3)                     // second set mode
   {
      if(digitalRead(INC)==HIGH)
      {  
          ss=(ss+1)%60;
          delay(200);
      }
   }
        dispnum(S2,ss%10);  // show the time on seven segment displays
        dispnum(S1,ss/10);
        dispnum(M2,mm%10);
        dispnum(M1,mm/10);
        dispnum(H2,hh%10);
        dispnum(H1,hh/10);
      
   
  
}

void dispnum(int i,int k)
{
  int j,l;
  for(j=A0;j<A6;j++)
    {  
      digitalWrite(j,LOW);
    }
  digitalWrite(i,HIGH);    // select current seven segment display
  
  for(l=2;l<9;l++)
    digitalWrite(l,digitArray[k][l-2]);  // write the digit to display
    delay(2);
  
}
