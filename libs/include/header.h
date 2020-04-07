#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>

#define CHECK(sts,msg) if ((sts) == -1) {perror(msg);exit(-1);}

