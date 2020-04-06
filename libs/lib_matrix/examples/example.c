#include <matrix.h>

int main(){
	initSPI();
	initMatrix();
	drawGood();
	sleep(2);
	drawBad();
	sleep(2);
	turnOffMatrix();
	return 1;
}


