  unsigned int filter(unsigned int a)
  {
    static unsigned int tab[4]={0,};
    for(unsigned char i=0;i<3;i++)tab[i]=tab[i+1];
    tab[3]=a;
    unsigned int sum=0;
    for(unsigned char i=0;i<4;i++)sum+=tab[i];
    sum>>=2;
    return sum>>2;
  }
volatile unsigned char cF[3]={0,},halt=0;

void scr(LiquidCrystal_I2C lcd,unsigned char pin)
{
  static long int pT=0;
  static unsigned char b=1,d=1;
  if(!digitalRead(pin))
  {
    b|=1;
    d|=1;
    pT=millis();
  }
  if(millis()>pT+35000)b=0;
  if(millis()>pT+30000)d=0;
  if(d)lcd.display();else lcd.noDisplay();
  digitalWrite(6,b);
}


void forward()
{
  const unsigned char sig[4]={0x60,0x50,0x90,0xA0};
  static int phase=0;
  static long int pT=0;
  if(cF[0])
  {
    digitalWrite(34,1);
    if (micros() > (pT + 800)) //0.8밀리초 주기
    {
      if(!digitalRead(A11))PORTF= sig[phase&3]|PORTF&15;
      else
      {
        cF[0]=0;
        phase=0;
      }
      phase++;
      pT =micros();   //타임 스탬프
    }
  }
  else phase=0;

}

void reverse()
{
  const unsigned char sig[4]={0x60,0x50,0x90,0xA0};
  static int phase=0;
  static long int pT=0;
  if(cF[1])
  {
    digitalWrite(34,0);
    if (micros() > (pT + 800)) //0.8밀리초 주기
    {
      if(!digitalRead(A10))PORTF= sig[3-(phase&3)]|PORTF&15;
      else
      {
        cF[1]=0;
        phase=0;
      }
      phase++;
      pT =micros();   //타임 스탬프
    }
  }
  else phase=0;
}

void a02module(unsigned int *anal)
{
  *anal = analogRead(A2);  //EC센서를 읽어오고
  static unsigned char trig=0;
  if(*anal<600) trig=1;
  if(*anal>700) trig=0;
  if(trig)//값이 일정 이하이면
  {
    static long int pT=0;
    static unsigned char f[2]={0,};
    digitalWrite(12,1);   //펌프 릴레이 활성화
    if (millis() > (pT + 20)) //0.8밀리초 주기
    {
      /*플래그의 심플 토글 래치*/
      if((OCR1A>=160)&(f[0]))f[0]=0;    
      if((OCR1A<=20)&(!f[0]))f[0]=1; 
      /*서보 제어 코드*/
      if(f[0])OCR1A++;
      else OCR1A--;
      pT =millis();   //타임 스탬프
    }
  }
  else digitalWrite(12,0);  //펌프 릴레이 비활성화
}

void a02demo()
{
  if(cF[2])     
  {
    static long int pT=0;
    static unsigned char f[2]={0,};
    digitalWrite(12,1);   //펌프 릴레이 활성화
    if (millis() > (pT + 10)) //0.8밀리초 주기
    {
      /*플래그의 심플 토글 래치*/
      if((OCR1A>=160)&(f[0]))f[0]=0;    
      if((OCR1A<=20)&(!f[0]))f[0]=1; 
      /*서보 제어 코드*/
      if(f[0])OCR1A++;
      else OCR1A--;
      pT =millis();   //타임 스탬프
    }
  }
  else digitalWrite(12,0);  //펌프 릴레이 비활성화
}
