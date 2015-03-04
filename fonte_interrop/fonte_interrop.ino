#include <TimerOne.h>



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
double potencia=0;
boolean limparv = false;
boolean limparp = false;

String string = "Power Supply "; // mensaguem inicial no monitor na 1 linha
String string2 = "Francisco Pinto"; // mensaguem inicial no monitor na 2 linha
int rele = 10;  // porta para o rele
boolean flagRele = false;

// timer para atualizacao do lcd


void setup() {


  Serial.begin(9600);
  // set up the LCD's number of columns and rows: 
  lcd.begin(16, 2);
  pinMode(rele, OUTPUT);
  inicial();
  
  Timer1.initialize(600000);
  Timer1.attachInterrupt(lcd_print);
}

void loop() {
  // imprecao do messagem de cima

  sensor_v();// leitura de valor e conversao para volts
  sensor_a(); //leitura do valor e convesar para ampere
  Rele(volts);
  power();
  //delay(100);
}
//#########################################################################################################
void sensor_a(){
  // read the value on AnalogIn pin 0 
  // and store it in a variable
  int sensorVal2 = analogRead(sensorPin2);


  // conversao de  ADC para voltes
  // este valor nao e multiplicado pois a resisntencia e de 1 ohm logo a voltagem e igual amparagem
  ampere =  (sensorVal2 * 5) / 1024.0;//fabs(fmap(sensorVal2, 0, 1023, 0.01, 5.0)); //(sensorVal2 * 5) / 1024.0;

  ///ampere *=10;

  // valor impreso na porta Serial 
  Serial.print("ampere: ");
  Serial.print(ampere);
}
//#########################################################################################################
//letura da ADC e converçao para tensão
void sensor_v(){
  // read the value on AnalogIn pin 0 
  // and store it in a variable
  int sensorVal = analogRead(sensorPin);

  // convert the ADC reading to voltage
  volts = (sensorVal * 5) / 1024.0;  
  //conversao 
  volts= volts * 6;
  
  // Send the voltage level out the Serial port
  Serial.print("      Volts: ");
  Serial.println(volts);


}
//#########################################################################################################
/* esta funçao le o valor da tenção e activa o rele 
 *se ele esta asima dos 8.5V
 */
void Rele(double volts){
  if(volts >=8.5){
    digitalWrite(rele, HIGH);  
    flagRele = true; 
  }
  else if(volts <= 6.5){
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
//#########################################################################################################
void inicial(){
  lcd.setCursor(2, 0);
  lcd.print(string);
  lcd.setCursor(1, 1);
  lcd.print(string2);
  delay(1000);
  lcd.clear();
}
//#########################################################################################################
void power(){

  potencia = volts * ampere;
 
}
//#########################################################################################################
void lcd_print(){
  
   //valor impreso no lcd
  lcd.setCursor(8, 0);
  lcd.print("A:");
  lcd.print(ampere,3);
  lcd.print("A");
  
  
    // print voltage of circuit in LCD
  lcd.setCursor(0, 0);  // set the cursor to column 0, line 0
  lcd.print("V:");
  if(volts >= 10){
    lcd.print(volts,1);
  }else{
    lcd.print(volts,2);
  }
   lcd.print("V");
  
  //valores da potencia
  lcd.setCursor(4, 1);
  lcd.print("P:");
  lcd.print(potencia,2);
  lcd.print("W");
 
  }
