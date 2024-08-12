#include <Servo.h>

#define MOTOR_PIN_LEFT_RIGHT    (8)   // D6 pin
#define MOTOR_PIN_UP_DOWN       (9)  // D10 pin
#define MOTOR_PIN_TONGS         (10)  // D11 pin

#define DEGREE_MIN    (0)
#define DEGREE_MAX    (180)

#define DEFAULT_DEGREE_LEFT_RIGHT    (55)
#define DEFAULT_DEGREE_UP_DOWN       (70)
#define DEFAULT_DEGREE_TONGS         (80)
#define NOMOV    (255)

class Motor {
  private:
    class SpeedControlParam {
      public:
        int fromDegree;
        int toDegree;
        int currDegree;
        int delta;
        int momentaryDelay;

        SpeedControlParam(int fromDegree, int toDegree) {
            if (toDegree == NOMOV || fromDegree == toDegree) {
              this->currDegree = NOMOV;
              this->toDegree = NOMOV;
              return;
            }
            
            this->fromDegree = fromDegree;
            this->toDegree = toDegree;
            this->delta = (fromDegree < toDegree) ? 1 : -1; 
            this->currDegree = fromDegree + this->delta;
            this->momentaryDelay = -1;

            checkLimit(&this->toDegree);
        }

        void checkLimit(int *degree) {
            if (*degree > DEGREE_MAX) {
                *degree = DEGREE_MAX;
            }
            else if (*degree < DEGREE_MIN) {
                *degree = DEGREE_MIN;
            }
        }
    };
  
  private:
    static Servo *leftRightMotor;
    static Servo *upDownMotor;
    static Servo *tongsMotor;  

    void initialize() {
        leftRightMotor = new Servo();
        upDownMotor = new Servo();
        tongsMotor = new Servo();
        
        leftRightMotor->attach(MOTOR_PIN_LEFT_RIGHT);
        upDownMotor->attach(MOTOR_PIN_UP_DOWN);
        tongsMotor->attach(MOTOR_PIN_TONGS);         
    }

    int getMomentaryDelayByGauss(int fromDegree, int toDegree, int currDegree) {
        if (fromDegree == toDegree) {
          return 0;
        }
        if (fromDegree < toDegree) {
          currDegree = (currDegree > toDegree) ? toDegree : currDegree;
          currDegree = (currDegree < fromDegree) ? fromDegree : currDegree;
        }
        else {
          currDegree = (currDegree > fromDegree) ? fromDegree : currDegree;
          currDegree = (currDegree < toDegree) ? toDegree : currDegree;
        }
      
        float x = ((float)currDegree - fromDegree) / (toDegree - fromDegree);  // Min-Max Normalize

        const float MOMENTARY_DELAY_MS_MAX = 20.0;
        const float MOMENTARY_DELAY_MS_MIN = 5.0;
        const float MOMENTARY_DELAY_MS_DIFF = MOMENTARY_DELAY_MS_MAX - MOMENTARY_DELAY_MS_MIN;
        const float ROTATE_DEGREE_MAX = 180.0;
        const float B = 0.5;
        const float C = 0.235;
        
        float y = MOMENTARY_DELAY_MS_MAX - MOMENTARY_DELAY_MS_DIFF * exp(- ((x - B) * (x - B)) / (C * C)) * (abs(fromDegree-toDegree) / ROTATE_DEGREE_MAX);
        
        return round(y);
    }    

    void moveWithSpeed(Servo *servo, int toDegree, Servo *servo2 = NULL, int toDegree2 = NOMOV) {
        SpeedControlParam sv(servo->read(), toDegree);
        SpeedControlParam sv2(servo2->read(), toDegree2);

        for (int ms = 0; ms < 999999; ms++) {
            if (sv.currDegree != sv.toDegree && sv.momentaryDelay < 0) {
                servo->write(sv.currDegree);
                sv.momentaryDelay = getMomentaryDelayByGauss(sv.fromDegree, sv.toDegree, sv.currDegree);
                sv.currDegree += sv.delta;
            }
            if (sv2.currDegree != sv2.toDegree && sv2.momentaryDelay < 0) {
                servo2->write(sv2.currDegree);
                sv2.momentaryDelay = getMomentaryDelayByGauss(sv2.fromDegree, sv2.toDegree, sv2.currDegree);
                sv2.currDegree += sv2.delta;
            }

            if (sv.currDegree == sv.toDegree && sv2.currDegree == sv2.toDegree) {
                break;            
            }

            delay(1);
            sv.momentaryDelay = (sv.momentaryDelay >= 0) ? sv.momentaryDelay-1 : sv.momentaryDelay;
            sv2.momentaryDelay = (sv2.momentaryDelay >= 0) ? sv2.momentaryDelay-1 : sv2.momentaryDelay;
        }
    }
    
  protected:
    Motor() {
        if (leftRightMotor == NULL) {
            initialize();
        }
    }

    void rotateMotors(int toDegree_LR, int toDegree_UD) {
        // one motor
        if (toDegree_UD == NOMOV) {
            moveWithSpeed(leftRightMotor, toDegree_LR);
        }
        // two motors
        else {
            moveWithSpeed(leftRightMotor, toDegree_LR, upDownMotor, toDegree_UD);
        }
    }
    
    void rotateTongs(int toDegree) {
        moveWithSpeed(tongsMotor, toDegree);
    }
};
Servo* Motor::leftRightMotor = NULL;
Servo* Motor::upDownMotor = NULL;
Servo* Motor::tongsMotor = NULL;  


class Robot : Motor {
  private:
    static Robot *_instance;
 
    Robot() {
    }

  public:
    static Robot* getInstance() {
        if (_instance == NULL) {
            _instance = new Robot();
        }
        return _instance;
    }

    void movDefault() {
        rotateMotors(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN);
        rotateTongs(DEFAULT_DEGREE_TONGS);
    }

    void movArms(int toDegree_LR, int toDegree_UD) {
        rotateMotors(toDegree_LR, toDegree_UD);
    }

    void movTongs(int toDegree) {
        rotateTongs(toDegree);
    }
    
};
Robot* Robot::_instance = NULL;


void setup() {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("[i] Start !");

    Robot *robot = Robot::getInstance();
    
    // 1. 초기 위치로 이동
    Serial.println("[i] Moving to initial position...");
    robot->movDefault();
    delay(2000); // 원하는 초기 위치에 도달할 때까지 충분한 시간을 기다립니다.
    
    // 2. 내가 원하는 위치로 이동
    int desiredDegree_LR = 140; // 왼쪽-오른쪽 방향 모터의 원하는 각도
    int desiredDegree_UD = 150; // 위-아래 방향 모터의 원하는 각도
    int desiredDegree_Tongs = 120; // 채찍 모터의 원하는 각도
    
    Serial.println("[i] Moving to desired position...");
    robot->movArms(desiredDegree_LR, desiredDegree_UD);
    robot->movTongs(desiredDegree_Tongs);
    delay(2000); // 원하는 위치에 도달할 때까지 충분한 시간을 기다립니다.

    // 3. 다시 초기 위치로 이동
    Serial.println("[i] Moving back to initial position...");
    robot->movDefault();
    delay(2000); // 다시 초기 위치에 도달할 때까지 충분한 시간을 기다립니다.

    Serial.println("[i] Setup completed.");
}

void loop() {
    if (Serial.available() < 1) {
      return;
    }

    String str = Serial.readStringUntil('\n');

    Robot *robot = Robot::getInstance();

    if (str.substring(0, 6) == "ready?") {
        Serial.println("true");
    }
    else if (str.substring(0, 11) == "mov,default") {
        robot->movDefault();
    }
    else if (str.substring(0, 8) == "mov,arms") {    // ex) mov,arms,100,80
        int idx_s = 9;
        int idx_e = str.indexOf(',', idx_s);
        int toDegree1 = str.substring(idx_s, idx_e).toInt();
        idx_s = idx_e + 1;
        int toDegree2 = str.substring(idx_s).toInt();
        robot->movArms(toDegree1, toDegree2);
    }
    else if (str.substring(0, 9) == "mov,tongs") {    // ex) mov,tongs,100
        int toDegree = str.substring(10).toInt();
        robot->movTongs(toDegree);
    }
}
