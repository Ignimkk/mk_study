#include <Servo.h>

#define MOTOR_PIN_LEFT_RIGHT    (2)   // D6 pin
#define MOTOR_PIN_UP_DOWN       (3)  // D10 pin
#define MOTOR_PIN_TONGS         (4)  // D11 pin

#define DEGREE_MIN    (0)
#define DEGREE_MAX    (180)

#define DEFAULT_DEGREE_LEFT_RIGHT    (0) //55
#define DEFAULT_DEGREE_UP_DOWN       (140) //70
#define DEFAULT_DEGREE_TONGS         (120) //80
#define NOMOV    (255)
bool isInitialPosition = true;


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
// 출고
class F1_1_out : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(140, 140, false); // 공통위치로 이동 (좌우, 위아래, 절대좌표)
        delay(1000);
        rotateMotor(140, 80, false); // 층 선택 1층(110) 
        delay(1000);
        rotateMotor(100, 80, false); // 구역 이동 (오른쪽 100) 왼쪽(140)
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        delay(200);
        rotateMotor(100, 60, false); // 물건을 집기 위해서 하강
        
        delay(1000);
        rotateTongsCloseByCurrPos(30);// 그리퍼 닫고
        delay(1000);
        rotateMotor(100, 80, false); // 들어 올리고
        delay(400);
        rotateMotor(140, 80, false); // 공통 위치로 이동
        delay(1000);
        rotateMotor(140, 140, false); // 목표지점 이동
        delay(1000);
        rotateMotor(10, 140, false); // 목표지점 이동
        delay(1000);
        rotateMotor(10, 90, false); // 목표지점 이동
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열어서 물건 놓기
        delay(1000);
        rotateMotor(10,110, false);  // 머리들고 
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫아서 원상 복구
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 
      }
};

class F1_2_out : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(140, 140, false); // 공통위치로 이동 (좌우, 위아래, 절대좌표)
        delay(1000);
        rotateMotor(140, 80, false); // 층 선택 1층(110) 
        delay(1000);
        rotateMotor(120, 80, false); // 구역 이동 (오른쪽 100) 왼쪽(140)
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        delay(200);
        rotateMotor(120, 60, false); // 물건을 집기 위해서 하강
        
        delay(1000);
        rotateTongsCloseByCurrPos(30);// 그리퍼 닫고
        delay(1000);
        rotateMotor(120, 80, false); // 들어 올리고
        delay(400);
        rotateMotor(140, 80, false); // 공통 위치로 이동
        delay(1000);
        rotateMotor(140, 140, false); // 목표지점 이동
        delay(1000);
        rotateMotor(10, 140, false); // 목표지점 이동
        delay(1000);
        rotateMotor(10, 90, false); // 목표지점 이동
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열어서 물건 놓기
        delay(1000);
        rotateMotor(10,110, false);  // 머리들고 
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫아서 원상 복구
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 
      }
};

class F1_3_out : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(140, 140, false); // 공통위치로 이동 (좌우, 위아래, 절대좌표)
        delay(1000);                                     
        rotateMotor(140, 80, false); // 층 선택 1층(110) 
        delay(1000);
        rotateMotor(170, 80, false); // 구역 이동 (오른쪽 100) 왼쪽(140)
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        delay(200);
        rotateMotor(170, 60, false); // 물건을 집기 위해서 하강
        
        delay(1000);
        rotateTongsCloseByCurrPos(30);// 그리퍼 닫고
        delay(1000);
        rotateMotor(170, 80, false); // 들어 올리고
        delay(400);
        rotateMotor(140, 80, false); // 공통 위치로 이동
        delay(1000);
        rotateMotor(140, 140, false); // 목표지점 이동
        delay(1000);
        rotateMotor(10, 140, false); // 목표지점 이동
        delay(1000);
        rotateMotor(10, 90, false); // 목표지점 이동
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열어서 물건 놓기
        delay(1000);
        rotateMotor(10,110, false);  // 머리들고 
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫아서 원상 복구
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 
      }
};

class F1_4_out : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(140, 140, false); // 공통위치로 이동 (좌우, 위아래, 절대좌표)
        delay(1000);
        rotateMotor(140, 80, false); // 층 선택 1층(110) 
        delay(1000);
        rotateMotor(170, 80, false); // 구역 이동 (오른쪽 100) 왼쪽(140)
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        delay(200);
        rotateMotor(170, 60, false); // 물건을 집기 위해서 하강
        
        delay(1000);
        rotateTongsCloseByCurrPos(30);// 그리퍼 닫고
        delay(1000);
        rotateMotor(170, 80, false); // 들어 올리고
        delay(400);
        rotateMotor(140, 80, false); // 공통 위치로 이동
        delay(1000);
        rotateMotor(140, 140, false); // 목표지점 이동
        delay(1000);
        rotateMotor(10, 140, false); // 목표지점 이동
        delay(1000);
        rotateMotor(10, 90, false); // 목표지점 이동
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열어서 물건 놓기
        delay(1000);
        rotateMotor(10,110, false);  // 머리들고 
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫아서 원상 복구
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 
      }
};

class F2_1_out : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(140, 140, false); // 공통위치로 이동 (좌우, 위아래, 절대좌표)
        delay(1000);
        rotateMotor(140, 130, false); // 층 선택 1층(110) 
        delay(1000);
        rotateMotor(100, 130, false); // 구역 이동 (오른쪽 100) 왼쪽(140)
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        delay(200);
        rotateMotor(100, 110, false); // 물건을 집기 위해서 하강
        
        delay(1000);
        rotateTongsCloseByCurrPos(30);// 그리퍼 닫고
        delay(1000);
        rotateMotor(100, 130, false); // 들어 올리고
        delay(400);
        // rotateMotor(140, 140, false); // 공통 위치로 이동
        // delay(1000);
        rotateMotor(10, 90, false); // 목표지점 이동
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열어서 물건 놓기
        delay(1000);
        rotateMotor(10,110, false);  // 머리들고 
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫아서 원상 복구
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 
      }
};

class F2_2_out : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(140, 140, false); // 공통위치로 이동 (좌우, 위아래, 절대좌표)
        delay(1000);
        rotateMotor(140, 130, false); // 층 선택 1층(110) 
        delay(1000);
        rotateMotor(120, 130, false); // 구역 이동 (오른쪽 100) 왼쪽(140)
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        delay(200);
        rotateMotor(120, 110, false); // 물건을 집기 위해서 하강
        
        delay(1000);
        rotateTongsCloseByCurrPos(30);// 그리퍼 닫고
        delay(1000);
        rotateMotor(120, 130, false); // 들어 올리고
        delay(400);
        // rotateMotor(140, 140, false); // 공통 위치로 이동
        // delay(1000);
        rotateMotor(10, 130, false); // 목표지점 이동
        delay(1000);
        rotateMotor(10, 90, false);
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열어서 물건 놓기
        delay(1000);
        rotateMotor(10,110, false);  // 머리들고 
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫아서 원상 복구
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 
      }
};

class F2_3_out : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(140, 140, false); // 공통위치로 이동 (좌우, 위아래, 절대좌표)
        delay(1000);
        rotateMotor(140, 130, false); // 층 선택 1층(110) 
        delay(1000);
        rotateMotor(150, 130, false); // 구역 이동 (오른쪽 100) 왼쪽(140)
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        delay(200);
        rotateMotor(150, 110, false); // 물건을 집기 위해서 하강
        
        delay(1000);
        rotateTongsCloseByCurrPos(30);// 그리퍼 닫고
        delay(1000);
        rotateMotor(150, 130, false); // 들어 올리고
        delay(400);
        // rotateMotor(140, 140, false); // 공통 위치로 이동
        // delay(1000);
        rotateMotor(10, 130, false); // 목표지점 이동
        delay(1000);
        rotateMotor(10, 90, false);
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열어서 물건 놓기
        delay(1000);
        rotateMotor(10,110, false);  // 머리들고 
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫아서 원상 복구
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 
      }
};

class F2_4_out : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(140, 140, false); // 공통위치로 이동 (좌우, 위아래, 절대좌표)
        delay(1000);
        rotateMotor(140, 130, false); // 층 선택 1층(110) 
        delay(1000);
        rotateMotor(170, 130, false); // 구역 이동 (오른쪽 100) 왼쪽(140)
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        delay(200);
        rotateMotor(170, 110, false); // 물건을 집기 위해서 하강
        
        delay(1000);
        rotateTongsCloseByCurrPos(30);// 그리퍼 닫고
        delay(1000);
        rotateMotor(170, 130, false); // 들어 올리고
        delay(400);
        // rotateMotor(140, 140, false); // 공통 위치로 이동
        // delay(1000);
        rotateMotor(10, 130, false); // 목표지점 이동
        delay(1000);
        rotateMotor(10, 90, false);
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열어서 물건 놓기
        delay(1000);
        rotateMotor(10,110, false);  // 머리들고 
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫아서 원상 복구
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 
      }
};

//입고
class F1_1_stock : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(0, 110, false); // 목표지점 이동
        delay(1000);
        rotateMotor(0, 95, false); // 하강
        delay(1000);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        delay(200);
        rotateMotor(0, 70, false); // 하강
        delay(200);
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫기
        delay(200);
        rotateMotor(0, 90, false); // 상승
        delay(500);
        rotateMotor(80, 140, false); //2층 입구 도착
        delay(500);
        rotateMotor(140, 140, false); // 2층 공통입구 도착
        delay(500);
        rotateMotor(140, 80, false); // 1층으로 이동
        delay(500);
        rotateMotor(100, 80, false);
        delay(500);
        rotateMotor(100, 60, false);
        delay(500);
        rotateTongsOpenByCurrPos(30); // 그리퍼 열고
        delay(500);
        rotateMotor(100, 80, false); // 상승
        delay(500);
        rotateTongsCloseByCurrPos(30); // 그리퍼 닫고
        delay(500);
        rotateMotor(140, 80, false); // 1층 입구로 이동
        delay(500);
        rotateMotor(140, 140, false); // 공통 위치로 이동(2층)
        delay(500);
        rotateMotor(10, 140, false); // 빠져나가기
        delay(500);
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 
      }
};

class F1_3_stock : public GrabMotion {
  public:
    void grab() override {        
        rotateMotor(0, 110, false); // 목표지점 이동
        delay(1000);
        rotateMotor(0, 95, false); // 하강
        delay(1000);
        rotateTongsOpenByCurrPos(40); // 그리퍼 열고
        delay(200);
        rotateMotor(0, 70, false); // 하강
        delay(200);
        rotateTongsCloseByCurrPos(40); // 그리퍼 닫기
        delay(200);
        rotateMotor(0, 90, false); // 상승
        delay(500);
        rotateMotor(80, 140, false); //2층 입구 도착
        delay(500);
        rotateMotor(140, 140, false); // 2층 공통입구 도착
        delay(500);
        rotateMotor(140, 80, false); // 1층으로 이동
        delay(500);
        rotateMotor(170, 80, false);
        delay(500);
        rotateMotor(170, 60, false);
        delay(500);
        rotateTongsOpenByCurrPos(40); // 그리퍼 열고
        delay(500);
        rotateMotor(170, 80, false); // 상승
        delay(500);
        rotateTongsCloseByCurrPos(40); // 그리퍼 닫고
        delay(500);
        rotateMotor(140, 80, false); // 1층 입구로 이동
        delay(500);
        rotateMotor(140, 140, false); // 공통 위치로 이동(2층)
        delay(500);
        rotateMotor(10, 140, false); // 빠져나가기
        delay(500);
        rotateMotor(DEFAULT_DEGREE_LEFT_RIGHT, DEFAULT_DEGREE_UP_DOWN); // 초기 
      }
};


void setup() {
    Serial.begin(9600);
    while (!Serial);
    Serial.println("[i] Start !");

    Robot *robot = Robot::getInstance();
    robot->setGrabMotionAndDo(new DefaultPosition());
    isInitialPosition = true;
    delay(2000);

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
      robot->setGrabMotionAndDo(new F1_1_out());
      isTaskCompleted = false; 
      // Serial.println("Task completed"); 
    }
    else if (command == '2' && !isTaskCompleted)
    {
      isTaskCompleted = true;
      robot->setGrabMotionAndDo(new F1_2_out());
      isTaskCompleted = false; 
      // Serial.println("Task completed"); 
    }
    else if (command == '3' && !isTaskCompleted)
    {
      isTaskCompleted = true;
      robot->setGrabMotionAndDo(new F1_3_out());
      isTaskCompleted = false; 
      // Serial.println("Task completed"); 
    }
    else if (command == '4' && !isTaskCompleted)
    {
      isTaskCompleted = true;
      robot->setGrabMotionAndDo(new F1_4_out());
      isTaskCompleted = false; 
      // Serial.println("Task completed"); 
    }
    else if (command == '5' && !isTaskCompleted)
    {
      isTaskCompleted = true;
      robot->setGrabMotionAndDo(new F2_1_out());
      isTaskCompleted = false; 
      // Serial.println("Task completed"); 
    }
    else if (command == '6' && !isTaskCompleted)
    {
      isTaskCompleted = true;
      robot->setGrabMotionAndDo(new F2_2_out());
      isTaskCompleted = false; 
      // Serial.println("Task completed"); 
    }
    else if (command == '7' && !isTaskCompleted)
    {
      isTaskCompleted = true;
      robot->setGrabMotionAndDo(new F2_3_out());
      isTaskCompleted = false; 
      // Serial.println("Task completed"); 
    }
    else if (command == '8' && !isTaskCompleted)
    {
      isTaskCompleted = true;
      robot->setGrabMotionAndDo(new F2_4_out());
      isTaskCompleted = false; 
      // Serial.println("Task completed"); 
    }
    else if (command == '9' && !isTaskCompleted)
    {
      isTaskCompleted = true;
      robot->setGrabMotionAndDo(new F1_1_stock());
      isTaskCompleted = false; 
      // Serial.println("Task completed"); 
    }
    else if (command == 'a' && !isTaskCompleted)
    {
      isTaskCompleted = true;
      robot->setGrabMotionAndDo(new F1_3_stock());
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
