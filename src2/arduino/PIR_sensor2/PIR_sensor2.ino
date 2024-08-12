const int PIR = 2;
const int LED = 4;
long unsigned int lowIn; 

long unsigned int pause = 5000; 

boolean lockLow = true;
boolean takeLowTime; 



void setup()
{
  Serial.begin(9600);
  pinMode(PIR, INPUT);
  pinMode(LED, OUTPUT);
}


void loop()
{
 
     if(digitalRead(PIR) == HIGH)
     {
       digitalWrite(LED, HIGH);   //PIR센서의 신호출력이 HIGH이면 LED에 전원을 공급한다.
       if(lockLow)
       { 
         //추가적인 PIR센서의 신호출력이 입력되기 전까지 LOW로 전환될 때까지 대기한다.
         lockLow = false;           
         Serial.println("---");
         Serial.print("motion detected at ");
         Serial.print(millis()/1000);
         Serial.println(" sec");
         delay(50);
       }        
         takeLowTime = true;
     }
 
     if(digitalRead(PIR) == LOW)
       {      
       digitalWrite(LED, LOW);  //PIR센서의 신호출력이 LOW이면 LED에 전원 공급을 안한다.
 
       if(takeLowTime)
       {
        lowIn = millis();          //HIGH에서 LOW로 전환되는 시간을 저장한다.
        takeLowTime = false;       //LOW에서만 실행하도록한다.
       }
       //센서의 LOW가 일시중단된 시간보다 클 경우 더 이상 움직임이 없다고 가정한다.
       if(!lockLow && millis() - lowIn > pause)
       { 
           //새로운 모션이 감지된 후에만 코드가 반복실행되는지 확인한다.
           lockLow = true;                       
           Serial.print("motion ended at ");      
           Serial.print((millis() - pause)/1000);
           Serial.println(" sec");
           delay(50);
       }
       }
  }

