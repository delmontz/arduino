
//*****************************
//ポート初期化用
//*****************************
void portSetup(void){
  pinMode(2,INPUT);//INT
  pinMode(3,OUTPUT);//バックライト
  pinMode(4,OUTPUT);//LCDPOWER
  pinMode(5,OUTPUT);//ORANGELED
  pinMode(6,OUTPUT);//BLUELED
  pinMode(7,OUTPUT);//焦電リレー
  pinMode(8,OUTPUT);//ブザー
  pinMode(A3,INPUT);//焦電センサー入力
  pinMode(A2,INPUT);//光センサー入力
  pinMode(A1,INPUT);//温度センサー
  pinMode(A0,INPUT);//距離センサー
  pinMode(12,INPUT_PULLUP);
  pinMode(11,INPUT_PULLUP);
  pinMode(10,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  digitalWrite(3,LOW);
  digitalWrite(4,HIGH);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  digitalWrite(7,LOW);
  digitalWrite(8,LOW);
}
//***********************************
//RTC時刻設定用関数
//***********************************
void rtcLcd(void){
top:
  //各種変数
  char ans = 0;
  char Year1 =0;
  char Year2 =0;
  char Mon1 = 0;
  char Mon2 = 0;
  char mDay1 = 0;
  char mDay2 = 0;
  char wDay = 1;
  char Hour = 0;
  char Min = 0;
  char Sec = 0;
  char cur = 3;
  //本文はここから
  GLCD_ClearScreen();
  GLCD_CursorTo(0,0);
  GLCD_Puts("RTCを初期化します\n");
  talk.SyntheP(PSTR("koreyo'ri/a-ruthi-shi'-o/sho'_ki/kashima'_su."));
  delay(500);
  //日付設定
  talk.SyntheP(PSTR("hizukeo/_shitei_shite/kudasa'i."));
  GLCD_ClearScreen();
  GLCD_CursorTo(0,0);
  GLCD_Puts("日付を設定してください\n");
  GLCD_Puts("20_");
  GLCD_PrintNumber(Year1);
  GLCD_PrintNumber(Year2);
  GLCD_Puts("/");
  GLCD_PrintNumber(Mon1);
  GLCD_PrintNumber(Mon2);
  GLCD_Puts("/");
  GLCD_PrintNumber(mDay1);
  GLCD_PrintNumber(mDay2);
  GLCD_CursorTo(13,1);
  GLCD_Puts("決定");
  GLCD_CursorTo(cur,2);
  GLCD_Puts("＾");
  while(1){
    //カーソル位置
    if( digitalRead(swmigi) == LOW){
      delay(300);
      cur = cur + 1;  
      if(cur == 5){
        cur = 6;
      }
      if(cur == 8){
        cur = 9;
      }
      if(cur == 11){
        cur = 13;
      }
      if(cur == 14){
        cur = 3;
      }
      GLCD_CursorTo(0,2);
      GLCD_Puts("              ");//14空白カーソル相殺
      GLCD_CursorTo(cur,2);
      GLCD_Puts("＾");
    }
    if(digitalRead(swhidari) == LOW){
      delay(300);
      cur = cur - 1;
      if(cur == 2){
        cur = 13;
      }
      if(cur == 12){
        cur = 10;
      }
      if(cur == 8){
        cur = 7;
      }
      if(cur == 5){
        cur = 4;
      }
      GLCD_CursorTo(0,2);
      GLCD_Puts("              ");//14空白カーソル相殺
      GLCD_CursorTo(cur,2);
      GLCD_Puts("＾");
    }
    //数値の増
    if(digitalRead(swue) == LOW){
      delay(300);
      switch(cur){
      case 3:
        Year1 = Year1 + 1;
        if(Year1 == 10){
          Year1 = 0;
        }
        GLCD_CursorTo(cur,1);
        GLCD_PrintNumber(Year1);
        break;
      case 4:
        Year2 = Year2 + 1;
        if(Year2 == 10){
          Year2 = 0;
        }
        GLCD_CursorTo(cur,1);
        GLCD_PrintNumber(Year2);
        break;
      case 6:
        Mon1 = Mon1 + 1;
        if(Mon1 == 2){
          Mon1 = 0;
        }
        GLCD_CursorTo(cur,1);
        GLCD_PrintNumber(Mon1);
        break;
      case 7:
        Mon2 = Mon2 + 1;
        if(Mon2 == 10){
          Mon2 = 0;
        }
        GLCD_CursorTo(cur,1);
        GLCD_PrintNumber(Mon2);
        break;
      case 9:
        mDay1 = mDay1 + 1;
        if(mDay1 == 4){
          mDay1 = 0;
        }
        GLCD_CursorTo(cur,1);
        GLCD_PrintNumber(mDay1);
        break;
      case 10:
        mDay2 = mDay2 + 1;
        if(mDay2 == 10){
          mDay2 = 0;
        }
        GLCD_CursorTo(cur,1);
        GLCD_PrintNumber(mDay2);
        break;
      case 13:
        GLCD_CursorTo(0,2);
        GLCD_Puts("これでよろしいですね\n");
        GLCD_Puts("↑ボタン決定//↓ボタン再設定");
        talk.SyntheP(PSTR("korede/yoroshi'idesune?"));
        while(1){
          if(digitalRead(swue) == LOW){
            goto out;
          }
          if(digitalRead(swsita) == LOW){
            goto top;
          }
        }

      } 
    }
    //数値の減
    if(digitalRead(swsita) == LOW){
      delay(300);
      switch(cur){
      case 3:
        Year1 = Year1 - 1;
        if(Year1 == -1){
          Year1 = 9;
        }
        GLCD_CursorTo(cur,1);
        GLCD_PrintNumber(Year1);
        break;
      case 4:
        Year2 = Year2 - 1;
        if(Year2 == -1){
          Year2 = 9;
        }
        GLCD_CursorTo(cur,1);
        GLCD_PrintNumber(Year2);
        break;
      case 6:
        Mon1 = Mon1 - 1;
        if(Mon1 == -1){
          Mon1 = 1;
        }
        GLCD_CursorTo(cur,1);
        GLCD_PrintNumber(Mon1);
        break;
      case 7:
        Mon2 = Mon2 - 1;
        if(Mon2 == -1){
          Mon2 = 9;
        }
        GLCD_CursorTo(cur,1);
        GLCD_PrintNumber(Mon2);
        break;
      case 9:
        mDay1 = mDay1 - 1;
        if(mDay1 == -1){
          mDay1 = 3;
        }
        GLCD_CursorTo(cur,1);
        GLCD_PrintNumber(mDay1);
        break;
      case 10:
        mDay2 = mDay2 - 1;
        if(mDay2 == -1){
          mDay2 = 9;
        }
        GLCD_CursorTo(cur,1);
        GLCD_PrintNumber(mDay2);
        break;
      case 13:
        GLCD_CursorTo(0,2);
        GLCD_Puts("これでよろしいですね\n");
        GLCD_Puts("↑ボタン決定//↓ボタン再設定");
        talk.SyntheP(PSTR("korede/yoroshi'idesune?"));
        while(1){
          if(digitalRead(swue) == LOW){
            goto out;
          }
          if(digitalRead(swsita) == LOW){
            goto top;
          }
        } 
      }
    }
  }

out:
  talk.SyntheP(PSTR("ji'kokuo/settei_shite/kudasa'i."));
  GLCD_ClearScreen();
  GLCD_CursorTo(0,0);
  GLCD_Puts("時刻を設定してください\n");
  GLCD_Puts("→");
  GLCD_PrintNumber(Hour);
  GLCD_Puts(":");
  GLCD_PrintNumber(Min);
  GLCD_CursorTo(0,2);
  GLCD_Puts("決定は左右同時!!");
  //カーソル位置
  cur = 0;
  while(1){
    if( digitalRead(swmigi) == LOW ){
      cur = 1;
      GLCD_CursorTo(0,1);
      GLCD_Puts("               ");
      GLCD_CursorTo(0,1);
      GLCD_PrintNumber(Hour);
      GLCD_Puts(":");
      GLCD_PrintNumber(Min);
      GLCD_Puts("←");
    }
    if( digitalRead(swhidari) == LOW ){
      cur = 0;
      GLCD_CursorTo(0,1);
      GLCD_Puts("               ");
      GLCD_CursorTo(0,1);
      GLCD_Puts("→");
      GLCD_PrintNumber(Hour);
      GLCD_Puts(":");
      GLCD_PrintNumber(Min);
    }
//数字の増    
    if( digitalRead(swue) == LOW ){
      delay(200);
      switch(cur){
        case 0:
        Hour = Hour + 1;
        if(Hour == 24){
        Hour = 0;
        }
        GLCD_CursorTo(0,1);
        GLCD_Puts("               ");
        GLCD_CursorTo(0,1);
        GLCD_Puts("→");
        GLCD_PrintNumber(Hour);
        GLCD_Puts(":");
        GLCD_PrintNumber(Min);
        break;
        case 1:
        Min = Min + 1;
        if(Min == 60){
        Min = 0;
        }
        GLCD_CursorTo(0,1);
        GLCD_Puts("               ");
        GLCD_CursorTo(0,1);
        GLCD_PrintNumber(Hour);
        GLCD_Puts(":");
        GLCD_PrintNumber(Min);
        GLCD_Puts("←");
        break;
        
      }
      
   
    }
//数字の減
    if( digitalRead(swsita) == LOW ){
      delay(200);
      switch(cur){
        case 0:
        Hour = Hour - 1;
        if(Hour == -1){
        Hour = 23;
        }
        GLCD_CursorTo(0,1);
        GLCD_Puts("               ");
        GLCD_CursorTo(0,1);
        GLCD_Puts("→");
        GLCD_PrintNumber(Hour);
        GLCD_Puts(":");
        GLCD_PrintNumber(Min);
        break;
        case 1:
        Min = Min - 1;
        if(Min == -1){
        Min = 59;
        }
        GLCD_CursorTo(0,1);
        GLCD_Puts("               ");
        GLCD_CursorTo(0,1);
        GLCD_PrintNumber(Hour);
        GLCD_Puts(":");
        GLCD_PrintNumber(Min);
        GLCD_Puts("←");
        break;
        
      }
      
    
    }
//決定選択
    if( digitalRead(swmigi) == LOW && digitalRead(swhidari) == LOW ){
      talk.SyntheP(PSTR("korede/yoroshi'idesune?"));
      GLCD_CursorTo(0,3);
      GLCD_Puts("これでよろしいですね?\n");
      GLCD_Puts("↑決定↓もどる\n");
      while(1){
      if(digitalRead(swue) == LOW){
      goto out2;
      }
      if(digitalRead(swsita) == LOW){
      goto out;
      }
      
      }
      
      
    }

  }//while
out2:
//曜日の設定
  GLCD_ClearScreen();
  GLCD_CursorTo(0,0);
  talk.SyntheP(PSTR("yo-bio/_shitei_shite/kudasa'i."));
  GLCD_Puts("曜日を指定してください\n");
  GLCD_Puts("曜日:");
  GLCD_PrintNumber(wDay);
  GLCD_Puts("←");
  GLCD_CursorTo(0,3);
  GLCD_Puts("日:0 月:1 火:2 水:3\n木:4 金:5 土:6\n");
  GLCD_Puts("決定は左右同時\n");
  while(1){
    if(digitalRead(swue) == LOW){
    delay(300);
    wDay = wDay + 1;
    if( wDay == 7 ){
    wDay = 0;
    }
    GLCD_CursorTo(4,1);
    GLCD_PrintNumber(wDay);
    }
    if(digitalRead(swsita) == LOW){
    delay(300);
    wDay = wDay - 1;
    if( wDay == -1 ){
    wDay = 6;
    }
    GLCD_CursorTo(4,1);
    GLCD_PrintNumber(wDay);
    }
    if( digitalRead(swmigi) == LOW && digitalRead(swhidari) == LOW ){
      talk.SyntheP(PSTR("korede/yoroshi'idesune?"));
      GLCD_CursorTo(0,6);
      GLCD_Puts("これでよろしいですね\n");
      GLCD_Puts("↑決定↓もどる\n");
      while(1){
      if(digitalRead(swue) == LOW){
        digitalWrite(orled,HIGH);
      goto out3;
      }
      if(digitalRead(swsita) == LOW){
      goto out2;
      }
      
      }
     
    }
   }
out3: 
  char Year = (Year1 * 10) + Year2;
  char Mon =  (Mon1 * 10) + Mon2;
  char mDay = (mDay1 * 10) + mDay2;
  ans = RTC.begin(0,Year,Mon,mDay,wDay,Hour,Min,0);
  GLCD_ClearScreen();
  GLCD_CursorTo(0,0);
  if( ans == 0 ){
  GLCD_Puts("RTC初期化成功\n");
  talk.SyntheP(PSTR("a-ruthi-shi-sho_kika/kannryo-."));
  digitalWrite(orled,LOW);
  delay(3000);
  }else{
     GLCD_Puts("RTC初期化失敗");
     while(1){}
  }
  
  
  return;
}

//***************************************
//初期起動用関数（一番初めに呼べ）
//***************************************
void opening(void){
  portSetup();
  delay(10);
  GLCD_Init(NON_INVERTED);
  delay(10);
  GLCD_ClearScreen();
  GLCD_DrawBitmap(gearLogo,0,0,BLACK);
  delay(10);
  talk.SyntheP(PSTR("_shisutemuche'xtu_ku _suta'-to."));
  delay(1500);
  GLCD_ClearScreen();
  GLCD_CursorTo(0,0);
  if(talk.IsActive() == false){
    GLCD_Puts("音声合成LSI エラーを確認\n");
    GLCD_Puts("システムを停止します\n");
    while(1){
    }//無限ループにより機能停止
  }
  else{
    GLCD_Puts("音声合成LSIチェック 正常\n");
    talk.SyntheP(PSTR("eruesuaichextu_kukuri'a."));
    delay(1500);
  }
  //EEPROM初期設定
  char romcheck[] = {
    105            };
  byte ans;
  ans = rom.Write(0,romcheck,1);
  if(ans == 0){
    talk.SyntheP(PSTR("i-i-pi-a-ruo-e'mu/raitoche'xtu_ku kuri'a. "));
    GLCD_Puts("EEPROM書きこみ　成功\n");
    delay(2000);
  }
  else{
    talk.SyntheP(PSTR("i-i-pi-a-ruo-e'mu/raitoche'xtu_ku fe'iru. "));
    GLCD_Puts("EEPROM書きこみ　失敗\n");
    GLCD_Puts("システムを停止します\n");
    while(1){
    }
  }
  ans = rom.Read(0,romcheck,1);
  if(ans == 0){
    talk.SyntheP(PSTR("i-i-pi-a-ruo-e'mu/ri-doche'xtu_ku kuri'a. "));
    GLCD_Puts("EEPROM読みこみ　成功\n");//GLCD三行目
    delay(2000);
  }
  else{
    talk.SyntheP(PSTR("i-i-pi-a-ruo-e'mu/ri-doche'xtu_ku fe'iru. "));
    GLCD_Puts("EEPROM読みこみ　失敗\n");
    GLCD_Puts("システムを停止します\n");
    while(1){
    }
  }
}
//**************************************************************************
//メニュ部分クリア塗りつぶし関数てきな
//***************************************************************************
void fillClear(void){
  GLCD_CursorTo(0,7);
  GLCD_Puts("                     ");
}

//**************************************************************************
//上画面部分ページクリア
//***************************************************************************
void pageClear(void){
  GLCD_CursorTo(0,0);
  GLCD_Puts("                     ");
  GLCD_CursorTo(0,1);
  GLCD_Puts("                     ");
  GLCD_CursorTo(0,2);
  GLCD_Puts("                     ");
  GLCD_CursorTo(0,3);
  GLCD_Puts("                     ");
  GLCD_CursorTo(0,4);
  GLCD_Puts("                     ");
  GLCD_CursorTo(0,5);
  GLCD_Puts("                     ");
}









