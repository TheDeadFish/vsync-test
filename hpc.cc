#include <stdshit.h>
#include "hpc.h"

INT64 hpc_freq;
double hpc_toUs_;
double hpc_fromUs_;

INITIALIZER(hpc_init) {
	QueryPerformanceFrequency(
		(LARGE_INTEGER*)&hpc_freq);
	hpc_toUs_ = 1e6 / hpc_freq;
	hpc_fromUs_ = hpc_freq / 1e6; }
	
void hpc_spinWaitUs(int us) {
	INT64 tt = hpc_getTime()+hpc_fromUs(us);
	hpc_spinUntil(tt); }
void hpc_spinUntilUs(INT64 base, int us) {
	base += hpc_fromUs(us); hpc_spinUntil(base); }

void hpc_realTime(bool rt) { SetThreadPriority(
	GetCurrentThread(), rt ? 31 : 0); }
