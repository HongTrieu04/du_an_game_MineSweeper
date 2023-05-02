#pragma once
#include<iostream>
#include<ctime>
#include<cstring>
#define ClickTrai 0x5A
#define ClickPhai 0X58

#define ConsoleWidth 80
#define ConsoleHeight 35

using namespace std;
struct CauTrucBang {
	int SDong = 0;
	int SCot = 0;
	int SSoBom = 0;
	int SSoODaMo = 0;  // số ô đã mở
	int SSoCo = 0;
};

struct CauTrucO {
	bool BCoBom = false;
	bool BDaMo = false;
	bool BCamCo = false;
	int SBomLanCan = 0;
};
 extern int STrang, SViTriChon, STongMuc;