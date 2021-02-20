  //init.h
  digitalWrite(9,1);  //미세먼지 센서 내장 LED: 부논리 초기설정
  digitalWrite(A10,1);      //열림 감지 포토 인터럽트 활성화
  digitalWrite(A11,1);      //닫힘 감지 포토 인터럽트 활성화
  DDRF|=240;          //A4-A7
  pinMode(7,1);       //MP3 K1 핀 활성화
  digitalWrite(7,1);
  pinMode(5,1);
  pinMode(6,1);       //LCD 백라이트 제어 핀 활성화
  delay(100);
  digitalWrite(7,0);
  pinMode(8,1);
  pinMode(9,1);       //미세먼지 센서 내장 LED 핀 활성화
  pinMode(11,1);      //PWM핀 활성화
  pinMode(12,1);      //펌프 릴레이 핀 활성화
  pinMode(34,1);      //팬 릴레이 핀 활성화
  digitalWrite(12,0); //펌프 릴레이 신호: 초기값 0;
  Serial.begin(9600); //디버깅용
  Serial1.begin(9600); //CO₂ 센서
  Serial2.begin(115200); //wifi 인터페이스
  dht.begin();
  lcd.init();  // I2C LCD를 초기화 합니다..
  lcd.backlight();  // I2C LCD의 백라이트를 켜줍니다.
  strip.begin();
  strip.clear();
  lcd.setCursor(0,0);
  lcd.print("waiting....");
  //delay(30000);
  lcd.clear();
  TCCR1A=130;
  TCCR1B=28;
  ICR1=1249;
  OCR1A= 20;

  /*
   * 핀 설정
   * 2:DHT22 온습도 센서 인터페이스 핀
   * 4:
   * 5:열선 PWM 제어 핀
   * 6:lcd 백라이트 제어 핀
   * 7:mp3테스트 핀(K1)
   * 8:네오픽셀 컨트롤 핀 
   * 9:미세 먼지 센서 내장 LED 제어 핀
   * 10:장애물 감지 센서 입력 핀
   * 11:서보모터 PWM 핀
   * 12:펌프 제어 핀
   * 13:
   * 14:
   * 15:
   * 16:시리얼Tx핀 (예비)
   * 17:시리얼Rx핀 (예비)
   * 18:CO₂ 센서 시리얼 Tx핀
   * 19:CO₂ 센서 시리얼 Rx핀   
   * 20:lcd 용 I²C SDA
   * 21:lcd 용 I²C SCL   
   * 
   * 34: FAN 릴레이 제어 핀
   * 
   * A2:EC센서 입력 ADC 핀
   * A3:미세 먼지 센서 입력 ADC 핀
   * A4:스텝 모터 A-IA연결  A
   * A5:스텝 모터 A-IB연결 /A
   * A6:스텝 모터 B-IA연결  B
   * A7:스텝 모터 B-IB연결 /B
   * A10:open 포토 인터럽트
   * A11:close 포토 인터럽트
   * 
   * A14: LM35 온도센서
   * A15: CdS 조도 센서 입력 ADC 핀
   * 
   */
