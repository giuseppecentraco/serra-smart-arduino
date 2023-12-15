#include <LiquidCrystal_I2C.h>
#include <SimpleDHT.h>

//dislay
LiquidCrystal_I2C lcd(0x27, 16, 2);

//dht11
SimpleDHT11 dht11;

//definizione costanti
//pin analogici
#define PIN_FOTORESISTORE A0
#define PIN_IGROMETRO A1
#define PIN_SENS_ACQUA A2

//pin digitali
#define PIN_DHT11 2
#define PIN_LED 7
#define PIN_BUZZER 4

//pin relè
#define PIN_VENTOLA 8
#define PIN_POMPA 12
#define PIN_LAMPADA 13

//valori di soglia
#define SOGLIA_LUCE 550
#define SOGLIA_UM_ARIA 50
#define SOGLIA_UM_TERRA 2000 //da definire il livello di umidità
#define SOGLIA_LIV_ACQUA 1000 //da definire il livello di acqua //soglia giusta 1020

void setup() {

  Serial.begin(9600);
  
  lcd.init();
  lcd.backlight();

  pinMode(PIN_VENTOLA,OUTPUT);
  pinMode(PIN_POMPA,OUTPUT);
  pinMode(PIN_LAMPADA,OUTPUT);
  pinMode(PIN_LED,OUTPUT);
  pinMode(PIN_BUZZER,OUTPUT);

  //valori iniziali per resettare eventuali configurazioni di default
  digitalWrite(PIN_VENTOLA, HIGH);
  digitalWrite(PIN_POMPA, HIGH);
  digitalWrite(PIN_LAMPADA, HIGH);
}

void loop() {

  int ris[] = {0,0};
  gestioneVentilazione(ris);

  //visualizza dati sul display
  visualizzaDati("Temperatura Aria",ris[0]);
  visualizzaDati("Umidita' Aria",ris[1]);
  visualizzaDati("Livello Luce",gestioneLuce());
  visualizzaDati("Livello Acqua",gestioneLivelloAcqua());
  visualizzaDati("Umidita' Terreno",gestioneIrrigazione());
}

int gestioneLuce(){
  int luce = analogRead(PIN_FOTORESISTORE);
  if(luce < SOGLIA_LUCE)
    digitalWrite(PIN_LAMPADA, LOW);
  else
    digitalWrite(PIN_LAMPADA, HIGH);
  return luce;
}

//gestisce temperatura e umidità dell'aria
void gestioneVentilazione(int val[]){
  byte temp = val[0];
  byte umid = val[0];
  int err = 0;
  if ((err = dht11.read(PIN_DHT11, &temp, &umid, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err=");
    Serial.println(err);
    return;
  }
  val[0] = (byte)temp;
  val[1] = (byte)umid;
  if(umid > SOGLIA_UM_ARIA)
    digitalWrite(PIN_VENTOLA, LOW);
  else
    digitalWrite(PIN_VENTOLA, HIGH);
}

int gestioneIrrigazione(){
  int val_igrometro = analogRead(PIN_IGROMETRO);
  int liv_acqua = analogRead(PIN_SENS_ACQUA);
  if(liv_acqua >= SOGLIA_LIV_ACQUA){
    if(val_igrometro < SOGLIA_UM_TERRA){
      digitalWrite(PIN_POMPA, LOW);
      delay(2000);
      digitalWrite(PIN_POMPA, HIGH);
    }
  }
  return val_igrometro;
}

int gestioneLivelloAcqua(){
  int liv_acqua = analogRead(PIN_SENS_ACQUA);
  if(liv_acqua < SOGLIA_LIV_ACQUA){
    allarme();
  }
  return liv_acqua;
}

void allarme(){
  digitalWrite(PIN_LED, HIGH);
  tone(4,2000,200);
  delay(300);
  digitalWrite(PIN_LED, LOW);
  delay(300);
  digitalWrite(PIN_LED, HIGH);
  tone(4,2000,200);
  delay(300);
  digitalWrite(PIN_LED, LOW);
  delay(300);
  digitalWrite(PIN_LED, HIGH);
  tone(4,2000,200);
  delay(300);
  digitalWrite(PIN_LED, LOW);
}

void visualizzaDati(String grandezza, int valore){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(grandezza);
  lcd.setCursor(0, 1);
  lcd.print(valore);
  delay(3000);
}
