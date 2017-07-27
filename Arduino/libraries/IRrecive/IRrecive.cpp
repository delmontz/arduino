#include "arduino.h"
#include "IRrecive.h"

// IRrecive�C���X�^���X������
IRrecive::IRrecive( unsigned char IR_PIN_ , unsigned char codeNum_  ,  unsigned char DATA_POINT_ , unsigned char * testByte_ )
 {
  // private�ϐ��ɓ���
  IR_PIN_Int = IR_PIN_ ;              // IR�ڑ��s��
  //IRbyte_Int = IRbyte_ ;           // ��M�o�C�g�o�b�t�@�i�|�C���^�j
  testByte_Int = testByte_ ;        // �Œ�o�C�g�ƍ��f�[�^�i�|�C���^�j
  codeNum_Int = codeNum_ ;      // �����R���̌ŗL�o�C�g�ƍ���
  DATA_POINT_Int =  DATA_POINT_ ;  // ��M����f�[�^�̃f�[�^�ʒu
}

// ���\�b�hread
// ��M�o�b�t�@�̓ǂݏo��
unsigned char IRrecive::read(int count) {
  return(IRbyte[count]) ;
}

// ���\�b�htest
// �@��ƍ��Ɛ���f�[�^���o �A��M��������f�[�^��Ԃ�
// 0x100 ��M�������@��ƍ��ł���
unsigned int IRrecive::test(void) {
  unsigned char test = 0 ;
  unsigned int recData = 0x100 ;

  if (byteCount > 0) {              // ��M����
    for (int i = 0; i <= codeNum_Int - 1 ; i++) {
      if (IRbyte[i] == testByte_Int[i]) test++ ;  // �@��ƍ�
    }
    if (test == codeNum_Int) {
      recData = IRbyte[DATA_POINT_Int - 1] ;
    }
  }
  return (recData) ;     // ��M�f�[�^��Ԃ��@�ƍ��ł��˂�0x100
}

// ���\�b�hrecive
// �ԊO�������R���̃f�[�^��M
int IRrecive::recive(void) {
  unsigned long tim = 0 ;
  unsigned char IRbit = 0;           // 8�r�b�g�̃V���A���o�b�t�@
  int bitCount = 0 ;       // �r�b�g��M��
  //int byteCount = 0 ; // �o�C�g�P�ʂ̎�M��
  int bitPoint = 0 ;        // IRbit�̃r�b�g�ݒ�ʒu

  // �o�C�g�o�b�t�@������
  byteCount = 0 ;
  for ( int x = 0 ; x < 10 ; x++)  IRbyte[x] = 0 ;
  // ���[�_���̃`�F�b�N
  if (!digitalRead(IR_PIN_Int) ) {
    tim = micros() ;
    while (!digitalRead(IR_PIN_Int) ) ;       // OFF���ԑ���
    tim = micros() - tim ;
  } else  return(0) ;
  // ���[�_��(3.4ms�ȏ��OFF)�Ȃ��M����
  if (tim >= 3200) {                   // �W��3400�ASharp = 3300�ȉ�
    while (digitalRead(IR_PIN_Int)) ;      // ON�����̂Ă�
    while (1) {
      while (!digitalRead(IR_PIN_Int)) ;   // ON��҂�
      tim = micros() ;
      while (digitalRead(IR_PIN_Int)) {    // ON���ԑ��蒆
        if ((micros() - tim) >= 12000) break ;      // 12ms�ȏ�Ȃ璆�f
      }
      // �f�[�^�̎�M
      tim = micros() - tim ;                      // ON���Ԓl
      if (tim >= 10000) break ;                  // �X�g�b�v�f�[�^
      bitCount++ ;
      if (tim >= 1000)  bitSet(IRbit, bitPoint) ; // ON�������A�f�[�^ = 1
      bitPoint++ ;
      if (byteCount < bitCount / 8) {           // �o�C�g�o�b�t�@�Ɋi�[
        IRbyte[bitCount / 8 - 1 ] = IRbit ;
        byteCount = bitCount / 8 ;
        bitPoint = 0 ;
        IRbit = 0 ;
      }
    }
  }
  return (byteCount) ;
}

void IRrecive::serialOut(void) {
  if (byteCount > 0 ) {
    // �����R�����̓f�[�^�\��
    for (int i = 0 ; i < byteCount ; i++) {
      Serial.print("[") ; Serial.print(read(i), HEX) ;
      Serial.print("]") ;
    }
    Serial.print(" total byte = ") ; Serial.print(byteCount) ;
    Serial.print(" DATA_POINT = ") ; Serial.print(DATA_POINT_Int) ;
    Serial.print(" [") ; Serial.print(read(DATA_POINT_Int - 1), HEX) ;
    Serial.println("]") ;
  }
}