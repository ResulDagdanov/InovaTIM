/*                            enA  ->  D10
                              enB  ->  D9
                              in1  ->  D2
L298N DC Motor Sürücü         in2  ->  D3
                              in3  ->  D4
                              in4  ->  D5
                              GND  ->  GND Arduino  +  GND Batarya
                              Vin  ->  Batarya 5V - 6V
                              5Vout -> Arduino 5V
                              
                              VCC  ->  5Vout
HC-SD04 Ultrasonik Sensör     GND  ->  GND Arduino
                              Echo ->  D7
                              Trig ->  D6
***********************************************************************/

// global değişkenlere pin numaralarını ata
#define enA 10
#define enB 9
#define in1 2
#define in2 3
#define in3 4
#define in4 5

// PWM sinyali 0-255 arasındadır
int pwmOutput = 255;

// değişkenlerin tanımlanması
long sure;
int mesafe;

// dijital pinleri tanımlamak
const int trigPin = 6;
const int echoPin = 7;

void setup()
{
  // 9600 Baud oranında Serial haberleşmeyi başlat
  Serial.begin(9600);
  
  pinMode(trigPin, OUTPUT);   // trigger pinini OUTPUT olarak tanımlamak
  pinMode(echoPin, INPUT);    // echo pinini INPUT olarak tanımlamak

  // enable pinleri OUTPUT olarak tanımla
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);

  // dijital pinleri OUTPUT olarak tanımla
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

void loop()
{
  // başta trigger pinini temizlemek
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // trigger pinine 10 milisaniye boyunca güç ver ve sonra gücü kes
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // echo pinini okumak, çıkış olarak ses dalgasının yolculuk zamanını mikrosaniye cinsinden verir
  sure = pulseIn(echoPin, HIGH);

  // mesafe hesaplamak
  mesafe= sure*0.034/2;
  
  analogWrite(enA, pwmOutput);    // L298N EnableA pinine PWM sinyal gönder
  analogWrite(enB, pwmOutput);    // L298N EnableB pinine PWM sinyal gönder

  // eğer engel ile aradaki mesafe 3 cm'den büyük ise
  if(mesafe >= 3)
  {
    // ileriye dogru git
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  else
  {
    // motorları durdur
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }

  // Serial Monitora yazdırmak
  Serial.print("Mesafe: ");
  Serial.println(mesafe);
}
