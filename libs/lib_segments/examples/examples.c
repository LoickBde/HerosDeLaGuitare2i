#include "../segments.c"

int main(){
    initSegments();
    writeScore(2340);
    sleep(3);
    turnOffSegments();
    return 1;
}

