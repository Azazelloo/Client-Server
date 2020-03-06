#include "AgInfiniiVision.h"
#include <Windows.h> 
#include <assert.h>
#include "Header.h"

static ViSession session;
static char reloadOscill[massSize];

bool InitializationOscilloscope(char *namedir) {
	ViStatus status;
	//char resource[] = "TCPIP0::192.168.0.245::inst0::INSTR";
	char resource[1024] = { 0 };
	GetPrivateProfileStringA((LPCSTR) "ADDRESS_USB", (LPCSTR) "0", (LPCSTR) "ERROR", (LPSTR)resource, (DWORD) sizeof(resource), (LPCSTR)namedir);
	char options[] = "QueryInstrStatus=true, Simulate=false, DriverSetup= Model=, Trace=false, TraceName=c:\\temp\\traceOut";
	ViBoolean idQuery = VI_FALSE;
	ViBoolean reset = VI_FALSE;
	status = AgInfiniiVision_InitWithOptions(resource, idQuery, reset, options, &session);
	if (status)
		return false; //ошибка инициализации осциллографа
	assert(session != VI_NULL);
	//AgInfiniiVision_SystemRecallState(session, 1);
	//AgInfiniiVision_SystemSaveState(session, 1);
	return true;
}

bool CloseOscilloscope() {
	ViStatus status;
	status = AgInfiniiVision_close(session);
	assert(status == VI_SUCCESS);
	session = VI_NULL;
	return true;
}

bool OscillMsgExchange(char *RecvBuffer, char *SendBuffer) {
	if (AgInfiniiVision_SystemWriteString(session, massSize, RecvBuffer)) {
		//для сброса ошибки после отправки ошибочной команды
		AgInfiniiVision_SystemWriteString(session, massSize, "*IDN?");
		AgInfiniiVision_SystemReadString(session, massSize, reloadOscill);
		return false;
	}
	if (AgInfiniiVision_SystemReadString(session, massSize, SendBuffer)) {
		//для сброса ошибки после отправки ошибочной команды
		AgInfiniiVision_SystemWriteString(session, massSize, "*IDN?");
		AgInfiniiVision_SystemReadString(session, massSize, reloadOscill);
		return false;
	}
	return true;
}

bool OscillMsgSend(char *RecvBuffer) {
	if (AgInfiniiVision_SystemWriteString(session, massSize, RecvBuffer))
		return false;
	//для сброса ошибки после отправки ошибочной команды
	AgInfiniiVision_SystemWriteString(session, massSize, "*IDN?");
	AgInfiniiVision_SystemReadString(session, massSize, reloadOscill);
	return true;
}
