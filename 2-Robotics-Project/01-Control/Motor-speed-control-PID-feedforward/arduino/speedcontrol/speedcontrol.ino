#include "feedforward_model3.h"
#include <PID_v1.h>

int enapin = 5;
int motorpin1 = 6;
int motorpin2 = 7;
int channelA = 20;
int channelB = 21;

volatile int32_t tickcount = 0;
int32_t last_tickcount = 0;

unsigned long last_time = 0;
const unsigned long sample_time = 100;    

unsigned long last_ramp_time = 0;
const unsigned long ramp_interval = 2000;  

double duty_cycle = 0.0;
double pid_output = 0.0;
double ff_output = 0.0;
double target_speed = 0.0;
double abs_target_speed = 0.0;
double filtered_speed = 0.0;
double abs_filtered_speed = 0.0;

float speed_rps = 0.0;
float speed_mmps = 0.0;

const float gearppr = 11.0 * 48.0;
const float alpha = 0.35;
const float wheel_diam_mm = 67.35;

double Kp=300.0, Ki=500.0, Kd=40.0;
PID myPID(&abs_filtered_speed, &pid_output, &abs_target_speed, Kp, Ki, Kd, DIRECT);

// ====================== STEP SIGNAL ======================
float getStepTargetSpeed(float t, const float step_value) {
  const unsigned long step_delay = 1;   // 30 seconds at 0
  t /= 1000.0;
  
  if (t < step_delay) {
    return 0.0;
  } else {
    return step_value;
  }
}

// ====================== SINUSOIDAL SIGNAL ======================
float getSinusoidalTargetSpeed(float t, const float step_value) {
  const float period = 60.0;                // current time in seconds

  t /= 1000.0;
  float angle = (2.0 * PI * t) / period;
  return step_value * sin(angle);                      // Amplitude = 0.6
}

float controlFeedForward(float target_speed){
  if (target_speed <= 0.01) return 0.0;
  
  float result = ff_coeffs[0];
  float pow_x = target_speed;

  for(int i=1; i<=POLY_DEGRE; i++){
    result += ff_coeffs[i] * pow_x;
    pow_x *= target_speed;
  }
  int PWM_ff = constrain(result, 0, 255);
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

  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 255);
  myPID.SetSampleTime(sample_time);
}

void loop() {
  unsigned long current_time = millis();

  target_speed = getSinusoidalTargetSpeed(current_time, 0.65);
  //target_speed = getStepTargetSpeed(current_time, 0.65);
  abs_target_speed = abs(target_speed);
  
  // Calcul du signal PWM
  ff_output = controlFeedForward(abs_target_speed);
  myPID.Compute();
  duty_cycle = constrain(ff_output + pid_output, 0, 255);
  
  analogWrite(enapin, (int)duty_cycle);
  if(target_speed > 0){
    forward();
  }else if(target_speed < 0){
    backward();
  }
  

  // ==================== CALCUL DE VITESSE ====================
  if (current_time - last_time >= sample_time) {
    int32_t delta_ticks = tickcount - last_tickcount;
    last_tickcount = tickcount;
    last_time = current_time;

    float delta_revs = delta_ticks / gearppr;
    float time_sec = sample_time / 1000.0;

    speed_rps = delta_revs / time_sec;
    speed_mmps = PI * wheel_diam_mm * speed_rps;
    float speed_mps = speed_mmps / 1000.0;

    
    filtered_speed = alpha * speed_mps + (1.0 - alpha) * filtered_speed;
    abs_filtered_speed = abs(filtered_speed);
   
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
