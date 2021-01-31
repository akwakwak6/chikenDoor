#ifndef MoveDoor_h
#define MoveDoor_h

#define CPT_FOR_POWER 40  //4s
#define CPT_TO_MOVE 1000  //100s
#define TIMER_MOVE_AFTER_END 500  //0.5s

void moveDoor(bool up);
int sensorSignal();

#endif
