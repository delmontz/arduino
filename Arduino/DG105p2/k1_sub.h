//プロトタイプ宣言
void mainMenu(void);
void memo(void);
void memoList(void);
void memoAdd(void);


//**************************************************************
//メインメニュー関数 MEMO PLAN OKAN EX
//**************************************************************
void mainMenu(void){
  cur = 0;
  fillClear();
  GLCD_DrawHoriLine(0,55,127,BLACK);
  GLCD_CursorTo(0,7);
  GLCD_Puts("*MEMO PLAN OKAN EX");
  
  while(1){
  //カーソル移動
  //→
  if(digitalRead(swmigi) == LOW ){
    GLCD_CursorTo(cur,7);
    GLCD_Puts(" ");
    cur = cur + 1;
    switch(cur){
    case 1:
    cur = 5;
    break;
    case 6:
    cur = 10;
    break;
    case 11:
    cur = 15;
    break;
    case 16:
    cur = 0;
    break;
    }
    GLCD_CursorTo(cur,7);
    GLCD_Puts("*");
    delay(300);
  }
  //カーソル移動←
  if(digitalRead(swhidari) == LOW){
    GLCD_CursorTo(cur,7);
    GLCD_Puts(" ");
    cur = cur - 1;
    switch(cur){
    case -1:
    cur = 15;
    break;
    case 14:
    cur = 10;
    break;
    case 9:
    cur = 5;
    break;
    case 4:
    cur = 0;
    break;
    }
    GLCD_CursorTo(cur,7);
    GLCD_Puts("*");
    delay(300);
  }
  //決定
  if(digitalRead(swue) == LOW){
    switch(cur){
      //MEMO選択
      case 0:
      memo();
      break;
      //PLAN選択
      case 5:
      break;
      //OKAN選択
      case 10:
      break;
      //EX選択
      case 15:
      break;
      
    
    }
  }
  
  }
  
  
}

//**************************************************************
//MEMOメニュー関数 LIST ADD DEL
//**************************************************************
void memo(void){
  fillClear();
  GLCD_CursorTo(0,7);
  GLCD_Puts("[MEMO]*LIST ADD DEL");
  cur = 6;
  
  while(1){
  //カーソル移動
  //→
  if(digitalRead(swmigi) == LOW ){
    GLCD_CursorTo(cur,7);
    GLCD_Puts(" ");
    cur = cur + 1;
    switch(cur){
    case 7:
    cur = 11;
    break;
    case 12:
    cur = 15;
    break;
    case 16:
    cur = 6;
    break;
    }
    GLCD_CursorTo(cur,7);
    GLCD_Puts("*");
    delay(300);
  }
  //カーソル移動←
  if(digitalRead(swhidari) == LOW){
    GLCD_CursorTo(cur,7);
    GLCD_Puts(" ");
    cur = cur - 1;
    switch(cur){
    case 5:
    cur = 15;
    break;
    case 14:
    cur = 11;
    break;
    case 10:
    cur = 6;
    break;

    }
    GLCD_CursorTo(cur,7);
    GLCD_Puts("*");
    delay(300);
  }
  //決定
  if(digitalRead(swue) == LOW){
    switch(cur){
      //LIST選択
      case 6:
      memoList();
      break;
      //ADD選択
      case 11:
      memoAdd();
      break;
      //DEL選択
      case 15:
      break;
      
    
    }
  }
  //戻るボタン ゴートゥ　メインメニュ
  if(digitalRead(swsita) == LOW ){
  GLCD_ClearScreen();
  mainMenu();
  }
  
  }

}

//**************************************************************
//MEMO_LIST関数 
//**************************************************************
void memoList(void){
  

}

//**************************************************************
//MEMO_ADD関数 
//**************************************************************
void memoAdd(void){
  //変数宣言
  char str[512] = {0};
  char i = 0;
  char x = 0;
  char u = 0;
  //
  Serial.begin(9600);
  GLCD_ClearScreen();
  GLCD_CursorTo(0,7);
  GLCD_Puts("記録する内容を入力してください");
  while(1){
    if(Serial.available() > 0){ 
    str[i] = Serial.read();
    i++;
    u = 1;
    
    }
    delay(50);
    if( u == 1 && Serial.available() == 0 ){
    pageClear();
    GLCD_CursorTo(0,0);
    GLCD_Puts(str);
    u = 0;
    
    }
   
  }
  
}






