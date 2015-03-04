// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int sensorPin = A0;// entrada voltes
const int sensorPin2 = A1; 
const double const_a= 5.0;
float R1 = 5000.0; //valor de la primera resistencia
float R2 = 1000.0; // valor de la segunda resistencia
double volts=0;
double ampere=0;
String string = "Power Supply"; // mensaguem fisa no monitor na 1 linha
int rele = 10;  // porta para o rele
boolean flagRele = false;


void setup() {
 
 
   Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  pinMode(rele, OUTPUT);

}

void loop() {
  // imprecao do messagem de cima
  lcd.setCursor(2, 0);
  lcd.print(string);
  volts = sensor_v();// leitura de valor e conversao para volts
  
  Rele(volts);

  delay(100);
}

//#########################################################################################################
//letura da ADC e converÃ§ao para tensÃ£o
double sensor_v(){
   // read the value on AnalogIn pin 0 
  // and store it in a variable
  int sensorVal = analogRead(sensorPin);

  // convert the ADC reading to voltage
  float voltage = (sensorVal * 5) / 1024.0;  
 //conversao 
 voltage = voltage * 6;
  // Send the voltage level out the Serial port
  Serial.print("      Volts: ");
  Serial.println(voltage);
  
 //valores impreso no lcd
  // print voltage of circuit
  
  lcd.setCursor(0, 1);  // set the cursor to column 0, line 1
  lcd.print("V:");
  lcd.print(voltage,1);
  return voltage;
}
 //###############################################################
 /* esta funÃ§ao le o valor da tenÃ§Ã£o e activa o rele 
 *se ele esta acima dos 8.5V
 */
 void Rele(double volts){
   if(volts >=8.5){
    digitalWrite(rele, HIGH);  
   flagRele = true; 
}
else if(volts <= 6){
  digitalWrite(rele, LOW); 
flagRele = false;  
}
else
{
  if(flagRele == false)
  {
    digitalWrite(rele, LOW); 
  }
  else
  {
    digitalWrite(rele, HIGH);
    flagRele = true;
  }
}
}
//###############################################################
   

