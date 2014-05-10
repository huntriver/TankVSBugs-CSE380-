#pragma once

#include "sssf\gsm\sprite\Effect.h"
#include "sssf\gsm\sprite\AnimatedSprite.h"

class FireEffect : public Effect
{
private:
	bool start;
	bool inProgress;
	bool stop;
	AnimatedSprite* player;
	int attack;

public:
	FireEffect(){stop=false;start=false;inProgress=false;attack=50;}
	bool isStart(){return start;}
	bool isStop(){return stop;}
	bool isInProgress(){return inProgress;}
	void setStart(bool initStart){start = initStart;}
	bool setInProgress(bool initInProgress){inProgress = initInProgress;}
	int getAttack() {return attack;}
	void setStop(bool initStop) {stop = initStop;}
	void changeFrame();
	void updateSprite();
	void setPlayer(AnimatedSprite* initPlayer){player = initPlayer;}
	void setAttack(int initAttack){attack = initAttack;}
};