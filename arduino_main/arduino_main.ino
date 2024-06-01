#include <Servo.h>
// 接続先のピン
const int rgb[3] = { 2, 3, 4 };
const int xyz[3] = { 0, 1, 2 };
const int swords[] = { 5, 6 };

// 動作変更のパラメータ
// LED点滅の間隔
const int flash_interval = 100;
// デフォルトのサーボモーターの角度
const int default_servo_angle = 0;
// 睡眠検知時のサーボモーターの角度
const int sleep_servo_angle = 110;
// 何Gで眠ったと判断するか
const int g_th = 2; 

// ステータスを示すグローバル変数
bool is_sleep = false;

Servo r_sword;
Servo l_sword;

int acc[] = {0, 0, 0};

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(rgb[i], OUTPUT);
  }
  r_sword.attach(swords[0]);
  l_sword.attach(swords[1]);

  r_sword.write(default_servo_angle);
  l_sword.write(180 - default_servo_angle);
  
  Serial.begin(9600);
}

void flash(int state) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(rgb[i], state);
  }
}

void loop() {
  if (is_sleep) {
    // 剣を動かして起こす
    r_sword.write(sleep_servo_angle);
    l_sword.write(180 - sleep_servo_angle);

    // フラッシュを焚いて起こす
    for (int i = 0; i < 10; i++) {
      flash(HIGH);
      delay(flash_interval);
      flash(LOW);
      delay(flash_interval);
    }
    delay(1000);  // サーボが振動するのを防ぐ
    is_sleep = false;  // 睡眠状態から復活

    // 眠くないときは剣をもとの位置に置く
    r_sword.write(default_servo_angle);
    l_sword.write(180 - default_servo_angle);
  } else {
    // 眠さの検知
    // 加速度の絶対値がしきい値（g_th）を超えたときに眠ったと判定
    // analogRead: 0~1023 (0V~5V)
    // x,y,z: 0V~3.3V (0g: 1.65V, 0.33V/g)
    // -> acc - (1.65 * 1023/5) = acc - 338
    // g = g_th を超えたときに眠ったと判定
    // g_th * 0.33 * 1023/5 = g_th * 67.518
    acc[0] = analogRead(xyz[0]) - 338;
    acc[1] = analogRead(xyz[1]) - 338;
    acc[2] = analogRead(xyz[2]) - 338;
    
    int magnitude = acc[0]*acc[0] + acc[1]*acc[1] + acc[2]*acc[2];
    // しきい値を超えていたら
    if (magnitude > g_th*68) {
      // 睡眠状態を睡眠中に変更
      is_sleep = true;
      // ラズパイに眠ったことを通知し，ラズパイ側では音楽を再生
      Serial.println("sleep!");
    }
  }
}