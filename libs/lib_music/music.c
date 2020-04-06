#include <music.h>

void initMusic(){
    wiringPiSetup();
    softToneCreate(BUZZER_PIN);
}

void setBPM(int bpm){
    printf("BPM: %d\n",bpm);
    printf("1 temps = %d ms\n",(int) (60000/bpm));
    time =  (int) 60000/bpm;
}

void playNote(Note note, Rythme rythme){
    printf("Note : %d\n",note);
    softToneWrite(BUZZER_PIN, note);
    printf("time : %d\n",time);
    delay(time*rythme);
    softToneWrite(BUZZER_PIN,0);
}

void playScale(){  
    playNote(DO,BLANCHE);
    playNote(REb,BLANCHE);
    playNote(MI,BLANCHE);
    playNote(FA,BLANCHE);
    playNote(SOLb,BLANCHE);
    playNote(SOL,BLANCHE);
    playNote(LAb,BLANCHE);
    playNote(LA,BLANCHE);
    playNote(SIb,BLANCHE);
    playNote(SI,BLANCHE);
}
