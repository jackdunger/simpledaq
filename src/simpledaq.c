#include <stdio.h>
#include <CAENDigitizer.h>

int main(int argc, char* argv[]){
	int handle;
	CAEN_DGTZ_ErrorCode err = CAEN_DGTZ_OpenDigitizer(CAEN_DGTZ_USB, 0, 0, 0, &handle);
	CAEN_DGTZ_BoardInfo_t info;

	if(err){
		printf("can't open\n");
		return 1;
	}
	
	err = CAEN_DGTZ_GetInfo(handle, &info);
	
	if(err){
		printf("can't get info");
		printf("%d\n", err);
		return 3;
	}

	printf(info.ModelName);
	err = CAEN_DGTZ_CloseDigitizer(handle);
	if(err){
		printf("can't close");
		return 2;
	}

	return 0;
}
