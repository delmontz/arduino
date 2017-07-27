#include <Wire.h>

void sentDate();
void setup()
{
	
	Wire.begin(0x04);
	Wire.onRequest(sentDate);
	

}


void loop()
{

	  

}

void sentDate(){
	byte data[5] = {1,2,3,4,5};
	Wire.write(data,5);		
}
