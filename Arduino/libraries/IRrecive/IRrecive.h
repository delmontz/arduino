
#ifndef IRrecive_h
#define IRrecive_h
#include "arduino.h"

// IRrecive �N���X�̐ݒ�
class IRrecive {
  public:
    IRrecive(unsigned char IR_PIN_ , unsigned char codeNum_ , unsigned char DATA_POINT_ , unsigned char *testByte_) ;
    unsigned char read(int) ;
    unsigned int test(void) ;
    int recive(void) ;
    void serialOut(void) ;
  private:
    int byteCount ;
    unsigned char IRbyte[10] ;  
    unsigned char IR_PIN_Int ;         // IR�ڑ��s��
    unsigned char *testByte_Int ;     // �����R���ŗL�ԍ��ƍ��f�[�^
    unsigned char codeNum_Int ;     // �ƍ��o�C�g���@�@�@
    unsigned char DATA_POINT_Int ;  // ��M����f�[�^�̃f�[�^�ʒu
} ;
#endif
