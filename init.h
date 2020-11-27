  //init.h
  //DHT22  
  Serial.begin(9600);
  Serial.println(F("DHT22 test!"));
  dht.begin();
  //
  //모터, 서보
  pinMode(3, OUTPUT);  
  servo.attach(servoPin); 
  //
  //

  

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
   
