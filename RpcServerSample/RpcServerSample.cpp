// RpcServerSample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "useless_h.h"
#include <windows.h>

extern "C" {
	void UselessProc(unsigned char* pszString)
	{
		printf("%s\n", pszString);
	}
}

	void Shutdown(void) {

	}


int main()
{
	RPC_STATUS status;
	unsigned char* pszProtocolSequence = (unsigned char *)"ncacn_np";
	unsigned char* pszSecurity = NULL;
	unsigned char* pszEndpoint = (unsigned char *)"\\pipe\\useless";
	unsigned int    cMinCalls = 1;
	unsigned int    fDontWait = FALSE;

	status = RpcServerUseProtseqEp(pszProtocolSequence,
		RPC_C_LISTEN_MAX_CALLS_DEFAULT,
		pszEndpoint,
		pszSecurity);

	if (status) exit(status);

	status = RpcServerRegisterIf(useless_v1_0_s_ifspec,
		NULL,
		NULL);

	if (status) exit(status);

	status = RpcServerListen(cMinCalls,
		RPC_C_LISTEN_MAX_CALLS_DEFAULT,
		fDontWait);

	if (status) exit(status);
}

/******************************************************/
/*         MIDL allocate and free                     */
/******************************************************/

void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len)
{
	return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR* ptr)
{
	free(ptr);
}