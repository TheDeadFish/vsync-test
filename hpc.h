#pragma once

extern INT64 hpc_freq;
extern double hpc_toUs_;
extern double hpc_fromUs_;

void hpc_init(void);

// time conversion
static inline
double hpc_fromUsFF(double time) {
	return time*hpc_fromUs_; }
static inline
INT64 hpc_fromUs(int time) {
	return llrint(time*hpc_fromUs_); }
static inline
INT64 hpc_fromUs(INT64 base, int time) {
	return base+hpc_fromUs(time); }

static inline
double hpc_toUsFF(double time) {
	return time*hpc_toUs_; }
static inline
int hpc_toUs(INT64 time) {
	return lrint(time*hpc_toUs_); }
static inline
int hpc_toUs(INT64 base, INT64 time) {
	return hpc_toUs(time-base); }
	
// current time query
static inline
void hpc_getTime(INT64* p) {
	QueryPerformanceCounter((LARGE_INTEGER*)p); }
static inline 
INT64 hpc_getTime(void) { INT64 time;
	hpc_getTime(&time); return time; }

// spin wait functins
static 
void hpc_spinUntil(INT64 tt) {
	while(tt > hpc_getTime()); }	
void hpc_spinUntilUs(INT64 base, int us);
void hpc_spinWaitUs(int us);

void hpc_realTime(bool rt);
