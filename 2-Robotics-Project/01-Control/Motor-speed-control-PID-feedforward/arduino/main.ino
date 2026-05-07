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

void setup() {
  Serial.begin(115200);
  
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
  pinMode(enapin, OUTPUT);
  pinMode(channelA, INPUT);
  pinMode(channelB, INPUT);

  digitalWrite(motorpin1, HIGH);
  digitalWrite(motorpin2, LOW);
  
  attachInterrupt(digitalPinToInterrupt(channelB), tickcounter, RISING);
  
  last_time = millis();
  last_ramp_time = millis();
  
  Serial.println("Duty Cycle Ramp Test Started");
}

void loop() {
  unsigned long current_time = millis();

  // ==================== RAMP DUTY CYCLE ====================
  if (current_time - last_ramp_time >= ramp_interval && duty_cycle < 255) {
    duty_cycle++;
    analogWrite(enapin, duty_cycle);
    last_ramp_time = current_time;
    
    Serial.print("Duty: ");
    Serial.print(duty_cycle);
    Serial.print(" | ");
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

    Serial.print("Speed: ");
    Serial.println(filtered_speed, 3);
  }
}

void tickcounter() {
  if (digitalRead(channelA)) {
    tickcount++;
  } else {
    tickcount--;
  }
}
