#include <LiquidCrystal_I2C.h> //library LCD
#include <AntaresESP8266HTTP.h> //library Antares
#include <DHT.h> //library sensor DHT

#define ACCESSKEY "b0d84f78cdfe3b1a:a7f1bc09785a43e2" //acces key didaptakn dari web antares
#define WIFISSID "SonOfHorus" //nama ssid yang digunakan untuk menyambungkan antares
#define PASSWORD "teajus789" //kata sandi dari Wifi yang di gunakan

#define projectName "smart-plant-temprature-control" //nama project yang sesuai dari web antares
#define deviceName "sensor1" //nama device yang sesuai dari web antares

AntaresESP8266HTTP antares(ACCESSKEY);

int statusrelay1 = 0;
int statusrelay2 = 0;

LiquidCrystal_I2C lcd(0x27, 16, 2); // alamat dari LCD dan ukuran dari LCD

#define DHTPIN 14 //mendefinisikan pin dht ke port 14
#define DHTTYPE DHT11 //mendefinisikan tipe sensor yang digunakan

#define Relay_1 12 //mendefinisikan relay 1 di port 12
#define Relay_2 13 //mendefinisikan relay 2 di port 13

DHT dht(DHTPIN, DHTTYPE);

//antares.get(projectName, deviceName);

void setup() {
  lcd.init(); //menginisialisasi lcd
  lcd.backlight(); //menyalakan backlight dari LCD
  Serial.begin(115200); //kecepatan serial monitor
  dht.begin(); //memulai dht sensor bekerja

  lcd.setCursor(0,0); //mesetting tata letak tulisan di layar lcd
  lcd.print("Menghubungkan"); //mencetak tulisan di layar lcd
  lcd.setCursor(0,1); //mesetting tata letak tulisan di layar lcd
  lcd.print("ke Wifi...");//mencetak tulisan di layar lcd

  pinMode(Relay_1, OUTPUT); //menjadikan relay 1 ke mode output
  pinMode(Relay_2, OUTPUT); //menjadikan relay 1 ke mode output

  antares.setDebug(true); //menampilkan data lengkap di serial monitor  
  antares.wifiConnection(WIFISSID,PASSWORD); //menyambungkan wifi ke anatares supaya data masuk  

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Berhasil");
  lcd.setCursor(0,1);
  lcd.print("terhubung!");

  delay(5000);

}

void loop() {
  float temp = dht.readTemperature(); //mendefinisikan angka temprature dalam bentuk float
  int hum = dht.readHumidity(); //mendefinisikan angka kelembapan dalam bentuk integer
  
  if (isnan(temp) || isnan(hum)){ //mendefinisikan jika bukan angka maka tidak terdeteksi
    Serial.println("Sensor DHT11 tidak ditemukan!"); //mencetak hasil jika bukan angka
    lcd.clear(); // untuk membersihkan lacar lcd
    lcd.setCursor(0,0); // mengatur letak baris dan kolom 
    lcd.print("Sensor DHT11"); 
    lcd.setCursor(0,1); // mengatur letak baris dan kolom
    lcd.print("tidak ditemukan!"); 
    delay(1000); // mengatur jumlah delay 
    return;
  }

  Serial.println("Temperatur : "+ String(temp) + "\t" + "Kelembaban : " + String(hum)+ "%");

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.setCursor(5,0);
  lcd.print(temp);
  lcd.print((char)223); // menampilkan karakter dari satuan derajat 
  lcd.print("C");


  lcd.setCursor(0,1);
  lcd.print("Kelembaban:");
  lcd.setCursor(11,1);
  lcd.print(hum);
  lcd.print("%");

//  if (temp<=19.00) {
//    digitalWrite(Relay_1, LOW);
//    digitalWrite(Relay_2, HIGH);
//  }
//
//  else if (temp>21.00) {
//    digitalWrite(Relay_1, HIGH);
//    digitalWrite(Relay_2, LOW);
//  } rentang yang digunakan adalah rentang yang digunakan untuk tanaman kopi yang rentangnya dari 19-21 derajat celcius sumber:"http://repository.ub.ac.id/id/eprint/172977/"

  if (temp<=29.00) {
    digitalWrite(Relay_1, LOW);
    statusrelay1 = 1;
    digitalWrite(Relay_2, HIGH);
    statusrelay2 = 0;
    antares.getInt("statusrelay1");
    
//    if (statusrelay1 == 0){
////      kondisi = 1;
//      digitalWrite(Relay_1, HIGH);
//    }
//    else if (statusrelay2 == 1){
////      kondisi = 1;
//      digitalWrite(Relay_2, LOW);
//      }
  }

  else if (temp>30.00) {
    digitalWrite(Relay_1, HIGH);
    statusrelay1 = 0;
    digitalWrite(Relay_2, LOW);
    statusrelay2 = 1;
  }
  

  antares.add("temperature",temp); //
  antares.add("humidity", hum);
  antares.add("lampu", statusrelay1);
  antares.add("kipas", statusrelay2);

  antares.send(projectName, deviceName);

  delay(5000);

}
