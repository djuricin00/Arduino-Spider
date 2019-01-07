/*
 * IZMENUTI KOD JER NIJE PROVERENO DA LI SU FUNKCIJE GORE,DOLE I SREDINA NEOPHODNE!!!
 * PODESITI PARAMETRE SERVO MOTORA KADA SE PAUK MONTIRA
 * ISPITATI DA LI BLUETOOTH FUNKCIJE FUNKCIONISU KAO I NA ARDUINO NANO
 * 
 * POVEZIVANJE:
 * 
 * +(VCC), -(GND) ZA 12 SERVO MOTORA SE DOBIJA IZ BATERIJE 1 (ILI ADAPTERA 5V)
 * SIGNALNI PINOVI ZA 12 SERVO MOTORA SU POVEZANI NA SL. NACIN:
 *    - MOTOR 1 (D2)
 *    - MOTOR 2 (D3)
 *    - MOTOR 3 (D4)
 *    - MOTOR 4 (D5)
 *    - MOTOR 5 (D6)
 *    - MOTOR 6 (D7)
 *    - MOTOR 7 (D8)
 *    - MOTOR 8 (D9)
 *    - MOTOR 9 (D10)
 *    - MOTOR 10 (D11)
 *    - MOTOR 11 (D12)
 *    - MOTOR 12 (D13)
 * NAPAJANJE ARDUINO PLOCICE SE VRSI POMOCU BATERIJE BR 2(ILI ADAPRETRA 5V)
 * BLUETOOTH MODUL:
 *  -NAPAJANJE IZ ARDUINO PROCICE(5V,GND)
 *  RX - 0 (PROVERITI JOS)
 *  TX - 1 (PROVERITI JOS)
 *  
 *  SVRHA PROIZVODA:(ZABAVA,TAKMICENJE)
 *  CENA PROIZVODA: MATERIJAL + PROGRAMIRANJE + MODELIRANJE + STAMPANJE + FILAMENT 
 *  MATERIJAL = 4000
 *  PROGRAMIRANJE = 6000-12000
 *  MODELIRANJE = 4800-8000
 *  STAMPANJE = 2000
 *  FILAMENT = 3000
 *  ---------------
 *  CENA = 20000 - 30000 DIN
 */
 
#include <Servo.h>
#include <SoftwareSerial.h>
#define Rx 3
#define Tx 2

SoftwareSerial Bluetooth(Rx,Tx); // Deklaracija Bt pinova

class Pauk
{
  public:
  
  Servo m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12,m13; // Deklaracija pinova
  byte c; // Bt read varijabla
  int Pauza = 100; // Brzina Kretanja
  int Korak = 10; // Ugao pomeranja
  int UgaoSpustanjaNoge = 30; // Ugao na kojem je noga
  int UgaoPodizanjaNoge = 60; // Maksimalni ugao za podizanje noge
  void Napred(); // Kretanje napred
  void Nazad(); // -||- nazad
  void Levo(); // -||- levo
  void Desno(); // -||- desno
  void KorakNapred(Servo,Servo); // Pomeranje Noge u jednom pravcu
  void KorakNazad(Servo,Servo); // Pomeranje Noge u jednom pravcu
  void Gore(); // Podizanje pauka
  void Dole(); // Spustanje pauka
  void Sredina(); // Srednja visina
  void Visina(int); // Visina na kojoj je pauk
  void Referenca(Servo,int); // Popstavljanje u pocetnu poziciju
};

Pauk p;

void::Pauk::Referenca(Servo Motor, int PocetniPolozaj)
{
  Motor.write(PocetniPolozaj);
  delay(p.Pauza);
}

void::Pauk::KorakNapred(Servo BliziMotor, Servo DaljiMotor)
{
  DaljiMotor.write(p.UgaoPodizanjaNoge); // Dizanje Noge
  delay(p.Pauza); // Pauza
  BliziMotor.write(90); // Pomeranje Noge
  delay(p.Pauza); // Pauza 
  DaljiMotor.write(p.UgaoSpustanjaNoge); // Spustanje Noge
  delay(p.Pauza); // Pauza
  BliziMotor.write(0); // Pomeranje Noge + Trenje
  delay(p.Pauza); // Pauza 
}

void::Pauk::KorakNazad(Servo BliziMotor, Servo DaljiMotor)
{
  DaljiMotor.write(p.UgaoPodizanjaNoge); // Dizanje Noge
  delay(p.Pauza); // Pauza
  BliziMotor.write(0); // Pomeranje Noge
  delay(p.Pauza); // Pauza 
  DaljiMotor.write(p.UgaoSpustanjaNoge); // Spustanje Noge
  delay(p.Pauza); // Pauza
  BliziMotor.write(90); // Pomeranje Noge + Trenje
  delay(p.Pauza); // Pauza 
}

void::Pauk::Napred()
{
  p.KorakNapred(p.m1,p.m5);
  p.KorakNapred(p.m2,p.m6);
  p.KorakNapred(p.m3,p.m7);
  p.KorakNapred(p.m4,p.m8);
}

void::Pauk::Nazad()
{
  p.KorakNazad(p.m1,p.m5);
  p.KorakNazad(p.m2,p.m6);
  p.KorakNazad(p.m3,p.m7);
  p.KorakNazad(p.m4,p.m8);
}

void::Pauk::Levo()
{
  p.KorakNazad(p.m2,p.m6);
  p.KorakNazad(p.m4,p.m8);
  p.KorakNapred(p.m1,p.m5);
  p.KorakNapred(p.m3,p.m7);
}

void::Pauk::Desno()
{
  p.KorakNazad(p.m1,p.m5);
  p.KorakNazad(p.m3,p.m7);
  p.KorakNapred(p.m2,p.m6);
  p.KorakNapred(p.m4,p.m8);
}

void::Pauk::Dole()
{
  if(p.m9.read()!=40)
  {
    p.m9.write(40);
    delay(p.Pauza);
    p.m10.write(40);
    delay(p.Pauza);
    p.m11.write(40);
    delay(p.Pauza);
    p.m12.write(40);
    delay(p.Pauza); 
  }
}

void::Pauk::Gore()
{
  if(p.m9.read()!=0)
  {
    p.m9.write(0);
    delay(p.Pauza);
    p.m10.write(0);
    delay(p.Pauza);
    p.m11.write(0);
    delay(p.Pauza);
    p.m12.write(0);
    delay(p.Pauza); 
  }
}

void::Pauk::Sredina()
{
  if(p.m9.read()!=20)
  {
    p.m9.write(20);
    delay(p.Pauza);
    p.m10.write(20);
    delay(p.Pauza);
    p.m11.write(20);
    delay(p.Pauza);
    p.m12.write(20);
    delay(p.Pauza); 
  }
}

void::Pauk::Visina(int a)
{
    p.m9.write(a);
    delay(p.Pauza);
    p.m10.write(a);
    delay(p.Pauza);
    p.m11.write(a);
    delay(p.Pauza);
    p.m12.write(a);
    delay(p.Pauza); 
}

void setup() 
{
  delay(5000);
  Serial.begin(9600); // Serijska komunikacija
  Bluetooth.begin(9600); // Bluetooth komunikacija
  
  // Izlazi za servo motore
  p.m1.attach(2);
  p.m2.attach(3);
  p.m3.attach(4);
  p.m4.attach(5);
  p.m5.attach(6);
  p.m6.attach(7);
  p.m7.attach(8);
  p.m8.attach(9);
  p.m9.attach(10);
  p.m10.attach(11);
  p.m11.attach(12);
  p.m12.attach(13);
  p.m13.attach(1);

  // Postavljanje u referentni polozaj
  p.Referenca(p.m1,20);
  p.Referenca(p.m2,20);
  p.Referenca(p.m3,20);
  p.Referenca(p.m4,20);
  p.Referenca(p.m5,45);
  p.Referenca(p.m6,45);
  p.Referenca(p.m7,45);
  p.Referenca(p.m8,45);
  p.Referenca(p.m9,30);
  p.Referenca(p.m10,30);
  p.Referenca(p.m11,30);
  p.Referenca(p.m12,30);
}

void loop() 
{
  if(Bluetooth.available())
  {
    p.c = Bluetooth.read();
    Serial.println(p.c);

    if(p.c == 'w')
    {
      p.Napred();
    }

    if(p.c == 's')
    {
      p.Nazad();
    }

    if(p.c == 'a')
    {
      p.Levo();
    }

    if(p.c == 'd')
    {
      p.Desno();
    }
    
    if(p.c == 'o')
    {
      p.Gore();
    }

    if(p.c == 'x')
    {
      p.Dole();
    }

    if(p.c == 'f')
    {
      p.Sredina();
    }

    if(p.c <= 40)
    {
      p.Visina(p.c);
      Serial.println(p.c);
    }
  }
}
