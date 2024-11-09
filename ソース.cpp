#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

struct TickCounter{
	intmax_t Master = 0;
	intmax_t Tick = 0;
	intmax_t Trap = 0;
};

TickCounter ConstructTicConter(intmax_t Trap) {
	TickCounter T;
	T.Master = 0;
	T.Tick = 0;
	T.Trap = Trap;

	return T;
}
bool SetMaster(TickCounter&In,intmax_t N){
	In.Master = N;
	return true;
}

bool Inc(TickCounter& In) {
	In.Master++;
	return true;
}
bool Dec(TickCounter& In) {
	In.Master--;
	return true;
}
bool Update(TickCounter& In) {
	In.Tick = In.Master / In.Trap;
	return true;
}
bool IsRise(TickCounter& In) {
	intmax_t N = In.Master % In.Trap;

	return N == In.Trap - 1;
}
intmax_t Tick(TickCounter& In) {
	return In.Tick;
}
intmax_t Master(TickCounter& In) {
	return In.Master;
}
/** /
intmax_t Tick(TickCounter& In) {
	return In.Tick;
}
/**/
struct Clocker {
	intmax_t hour = 0;
	intmax_t minuits = 0;
	intmax_t seconds = 0;

	TickCounter T;
};

Clocker ConstructClocker(intmax_t Trap) {
	Clocker C;
	C.hour = 0;
	C.minuits = 0;
	C.seconds = 0;
	C.T = ConstructTicConter(Trap);
	return C;
}

bool Forward(Clocker& In) {
	return Inc(In.T);
}
intmax_t Master(Clocker& In) {
	return In.T.Master;
}
intmax_t Tick(Clocker& In) {
	return In.T.Tick;
}
bool Update(Clocker& In) {
	Update(In.T);
	In.seconds = Tick(In.T);
	In.minuits = In.seconds % 60;
	In.hour = In.minuits % 60;

	In.seconds %= 60;
	In.minuits %= 60;
	In.hour %= 24;
	return true;
}
intmax_t Lasthour(Clocker& In) {
	return In.hour;
}
intmax_t Lastminuits(Clocker& In) {
	return In.minuits;
}
intmax_t Lastseconds(Clocker& In) {
	return In.seconds;
}

int main() {
	intmax_t Trap = 16;
	intmax_t Tick_ = 60;
	Clocker C = ConstructClocker(Trap);
	time_t S = time(NULL);
	//clock_t E = time(NULL);
	time_t L = 3;

	
	while (Tick(C) <= Tick_) {
		S = time(NULL);
		while (S + L > time(NULL)) {
			//need hardwere sleep.
		}
		Forward(C);
		Update(C);
		printf("%u:%u:%u  %u\r", Lasthour(C), Lastminuits(C), Lastseconds(C),time(NULL));
	}

	printf("%u:%u:%u", Lasthour(C), Lastminuits(C),Lastseconds(C));

	return 0;

 }
/** /
int main() {
	intmax_t Trap = 16;
	intmax_t Tick_ = 60;
	Clocker C = ConstructClocker(Trap);
	clock_t S = clock();
	//clock_t E = clock();
	clock_t L = 7;

	
	while (Tick(C) <= Tick_) {
		S = clock();
		while (S + L > clock()) {
			//need hardwere sleep.
		}
		Forward(C);
		Update(C);
		printf("%d:%d:%d\r", (int)Lasthour(C), (int)Lastminuits(C),(int) Lastseconds(C));
	}

	printf("%d:%d:%d", (int)Lasthour(C), (int)Lastminuits(C),(int) Lastseconds(C));

	return 0;

 }
 /**/