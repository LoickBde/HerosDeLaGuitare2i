#include "../matrix.c"

int main(){
	initSPI();
	initMatrix();
	drawGood();
	sleep(2);
	drawBad();
	return 1;
}


