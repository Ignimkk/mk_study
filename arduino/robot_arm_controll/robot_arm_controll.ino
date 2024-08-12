#include <Servo.h>

#define MOTOR_PIN_LEFT_RIGHT    (8)   
#define MOTOR_PIN_UP_DOWN       (9)  
#define MOTOR_PIN_TONGS         (10) 

#define MOTOR1_DEGREE_MIN    (0)
#define MOTOR1_DEGREE_MAX    (180)

#define MOTOR2_DEGREE_MIN    (0)
#define MOTOR2_DEGREE_MAX    (180)

#define MOTOR3_DEGREE_MIN    (0)
#define MOTOR3_DEGREE_MAX    (180)  

#define DEFAULT_DEGREE_LEFT_RIGHT    (0) //55
#define DEFAULT_DEGREE_UP_DOWN       (140) //70
#define DEFAULT_DEGREE_TONGS         (120) //80
#define NOMOV    (255)
bool isInitialPosition = true;


class Motor {
  private:
    // static int MOTOR1_DEGREE_MIN;
    // static int MOTOR1_DEGREE_MAX;
    // static int MOTOR2_DEGREE_MIN;
    // static int MOTOR2_DEGREE_MAX;
    // static int MOTOR3_DEGREE_MIN;
    // static int MOTOR3_DEGREE_MAX;

    class SpeedControlParam {
      public:
        int fromDegree;
        int toDegree;
        int currDegree;
        int delta;
        int momentaryDelay;

        SpeedControlParam(int fromDegree, int toDegree)
        {
          if (toDegree == NOMOV || fromDegree == toDegree)
          {
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

        void checkLimit(int *degree, int minDegree, int maxDegree)
        {
          if (*degree < minDegree)
          {
            *degree = minDegree;
          }
          else if (*degree > maxDegree)
          {
            *degree = maxDegree;
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

    void moveWithSpeed(Servo *servo, int toDegree, Servo *servo2 = NULL, int toDegree2 = NOMOV, Servo *servo3 = NULL, int toDegree3 = NOMOV) {
        SpeedControlParam sv(servo->read(), toDegree);
        SpeedControlParam sv2(servo2->read(), toDegree2);
        SpeedControlParam sv3(servo3->read(), toDegree3);

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
            if (sv3.currDegree != sv3.toDegree && sv3.momentaryDelay < 0) {
                servo3->write(sv3.currDegree);
                sv3.momentaryDelay = getMomentaryDelayByGauss(sv3.fromDegree, sv3.toDegree, sv3.currDegree);
                sv3.currDegree += sv3.delta;
            }

            if (sv.currDegree == sv.toDegree && sv2.currDegree == sv2.toDegree && sv3.currDegree == sv3.toDegree) {
                break;            
            }

            delay(1);
            sv.momentaryDelay = (sv.momentaryDelay >= 0) ? sv.momentaryDelay-1 : sv.momentaryDelay;
            sv2.momentaryDelay = (sv2.momentaryDelay >= 0) ? sv2.momentaryDelay-1 : sv2.momentaryDelay;
            sv3.momentaryDelay = (sv3.momentaryDelay >= 0) ? sv3.momentaryDelay-1 : sv3.momentaryDelay;
        }
    }
    
  protected:
    Motor() {
        if (leftRightMotor == NULL) {
            initialize();
        }
    }

    void rotateMotor(int toDegree_LR, int toDegree_UD, bool isRelative=false) {
        if (isRelative) {
            toDegree_LR = (toDegree_LR == NOMOV) ? NOMOV : leftRightMotor->read() + toDegree_LR;
            toDegree_UD = (toDegree_UD == NOMOV) ? NOMOV : upDownMotor->read() - toDegree_UD;
        }

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
    void rotateTongsCloseByCurrPos(int toDegree) {
        moveWithSpeed(tongsMotor, tongsMotor->read()+toDegree);
    }
    void rotateTongsOpenByCurrPos(int toDegree) {
        moveWithSpeed(tongsMotor, tongsMotor->read()-toDegree);
    }
};

Servo* Motor::leftRightMotor = NULL;
Servo* Motor::upDownMotor = NULL;
Servo* Motor::tongsMotor = NULL;  


class GrabMotion : public Motor {
  protected:
    GrabMotion() {
    
    }

  public:
    virtual void grab() = 0;
};


class Robot {
  private:
    static Robot *_instance;
    GrabMotion *grabMotion;
    Robot() {
      grabMotion = NULL; 
    }

  public:
    static Robot* getInstance() {
        if (_instance == NULL) {
            _instance = new Robot();
        }
        return _instance;
    }
    
    void setGrabMotion(GrabMotion *grabMotion) {
        if (this->grabMotion != NULL) {
            delete this->grabMotion;
        }
        this->grabMotion = grabMotion;
    }

    void doGrab() {
        grabMotion->grab();
    }

    void setGrabMotionAndDo(GrabMotion *grabMotion) {
        setGrabMotion(grabMotion);
        doGrab();
    }
};
Robot* Robot::_instance = NULL;


class DefaultPosition : public GrabMotion {
  public:
    void grab() override {
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN);
        rotateTongs(DEFAULT_DEGREE_TONGS);  
    }
};

class A1_place : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(130, 120, false); // 공통위치로 이동 (좌우, 위아래, 절대좌표)
        delay(1000);
        rotateMotor(150, 110, false); // 1-1 구역으로 이동 
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        delay(200);
        rotateMotor(150, 90, false); // 물건을 집기 위해서 하강
        
        delay(1000);
        rotateTongsCloseByCurrPos(30);// 그리퍼 닫고
        delay(1000);
        rotateMotor(150, 110, false); // 들어 올리고
        delay(400);
        rotateMotor(130, 110, false); // 공통 위치로 이동
        delay(400);
        rotateMotor(40, 90, false); // 목표지점 이동
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열어서 물건 놓기
        delay(1000);
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫아서 원상 복구
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 위치로 이동
        delay(100);
      }
};

class A2_place : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(130, 120, false); // 공통위치로 이동
        delay(1000);
        rotateMotor(180, 110, false); // 1-2구역으로 이동
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        delay(200);
        rotateMotor(180, 90, false); // 물건을 집기 위해서 하강
        
        delay(1000);
        rotateTongsCloseByCurrPos(30);// 그리퍼 닫고
        delay(1000);
        rotateMotor(180, 110, false); // 들어 올리고
        delay(1000);
        rotateMotor(130, 110, false); // 공통 위치로 이동
        delay(300);
        rotateMotor(40, 90, false); // 목표지점 이동
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열어서 물건 놓기
        delay(1000);
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫아서 원상 복구
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 위치로 이동
        delay(100);
      }
};

class B1_place : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(130, 110, false); // 공통위치로 이동
        delay(1000);
        rotateMotor(150, 110, false); // 3층으로 이동
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        delay(500);
        rotateMotor(150, 90, false); // 물건을 집기 위해서 하강
        delay(1000);
        rotateTongsCloseByCurrPos(30);// 그리퍼 닫고
        delay(1000);
        rotateMotor(150, 110, false); // 들어 올리고
        delay(500);
        rotateMotor(130, 110, false); // 공통 위치로 이동
        rotateMotor(50, 90, false); // 목표지점 이동
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열어서 물건 놓기
        delay(1000);
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫아서 원상 복구
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 위치로 이동
        delay(100);
      }
};

class B2_place : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(130, 110, false); // 공통위치로 이동
        delay(1000);
        rotateMotor(150, 110, false); // 3층으로 이동
        delay(100);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        // delay(500);
        rotateMotor(150, 90, false); // 물건을 집기 위해서 하강
        delay(1000);
        rotateTongsCloseByCurrPos(30);// 그리퍼 닫고
        delay(500);
        rotateMotor(150, 110, false); // 들어 올리고
        delay(500);
        rotateMotor(130, 110, false); // 공통 위치로 이동
        rotateMotor(50, 90, false); // 목표지점 이동
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열어서 물건 놓기
        delay(1000);
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫아서 원상 복구
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 위치로 이동
        delay(100);
      }
};

void setup() {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("[i] Start !");

    Robot *robot = Robot::getInstance();
    robot->setGrabMotionAndDo(new DefaultPosition());
    delay(500);

    // Serial.println("[i] setup() completed.");
}

bool isTaskCompleted = false;
void loop()
{
  Robot *robot = Robot::getInstance();

  if (!isInitialPosition)
  {
    robot->setGrabMotionAndDo(new DefaultPosition());
    isInitialPosition = true;
  }

  // 2. 원하는 동작 수행
  if (Serial.available() > 0)
  {
    char command = Serial.read();
    if (command == '1' && !isTaskCompleted)
    {
      isTaskCompleted = true;
      robot->setGrabMotionAndDo(new A1_place());
      isTaskCompleted = false; 
      // Serial.println("Task completed"); 
    }
    else if (command == '2' && !isTaskCompleted)
    {
      isTaskCompleted = true;
      robot->setGrabMotionAndDo(new A2_place());
      isTaskCompleted = false; 
      // Serial.println("Task completed"); 
    }
    else if (command == '3' && !isTaskCompleted)
    {
      isTaskCompleted = true;
      robot->setGrabMotionAndDo(new B1_place());
      isTaskCompleted = false; 
      // Serial.println("Task completed"); 
    }
    else if (command == '4' && !isTaskCompleted)
    {
      isTaskCompleted = true;
      robot->setGrabMotionAndDo(new B2_place());
      isTaskCompleted = false; 
      // Serial.println("Task completed"); 
    }
  }

  else if (!isInitialPosition)
  {
    robot->setGrabMotionAndDo(new DefaultPosition());
    isInitialPosition = true;
  } 
}
