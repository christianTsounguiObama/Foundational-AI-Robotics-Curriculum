#include "feedforward_model3.h"

int enapin = 5;
int motorpin1 = 6;
int motorpin2 = 7;
int channelA = 20;
int channelB = 21;

volatile int32_t tickcount = 0;
int32_t last_tickcount = 0;

unsigned long last_time = 0;
const unsigned long sample_time = 200;    

unsigned long last_ramp_time = 0;
const unsigned long ramp_interval = 2000;  

int duty_cycle = 0;

float speed_rps = 0.0;
float speed_mmps = 0.0;
float filtered_speed = 0.0;

const float gearppr = 11.0 * 48.0;
const float alpha = 0.35;
const float wheel_diam_mm = 67.35;
float target_speed = 0.0;

float getSinusoidalTargetSpeed(float t) {
  const float period = 60.0;                // current time in seconds

  t /= 1000.0;
  float angle = (2.0 * PI * t) / period;
  return 0.6 * sin(angle);                      // Amplitude = 0.6
}

float controlFeedForward(float target_speed){
  float result = ff_coeffs[0];
  float pow_x = target_speed;

  for(int i=1; i<=POLY_DEGRE; i++){
    result += ff_coeffs[i] * pow_x;
    pow_x *= target_speed;
  }
  int PWM_ff = constrain(round(result), 0, 255);
  return PWM_ff;
}

void forward(){
  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
}

void backward(){
  digitalWrite(motorpin1, LOW);
  digitalWrite(motorpin2, HIGH);
}

void setup() {
  Serial.begin(115200);
  
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
  pinMode(enapin, OUTPUT);
  pinMode(channelA, INPUT);
  pinMode(channelB, INPUT);

  
  attachInterrupt(digitalPinToInterrupt(channelB), tickcounter, RISING);
  
  last_time = millis();
  last_ramp_time = millis();
}

void loop() {
  unsigned long current_time = millis();

  target_speed = getSinusoidalTargetSpeed(current_time);
  
  // Calcul du signal PWM
  duty_cycle = controlFeedForward(abs(target_speed));
  analogWrite(enapin, duty_cycle);
  if(target_speed > 0){
    forward();
  }else if(target_speed < 0){
    backward();
  }
  

  // ==================== SPEED CALCULATION ====================
  if (current_time - last_time >= sample_time) {
    int32_t delta_ticks = tickcount - last_tickcount;
    last_tickcount = tickcount;
    last_time = current_time;

    float delta_revs = delta_ticks / gearppr;
    float time_sec = sample_time / 1000.0;

    speed_rps = delta_revs / time_sec;
    speed_mmps = PI * wheel_diam_mm * speed_rps;
    float speed_mps = speed_mmps / 1000.0;

    // Low-pass filter
    filtered_speed = alpha * speed_mps + (1.0 - alpha) * filtered_speed;
   
    Serial.print(target_speed, 4);
    Serial.print(",");
    Serial.println(filtered_speed, 4);
  }
}

void tickcounter() {
  if (digitalRead(channelA)) {
    tickcount++;
  } else {
    tickcount--;
  }
}
