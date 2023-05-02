#include "main.h"
#include "Console.h"
#include "function.h"
using namespace std;
int STrang, SViTriChon, STongMuc;

int main() {

	resizeConsole(ConsoleWidth, ConsoleHeight);
	SetConsoleTitle(TEXT("Game Do Min"));
	Cursor(false);
	veTieuDe();
	veMenuChinh(0);
	STrang = 1;
	xuLySuKien();
}