#pragma once

struct FrameTime {
	enum { MAX_FRAME = 120, 
		STEP_FRAME = 30 };

	double fTime, aTime, vTime, lTime; 
	int fLines, aLines, vLines;
	
	HRESULT init(void);
			
	bool calcTime(double& time, 
		int* data, int len);
		
	double pixToUsF(int pix);
	int pixToUs(int pix);
	int usToPix(int us);
	
	
};
