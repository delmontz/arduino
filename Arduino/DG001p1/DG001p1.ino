#include <MsTimer2.h>
#include <LiquidCrystal.h>
#define Rsw 13
#define Wsw 12
#define Bsw 11
#define SP 3
//液晶設定
LiquidCrystal lcd(A5,A3,A4,A1,A2,8,7);
//変数宣言
unsigned int cx = 0; //カーソール位置
int hour1 = 0;
int hour2 = 6; //デフォルト６時間
int minute1 = 0;
int minute2 = 0;
unsigned long time = 0; 
unsigned int i = 0;
unsigned int q = 0;
unsigned int w = 0;
int e = 0;//残り時間表示用
long num1 = 0;
long num2 = 0;
int a1 = 1;
int a2 = 5;
int a3 = 5;
int a4 = 5;
//タイマー設定表示関数
void alarm(void){
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("alarm set");//上段
  lcd.setCursor(0,2);
  lcd.print(hour1);
  lcd.setCursor(1,2);
  lcd.print(hour2);
  lcd.setCursor(2,2);
  lcd.print('h');
  lcd.setCursor(3,2);
  lcd.print(minute1);
  lcd.setCursor(4,2);
  lcd.print(minute2);
  lcd.setCursor(5,2);
  lcd.print('m');
  lcd.setCursor(7,2);
  lcd.print("OK");
  lcd.setCursor(cx,2);
  lcd.cursor();
}
//タイマーカウント関係関数
void talarm(void){
  interrupts();
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("START");//上段
  lcd.setCursor(0,2);
  lcd.print(e);
  lcd.setCursor(4,2);
  lcd.print("minutes left");
}

void timer(void){
  interrupts();
  q = (hour1 * 10) + hour2; //時間
  w = (minute1 * 10 ) + minute2; // 分
  e = (q * 60) + w; //分合計
  time = e * 60; //秒合計
  MsTimer2::set(1024,count);   //一秒ごとにカウント
  MsTimer2::start();
  talarm();
  while(1){
    if( digitalRead(Rsw) == HIGH ){
      lcd.setCursor(2,2);
      lcd.cursor();
      e = 5;
      wakeup();
    }
  }

}
void count(void){
  interrupts();
  time = time - 1;
  i = i + 1;
  if( time == 0 ){
    lcd.setCursor(2,2);
    lcd.cursor();
    e = 5;
    wakeup();
  }
  if( i == 60 ){
    e = e - 1;
    talarm();
    i = 0;
  }

}
//アンサークエスチョン用表示関数
void wakeuplcd(void){
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print('Q');
  lcd.setCursor(2, 0);
  lcd.print(num1);
  lcd.setCursor(6, 0);
  lcd.print('+');
  lcd.setCursor(8, 0);
  lcd.print(num2);
  lcd.setCursor(0, 2);
  lcd.print('A');
  lcd.setCursor(2, 2);
  lcd.print(a1);
  lcd.setCursor(3, 2);
  lcd.print(a2);
  lcd.setCursor(4, 2);
  lcd.print(a3);
  lcd.setCursor(5, 2);
  lcd.print(a4);
  lcd.setCursor(7, 2);
  lcd.print("OK");
  lcd.setCursor(cx,2);
  lcd.cursor();
  lcd.setCursor(14,0);
  lcd.print("@");
  lcd.setCursor(15,0);
  lcd.print(e);
  lcd.setCursor(cx,2);
  lcd.cursor();
}

void count2(void){
   interrupts();
   if( digitalRead(Rsw) == LOW && digitalRead(Wsw) == LOW  && digitalRead(Bsw) == LOW ){
     digitalWrite(SP,HIGH);
   }
}

void wakeup(void){
  MsTimer2::stop();
  digitalWrite(SP,HIGH);
  MsTimer2::set(10000,count2);
  MsTimer2::start();
  randomSeed(analogRead(0));
  num1 = random(100, 1000);
  num2 = random(100, 1000);
  cx = 2;
  wakeuplcd();
  delay(300);
  while(1){
    if( digitalRead(Rsw) == HIGH ){
      digitalWrite(SP,LOW);
      MsTimer2::stop();
      MsTimer2::start();
    }
    if( digitalRead(Wsw) == HIGH ){
      digitalWrite(SP,LOW);
      MsTimer2::stop();
      MsTimer2::start();
    }
    if( digitalRead(Bsw) == HIGH ){
      digitalWrite(SP,LOW);
      MsTimer2::stop();
      MsTimer2::start();
    }
    //カーソル移動
    if( digitalRead(Rsw) == HIGH){
      digitalWrite(SP,LOW);
      cx = cx + 1;
      if( cx == 1 ){
        cx = 5;
        lcd.setCursor(cx,2);
        lcd.cursor();
      }
      if( cx == 6 ){
        cx = 7;
        lcd.setCursor(cx,2);
        lcd.cursor();
      }
      if( cx >= 8 ){
        cx = 2;
        lcd.setCursor(cx,2);
        lcd.cursor();
      }
      lcd.setCursor(cx,2);
      lcd.cursor();
      delay(400);
    }
    //数字の増及び決定
    if( digitalRead(Wsw) == HIGH ){
      digitalWrite(SP,LOW);
      delay(400);
      switch(cx){
      case 2:
        a1 = a1 + 1;
        if( a1 == 10 ){
          a1 = 0;
        }
        wakeuplcd();
        break;
      case 3:
        a2 = a2 + 1;
        if( a2 == 10 ){
          a2 = 0;
        }
        wakeuplcd();
        break;
      case 4:
        a3 = a3 + 1;
        if( a3 == 10 ){
          a3 = 0;
        }
        wakeuplcd();
        break;
      case 5:
        a4 = a4 + 1;
        if( a4 == 10 ){
          a4 = 0;
        }
        wakeuplcd();
        break;
      case 7:
        check();
        break;
      }
    }
    //数字の減及び決定
    if( digitalRead(Bsw) == HIGH ){
      digitalWrite(SP,LOW);
      delay(400);
      switch(cx){
      case 2:
        a1 = a1 - 1;
        if( a1 == -1 ){
          a1 = 9;
        }
        wakeuplcd();
        break;
      case 3:
        a2 = a2 - 1;
        if( a2 == -1 ){
          a2 = 9;
        }
        wakeuplcd();
        break;
      case 4:
        a3 = a3 - 1;
        if( a3 == -1 ){
          a3 = 9;
        }
        wakeuplcd();
        break;
      case 5:
        a4 = a4 - 1;
        if( a4 == -1 ){
          a4 = 9;
        }
        wakeuplcd();
        break;
      case 7:
        check();
        break;
      }
    }
  }
}

void check(void){
  q = num1 + num2;
  w = (a1 * 1000) + (a2 * 100) + (a3 *10) + a4;
  if( q == w ){
    e = e - 1;
    if( e == -1 ){
      digitalWrite(2,LOW);
    }
    wakeup();
  }
  if( q != w ){
    wakeup();
  }
}

void setup() {
  //電源をホールド
  pinMode(2,OUTPUT);
  digitalWrite(2,HIGH);
  delay(10);
  //ポート初期設定
  pinMode(Rsw,INPUT);
  pinMode(Wsw,INPUT);
  pinMode(Bsw,INPUT);
  pinMode(SP,OUTPUT);
  //オープニング
  lcd.begin(16,2);
  lcd.print("DG001 prototype");
  lcd.setCursor(0, 2);
  lcd.print("ver1.00");
  delay(1991);
  //初期タイマー設定画面
  alarm();

}

void loop() {
  //カーソル移動

  if( digitalRead(Rsw) == HIGH){
    cx = cx + 1;
    if( cx == 2){
      cx = 3;
      lcd.setCursor(cx,2);
      lcd.cursor();
    }
    if( cx == 5 ){
      cx = 7;
      lcd.setCursor(cx,2);
      lcd.cursor();
    }
    if( cx >= 8 ){
      cx = 0;
      lcd.setCursor(cx,2);
      lcd.cursor();
    }
    lcd.setCursor(cx,2);
    lcd.cursor();
    delay(400);
  }
  //数字の増及び決定
  if( digitalRead(Wsw) == HIGH ){
    delay(400);
    switch(cx){
    case 0:
      hour1 = hour1 + 1;
      if( hour1 == 10 ){
        hour1 = 0;
      }
      alarm();
      break;
    case 1:
      hour2 = hour2 + 1;
      if( hour2 == 10 ){
        hour2 = 0;
      }
      alarm();
      break;
    case 3:
      minute1 = minute1 + 1;
      if( minute1 == 10 ){
        minute1 = 0;
      }
      alarm();
      break;
    case 4:
      minute2 = minute2 + 1;
      if( minute2 == 10 ){
        minute2 = 0;
      }
      alarm();
      break;
    case 7:
      timer();
      break;
    }
  }
  //数字の減及び決定
  if( digitalRead(Bsw) == HIGH ){
    delay(400);
    switch(cx){
    case 0:
      hour1 = hour1 - 1;
      if( hour1 == -1 ){
        hour1 = 9;
      }
      alarm();
      break;
    case 1:
      hour2 = hour2 - 1;
      if( hour2 == -1 ){
        hour2 = 9;
      }
      alarm();
      break;
    case 3:
      minute1 = minute1 - 1;
      if( minute1 == -1 ){
        minute1 = 9;
      }
      alarm();
      break;
    case 4:
      minute2 = minute2 - 1;
      if( minute2 == -1 ){
        minute2 = 9;
      }
      alarm();
      break;
    case 7:
      timer();
      break;
    }
  }
}




