#include "../matrix.c"

int main(){
	initSPI();
	initMatrix();
	drawGood();
	delay(2);
	drawBad();
	return 1;
}


