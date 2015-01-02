#include "lightClass.h"

lightClass::lightClass(void){
	triple n;
	n.x = 0;
	n.y = 0;
	n.z = 0;
}

lightClass::lightClass(triple n){
	pos = n;
}

void lightClass::movebackward(void){
	pos.z -= 0.2;
}

void lightClass::moveforward(void){
	pos.z += 0.2;
}

void lightClass::moveleft(void){
	pos.x -= 0.2;
}

void lightClass::moveright(void){
	pos.x += 0.2;
}

void lightClass::movedown(void){
	pos.y -= 0.2;
}

void lightClass::moveup(void){
	pos.y += 0.2;
}

void lightClass::switchOn(void){
	if (on){
		on = FALSE;
	}
	else{
		on = TRUE;
	}
}