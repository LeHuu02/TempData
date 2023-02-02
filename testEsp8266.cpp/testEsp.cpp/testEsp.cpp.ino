#include <Arduino.h>
#include <DHTesp.h>

int value, real_value;
boolean button_bomtuoiState=HIGH;
boolean tt;
#define bom D2
#define button D5
#define buttontemp D6

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  pinMode(bom, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(buttontemp, OUTPUT);
  Serial.begin(115200);
  tt = digitalRead(button);
}

void loop() {
  //BAT TAT LED TREN BOARD ESP8266
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);  
  
  // Chúng ta sẽ tạo một hàm for để đọc 10 lần giá trị cảm biến, sau đó lấy giá trị trung bình để được giá trị chính xác nhất.
  for(int i=0;i<=9;i++){
    real_value+=analogRead(A0);
  }
  value=real_value/10;
  int percent = map(value, 0, 1023, 0, 100);    // Set giá thang giá trị đầu và giá trị cuối để đưa giá trị về thang từ 0-100. 
                                                  // Cái này sẽ bằng thực nghiệm nhé
  percent=100-percent;                            // Tính giá trị phần trăm thực. Chuyển điện thế từ 3.3V ( khô ) thành 3.3V ( ẩm )
  Serial.print(percent);
  Serial.print('%');
  Serial.print(" ");
  Serial.print("Gia tri analog: ");
  Serial.print(value);                       
  Serial.print(" ");
  Serial.print("Gia tri digital: ");
  Serial.println(digitalRead(bom));
  delay(100);
  real_value=0;

  //TAT MAY BOM NEU DO AM NHO HON 1000
  if(value < 1000 ){
    digitalWrite(bom, LOW);   
    // Serial.println(value);
  }
  //BAT MAY BOM NEU DO AM > 1010
  if(value > 1010){
    digitalWrite(bom, HIGH);
     Serial.print(": BAT may bom: ");
    // Serial.println(tt);
  }
  
  //Điều khiển trực tiếp bằng nút nhấn vật lý. BOM DEN KHI NAO KHONG NHAN THI MOI TAT BOM
  if(digitalRead(button)==LOW){
      digitalWrite(bom,!digitalRead(bom));
  }


  //DIEU KHIEN, neu nhan cong tac thi BAT TRONG 0.5S
//  if(digitalRead(button)==LOW){
//    if(button_bomtuoiState==HIGH){
//      button_bomtuoiState=LOW;
//      digitalWrite(bom,!digitalRead(bom));
//      Serial.println("Relay bơm tưới: " + String(digitalRead(bom)));
//      delay(500);
//    }
//  }else{
//    button_bomtuoiState=HIGH;
//  }
  
}
