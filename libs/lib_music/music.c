#include <music.h>

void initMusic(){
    wiringPiSetup();
    softToneCreate(BUZZER_PIN);
}

void setBPM(int bpm){
    // printf("BPM: %d\n",bpm);
    //printf("1 temps = %d ms\n",(int) (60000/bpm));
    time =  (int) 60000/bpm;
}

void playNote(Note note, Rythme rythme){
    //printf("Note : %d\n",note);
    softToneWrite(BUZZER_PIN, note);
    //printf("time : %d\n",time);
    delay(time*(rythme/100));
    softToneWrite(BUZZER_PIN,0);
    delay(time*(rythme/100)/30);
}

void playScale(){   
    playNote(DO,NOIRE);
    playNote(REb,NOIRE);
    playNote(MI,NOIRE);
    playNote(FA,NOIRE);
    playNote(SOLb,NOIRE);
    playNote(SOL,NOIRE);
    playNote(LAb,NOIRE);
    playNote(LA,NOIRE);
    playNote(SIb,NOIRE);
    playNote(SI,NOIRE);
}
