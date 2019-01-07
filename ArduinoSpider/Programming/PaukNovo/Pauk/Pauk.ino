/*
 * DODATI JOS FUNKCIJA KOJE PAUK RADI - MAHANJE-IGRANJE-SKAKANJE
 * 
 * Datum kodiranja 26\11\18
 * Vreme kodiranja 180 min
 * Kodiranje app = 6 h
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
 *  SVRHA PROIZVODA:(ZABAVA,TAKMICENJE,PRIMENJIVANJE ZNANJA)
 *  CENA PROIZVODA: MATERIJAL + PROGRAMIRANJE + MODELIRANJE + STAMPANJE  
 *  MATERIJAL = 12000 (Servomotori + filament + arduino + bluetooth + kablici + elektronika)
 *  PROGRAMIRANJE = 10000 
 *  MODELIRANJE i ANIMACIJA = 10000
 *  STAMPANJE = 3000
 *  ---------------
 *  CENA = 18000 - 20000 DIN
 */
 
#include<Servo.h>
#include<SoftwareSerial.h>
#define Rx 3
#define Tx 2

SoftwareSerial Bluetooth(Rx,Tx); // Deklaracija Bt pinova

class Pauk
{
  public:
  Servo m1,m2,m3,m4,m5,m6,m7,m8,m9,m10,m11,m12; // Deklaracija pinova
  byte c; // Bt read varijabla
  int ShortPause = 10; // Pauza kraca za regulisanje brzine pomeranja pauka(OBRNUTO SRAZMERNA SA BRZINOM KRETANJA)
  int Pauza = 100; // Pauza duza, za postavljane Servomotora u referentni polozaj
  int UgaoZaSpustanjeM5M8 = 75; // Minimalni ugao na kojem je noga m5m8
  int UgaoZaPodizanjeM5M8 = 105; // Maksimalni ugao za podizanje noge m5m8
  int UgaoZaSpustanjeM6M7 = 105; // Minimalni ugao na kojem je noga m5m8
  int UgaoZaPodizanjeM6M7 = 75; // Maksimalni ugao za podizanje noge m5m8
  void Napred(); // Kretanje napred
  void Nazad(); // -||- nazad
  void Levo(); // -||- levo
  void Desno(); // -||- desno
  void Referenca(); // Postavljanje u pocetnu poziciju
  void Visina(int); // Funkcija za postavljanje pauka u odredjenu visinu proporcionalno sa sliderom
  void Brzina(Servo,int); // Funkcija za regulisanje brzine pomeranja nogu
};

Pauk p; // Kreiranje objekta

void::Pauk::Brzina(Servo m,int kp) // Funkcija pomocu koje se regulise brzina kretanja nogu pauka
{
  int pp=m.read(); // Ocitavanje trenutne vrednosti ugla na ServoMotoru
  if(pp>kp) // Slucaj pada ugla
  {
    for(int i=pp; i>kp; i-=5) // ugao kretanja od 5 stepeni
    {
      m.write(i);
      delay(p.ShortPause);
    }
  }
  else if(pp<kp) // Slucaj rasta ugla
  {
    for(int i=pp; i<kp; i+=5) // ugao kretanja od 5 stepeni
    {
      m.write(i);
      delay(p.ShortPause);
    }
  }
}

void::Pauk::Referenca() // Postavljanje ServoMotora u pocetni polozaj na pocetku koda
{
  // Leva gornja noga referentni polozaj
  p.Brzina(p.m5,105); // Podizanje
  p.Brzina(p.m9,90); // Postavka ref 1
  p.Brzina(p.m1,90); // Postavka ref 2
  p.Brzina(p.m5,90); // Postavka ref 3

  // Desna donja noga referentni polozaj
  p.Brzina(p.m8,105); // Podizanje
  p.Brzina(p.m12,90); // Postavka ref 4
  p.Brzina(p.m4,90); // Postavka ref 5
  p.Brzina(p.m8,90); // Postavka ref 6

  // Leva donja noga referentni polozaj
  p.Brzina(p.m7,105); // Podizanje
  p.Brzina(p.m11,90); // Postavka ref 7
  p.Brzina(p.m3,90); // Postavka ref 8
  p.Brzina(p.m7,90); // Postavka ref 9

  // Desna gornja noga referentni polozaj
  p.Brzina(p.m6,105); // Podizanje
  p.Brzina(p.m10,90); // Postavka ref 10
  p.Brzina(p.m2,90); // Postavka ref 11
  p.Brzina(p.m6,90); // Postavka ref 12
}

void::Pauk::Napred()
{
  // podizanje,pomeranje i spustanje leve gornje noge
  p.Brzina(p.m5,UgaoZaPodizanjeM5M8); // Podizanje
  p.Brzina(p.m1,45); // Pomeranje
  p.Brzina(p.m5,UgaoZaSpustanjeM5M8); // Spustanje

  // podizanje,pomeranje i spustanje desne donje noge
  p.Brzina(p.m8,UgaoZaPodizanjeM5M8); // Podizanje
  p.Brzina(p.m4,135); // Pomeranje
  p.Brzina(p.m8,UgaoZaSpustanjeM5M8); // Spustanje

  // podizanje,pomeranje i spustanje desne gornje noge
  p.Brzina(p.m6,UgaoZaPodizanjeM6M7); // Podizanje
  p.Brzina(p.m2,135); // Pomeranje
  p.Brzina(p.m6,UgaoZaSpustanjeM6M7); // Spustanje

  // podizanje,pomeranje i spustanje leve donje noge
  p.Brzina(p.m7,UgaoZaPodizanjeM6M7); // Podizanje
  p.Brzina(p.m3,45); // Pomeranje
  p.Brzina(p.m7,UgaoZaSpustanjeM6M7); // Spustanje

  // vracanje +++ trenje o podlogu
  p.Brzina(p.m1,135);
  p.Brzina(p.m2,45);
  p.Brzina(p.m3,135);
  p.Brzina(p.m4,45);

}

void::Pauk::Nazad()
{
  // podizanje,pomeranje i spustanje leve gornje noge
  p.Brzina(p.m5,UgaoZaPodizanjeM5M8); // Podizanje
  p.Brzina(p.m1,135); // Pomeranje
  p.Brzina(p.m5,UgaoZaSpustanjeM5M8); // Spustanje

  // podizanje,pomeranje i spustanje desne donje noge
  p.Brzina(p.m8,UgaoZaPodizanjeM5M8); // Podizanje
  p.Brzina(p.m4,45); // Pomeranje
  p.Brzina(p.m8,UgaoZaSpustanjeM5M8); // Spustanje

  // podizanje,pomeranje i spustanje desne gornje noge
  p.Brzina(p.m6,UgaoZaPodizanjeM6M7); // Podizanje
  p.Brzina(p.m2,45); // Pomeranje
  p.Brzina(p.m6,UgaoZaSpustanjeM6M7); // Spustanje

  // podizanje,pomeranje i spustanje leve donje noge
  p.Brzina(p.m7,UgaoZaPodizanjeM6M7); // Podizanje
  p.Brzina(p.m3,135); // Pomeranje
  p.Brzina(p.m7,UgaoZaSpustanjeM6M7); // Spustanje

  // vracanje +++ trenje o podlogu
  p.Brzina(p.m1,45); 
  p.Brzina(p.m2,135); 
  p.Brzina(p.m3,45); 
  p.Brzina(p.m4,135); 
}

void::Pauk::Levo()
{
  // podizanje,pomeranje i spustanje leve gornje noge
  p.Brzina(p.m5,UgaoZaPodizanjeM5M8); // Podizanje
  p.Brzina(p.m1,45); // Pomeranje
  p.Brzina(p.m5,UgaoZaSpustanjeM5M8); // Spustanje

  // podizanje,pomeranje i spustanje desne donje noge
  p.Brzina(p.m8,UgaoZaPodizanjeM5M8); // Podizanje
  p.Brzina(p.m4,45); // Pomeranje
  p.Brzina(p.m8,UgaoZaSpustanjeM5M8); // Spustanje

  // podizanje,pomeranje i spustanje desne gornje noge
  p.Brzina(p.m6,UgaoZaPodizanjeM6M7); // Podizanje
  p.Brzina(p.m2,45); // Pomeranje
  p.Brzina(p.m6,UgaoZaSpustanjeM6M7); // Spustanje

  // podizanje,pomeranje i spustanje leve donje noge
  p.Brzina(p.m7,UgaoZaPodizanjeM6M7); // Podizanje
  p.Brzina(p.m3,45); // Pomeranje
  p.Brzina(p.m7,UgaoZaSpustanjeM6M7); // Spustanje

  // vracanje +++ trenje o podlogu
  p.Brzina(p.m1,135); 
  p.Brzina(p.m2,135); 
  p.Brzina(p.m3,135); 
  p.Brzina(p.m4,135);
  
}

void::Pauk::Desno()
{
  // podizanje,pomeranje i spustanje leve gornje noge
  p.Brzina(p.m5,UgaoZaPodizanjeM5M8); // Podizanje
  p.Brzina(p.m1,135); // Pomeranje
  p.Brzina(p.m5,UgaoZaSpustanjeM5M8); // Spustanje

  // podizanje,pomeranje i spustanje desne donje noge
  p.Brzina(p.m8,UgaoZaPodizanjeM5M8); // Podizanje
  p.Brzina(p.m4,135); // Pomeranje
  p.Brzina(p.m8,UgaoZaSpustanjeM5M8); // Spustanje

  // podizanje,pomeranje i spustanje desne gornje noge
  p.Brzina(p.m6,UgaoZaPodizanjeM6M7); // Podizanje
  p.Brzina(p.m2,135); // Pomeranje
  p.Brzina(p.m6,UgaoZaSpustanjeM6M7); // Spustanje

  // podizanje,pomeranje i spustanje leve donje noge
  p.Brzina(p.m7,UgaoZaPodizanjeM6M7); // Podizanje
  p.Brzina(p.m3,135); // Pomeranje
  p.Brzina(p.m7,UgaoZaSpustanjeM6M7); // Spustanje

  // vracanje +++ trenje o podlogu
  p.Brzina(p.m1,45); 
  p.Brzina(p.m2,45); 
  p.Brzina(p.m3,45); 
  p.Brzina(p.m4,45);
}

void::Pauk::Visina(int a)
{
  if(isDigit(a)) // Provera da li je ocitana varijabla cifra(int)
  {
    // Racunanje i postavljanje vrednosti novog ugla
    p.m9.write(60+a);  
    delay(p.Pauza);
    p.m10.write(120-a);
    delay(p.Pauza);
    p.m11.write(120-a);
    delay(p.Pauza);
    p.m12.write(60+a);
    delay(p.Pauza); 
  }
  else{Serial.println("Primljena vrednost nije cifra");} // Ispis Greske
}

void setup() 
{
  delay(5000); // Cekanje 5 sekundi za pripremu 
  Serial.begin(9600); // Serijska komunikacija neophodna za komuniciranje i lakse programiranje
  Bluetooth.begin(9600); // Bluetooth komunikacija neophodna za komuniciranje izmedju kontrolnog uredjaja i pauka
  
  // Izlazi za servo motore
  p.m1.attach(2);p.m2.attach(3);p.m3.attach(4);p.m4.attach(5);p.m5.attach(6);p.m6.attach(7);p.m7.attach(8);p.m8.attach(9);p.m9.attach(10);p.m10.attach(11);p.m11.attach(12);p.m12.attach(13);
  p.Referenca(); // Postavljanje u referentni polozaj
  
  Serial.println("Sve reference su postavljene!"); // Ispis da je sve uredu i da mozemo poceti sa koristenjem
  delay(5000); // Cekanje 5 sekundi za pripremu 
}

void loop() 
{
  if(Bluetooth.available())
  {
    p.c = Bluetooth.read(); // Citanje vrednosti sa bluetooth uredjaja a=97,w=119,s=115,d=100, Vrednost slidera 0-60
    Serial.println(p.c); // Ispis varijable koja je ocitana sa Bluetooth komunikacije
    if(isAlpha(p.c)) // Ispitivanje da li je procitana varijabla karakter(Char)
    {
      if(p.c == 'w'){p.Napred();}
  
      if(p.c == 's'){p.Nazad();}
  
      if(p.c == 'a'){p.Levo();}
  
      if(p.c == 'd'){p.Desno();}
    }
    
    else if(isDigit(p.c)) // Ispitivanje da li je procitana varijabla cifra(int)
    {
      if(p.c <= 60) // VREDNOST SLIDERA 0-60
      {
        p.Visina(p.c); // Postavljanje visine na vrednost slidera
        Serial.println(p.c); // Ispis na Serial Monitoru
      }
    }
    else {Serial.println("Ocitana vrednost nije ni cifra ni slovo");}
  }
}
