  if (distanceincm < 50) {
    digitalWrite(LEDlampGreen, HIGH);
  }
  else {
    digitalWrite(LEDlampGreen, LOW);
  }
  
  if (distanceincm < 20) {
    digitalWrite(LEDlampYellow, HIGH);
  }
  else {
    digitalWrite(LEDlampYellow,LOW);
  }
  if (distanceincm < 5) {
    digitalWrite(LEDlampRed, HIGH);
  sound = 1000;
  }
  else {
    digitalWrite(LEDlampRed,LOW);
  }
  
  if (distanceincm > 5 || distanceincm <= 0){
    Serial.println("Outside the permissible range of distances");
    noTone(soundbuzzer);
  }
  else {
    Serial.print(distanceincm);
    Serial.println(" cm");
    tone(soundbuzzer, sound);
  }
