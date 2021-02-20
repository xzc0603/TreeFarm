  for (int i = 0; i < 8; i++)strip.setPixelColor(i, 0, 0, 0);
  strip.show();
  digitalWrite(12,0);
  digitalWrite(34,0);
  PORTF&=15;
  digitalWrite(5,0); //열선 출력 OFF
