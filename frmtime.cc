#include <stdshit.h>
#include <algorithm>
#include "ddrawfb.h"
#include "frmtime.h"
#include "hpc.h"

// !!! must be sorted !!!
struct best_range_t { int idx, len; };
template <class V, class U>
best_range_t best_range(
	V fi, int len, U range)
{
	best_range_t best = {};
	for(int start = 0, end = 0;
		(end+1) < len; start++) 
	{
		while((end < len) && (fi[end]-
			fi[start]) < range) end++; 
		if(best.len < (end-start)) {
			best.len = end-start; 
			best.idx = start; }
	}
	return best;
}

struct bestRngAvg_t { double avg; int count; };
template <class V, class U>
long double bestRngAvg(int& count,
	V fi, int len, U range)
{
	auto x = best_range(fi, len, range);
	long double total = 0;
	for(int i = x.idx; i < x.idx+x.len; i++)
		total += fi[i]; total /= x.len; 
	count = x.len; return total;
}

template <class V, class U>
long double bestRngAvg2(int& count,
	V fi, int len, U range)
{
	std::sort(fi, fi+len);
	return bestRngAvg(count, fi, len, range);
}



bool FrameTime::calcTime(
	double& time, int* data, int count)
{
	int avg_count; 
	time = bestRngAvg2(avg_count, 
		data, count, hpc_fromUs(25));
	if(avg_count < (count*9/10)) {
		return false; } return true;
}

HRESULT FrameTime::init(void)
{
	int data[2][MAX_FRAME];
	int* wrPos = data[0];

	
GET_MORE_TIMES:
	IFRET(ddrawFb_spinNotVsync());
	INT64 lastTime;
	for(int i = 0; i <= STEP_FRAME; i++) {
		IFRET(ddrawFb_spinVsync());
		INT64 syncTime; hpc_getTime(&syncTime);
		IFRET(ddrawFb_spinNotVsync());
		INT64 curTime = hpc_getTime();		
		if(i) { wrPos[0] = curTime-syncTime;
			wrPos[MAX_FRAME] = curTime-lastTime; wrPos++; }
		lastTime = curTime;
	}
	
	
	
	int count = wrPos-data[0];
	if(!calcTime(vTime, data[0], count)
	|| !calcTime(fTime, data[1], count)) {
		if(count == MAX_FRAME) return -1;
		goto GET_MORE_TIMES; }
		
	// extra fields
	aTime = fTime-vTime;
	aLines = ddrawFb_ddsd.dwHeight;
	fLines = lrint(aLines*fTime/aTime);
	vLines = lrint(aLines*vTime/aTime);
	lTime = lrint(fTime/fLines);
	return 0;
}

double FrameTime::pixToUsF(int pix)
{
	return hpc_toUsFF(pix*lTime);
}

int FrameTime::pixToUs(int pix)
{
	return lrint(hpc_toUsFF(pix*lTime));
}

int FrameTime::usToPix(int us)
{
	return lrint(hpc_fromUsFF(us/lTime));
}
