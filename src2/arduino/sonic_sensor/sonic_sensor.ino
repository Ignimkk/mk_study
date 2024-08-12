const int TRIG = 9; //TRIG 핀 설정 (초음파 보내는 핀)
const int ECHO = 8;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
long duration, distance;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH); // 초음파를 받은 시간 (LOW 에서 HIGH 로 )
  distance = duration * 17 / 1000; // cm 로 환산 (34000 / 10000000 /2 를 간단하게)
  Serial.println(duration);
  Serial.print("\nDIstance : ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);  
}
// 340m/s = 17000cm/s * 1s/1000ms