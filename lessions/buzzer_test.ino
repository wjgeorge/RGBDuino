int pinBuzzer = 8; //管脚D9连接到蜂鸣器模块的信号脚
const int buttonPin = 2;
int buttonState = 0;
void setup() {
pinMode(buttonPin,INPUT);
pinMode(pinBuzzer, OUTPUT); //设置pinBuzzer脚为输出状态
}
void loop() {
  long frequency = 2000; //频率, 单位Hz
  buttonState = digitalRead(buttonPin);
  if(buttonState == LOW){
    tone(pinBuzzer, frequency );
  }
  else{
   noTone(pinBuzzer);
  }
}
