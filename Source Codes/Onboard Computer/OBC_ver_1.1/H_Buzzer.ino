void updateBuzzer() {
  unsigned long currTime_MS = millis();
  if (currTime_MS - prevTime_Buzzer_MS >= BUZZER_TOGGLE_MS) {
    prevTime_Buzzer_MS  = currTime_MS;
    buzzerState         = !buzzerState;
    ledcWrite(BUZZER_PIN, buzzerState ? 128 : 0);
  } 
}