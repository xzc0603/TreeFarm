  //OCR1A=14;   //=>CCW 보더라인
  //OCR1A = 167;  //=> CW 보더라인
  analogWrite(5,31); //열선 PWM 출력 12.5%(31)
  const char celcT[]={223,'C',' ',0};
  const char 
  cmd[5] = {17, 1, 1, 0xED, 0}, 
  *label[] = {"TP :", "HM :", "EC :", "DT :", "CO2:","HT :"},
  *unit[] = {celcT,"% ", "  ", "  ", "  "};
  const float norm[] = {0.2, 0.5, 1}; //  => 컬러 코드를 넣어야 하는 부분.(정규화 비율)
  static long int pT[3] = {0,};
  static unsigned char state=0;

  scr(lcd,10);
  arr[5]=(int)(analogRead(A14)*0.4882); //LM35
  arr[6]=analogRead(A15); //CdS
  a02module(&arr[2]);

  for (int i = 0; i < 8; i++)strip.setPixelColor(i, (unsigned char)(0.8705*(127-(arr[6]>>3))), 0, (unsigned char)(0.2078*(127-(arr[6]>>3))));
  strip.show();    
  if (millis() > (pT[0] + 500)) //0.5초 주기로
  {
    digitalWrite(9,0);  //LED 활성화
    delayMicroseconds(280); //280 마이크로 초 대기
    arr[3]=analogRead(A3);   //센싱값 저장
    delayMicroseconds(40);  //40 마이크로 초 대기
    digitalWrite(9,1);  //LED 비활성화
    pT[0] = millis();   //타임 스탬프
  }
  if((state)&(arr[3]>250)) //창문이 열려있고 미세먼지 센서값이 300이상이면
  {
    cF[1]|=1;   //창문을 닫는다
    state=0;    //창문 닫힘
  }
  if((!state)&(arr[3]<170)) //창문이 닫혀있고 미세먼지 센서값이 200이하이면
  {
    cF[0]|=1; //창문을 연다
    state=1;  //창문 열림
  }
  forward(); //닫는거
  reverse(); //여는거
  
  if (millis() > (pT[1] + 2000))  //2초 주기로
  {
    float
    h = dht.readHumidity(),       //습도 센싱
    t = dht.readTemperature();    //온도 센싱
    if (isnan(h) || isnan(t))arr[0] = arr[1] = 255; //값이 없으면 에러코드 255를 출력
    else
    {
      arr[0] = (unsigned int)t; //온도 저장
      arr[1] = (unsigned int)h; //습도 저장
    }
    uint8_t bREG = SREG;    //상태 레지스터 저장
    cli();                  //인터럽트 차단
    Serial1.print(cmd);     //명령 코드를 CO₂로 전송
    SREG = bREG;            //상태 레지스터 값 로드
    unsigned char cs = 0;   //체크섬 변수 초기화
    for (unsigned char i = 0; i - 7; i++)cs += rcv[i];  //체크섬 연산
    if (!(unsigned char)(cs + rcv[7]))  //체크섬이 일치하면 값을 저장
    arr[4] = ((unsigned int)(rcv[3] << 8) + (unsigned int)rcv[4]); 
    Serial.print((String)arr[0]+ " " + (String)arr[1] + " " + (String)arr[2] + " " + (String)arr[3] + " " );
    Serial.print((String)arr[4]+ " " + (String)arr[5] + " " + (String)arr[6] + " " + (String)arr[7] + "\n");
    for (unsigned char i = 0; i - 6; i++)
    {
      char str[5] = {0,};
      sprintf(str, "%4d", arr[i]);
      lcd.setCursor((i & 1) ? 11 : 0, i >> 1);
      lcd.print(label[i] + (String)str +(String)unit[i]);
    }
    pT[1] = millis();
  }  
