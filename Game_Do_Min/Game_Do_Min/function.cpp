#include "main.h"
#include "function.h"
#include "Console.h"
CauTrucBang CTBang;
CauTrucO** CTO;
COORD CViTriConTro;
bool BSuDungPhim = false;

int SToaDoX;
int SToaDoY;

bool BTrangThaiChoiGame = false;



void taoMang_2_chieu() {
	CTO = new CauTrucO * [CTBang.SDong];
	for (int i = 0; i < CTBang.SDong; i++) {
		CTO[i] = new CauTrucO[CTBang.SCot];
	}
}



void xoaMang_2_chieu() {
	for (int i = 0; i < CTBang.SDong; i++) {
		delete[]CTO[i];
	}
	delete[]CTO;
}

void luuToaDoBang() {
	SToaDoX = ((ConsoleWidth / 2) - (CTBang.SDong));
	SToaDoY = ((ConsoleHeight - 6) - CTBang.SCot) / 2 + 4;
}

void khoiTao(int SDong, int SCot, int SSoBom) {
	CTBang.SDong = SDong;
	CTBang.SCot = SCot;
	CTBang.SSoBom = SSoBom;
	CTBang.SSoODaMo = 0;
	CTBang.SSoCo = 0;

	taoMang_2_chieu();
	luuToaDoBang();
	CViTriConTro = { 0,0 };
	BTrangThaiChoiGame = true;
	veBang();
	taoBomNgauNhien();
	veTrangThaiChoiGame(1, 0, 0);
	/*xoaMang_2_chieu();*/
}

int toaDoX(int SX) {
	return(SX * 2) + SToaDoX;
}

int toaDoY(int SY) {
	return (SY + SToaDoY);
}

void veO(int SX, int SY, int SKieu) {
	LPSTR str;
	switch (SKieu) {
	case 0:
		str = (LPSTR)"  ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 10, str);
		break;
	case 1:
		str = (LPSTR)"1 ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 9, 15, str);
		break;
	case 2:
		str = (LPSTR)"2 ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 2, 15, str);
		break;
	case 3:
		str = (LPSTR)"3 ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 15, str);
		break;
	case 4:
		str = (LPSTR)"4 ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 1, 15, str);
		break;
	case 5:
		str = (LPSTR)"5 ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 4, 15, str);
		break;
	case 6:
		str = (LPSTR)"6 ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 3, 15, str);
		break;
	case 7:
		str = (LPSTR)"7 ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 15, str);
		break;
	case 8:
		str = (LPSTR)"8 ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 13, 15, str);
		break;
	case 9:
		str = (LPSTR)"B ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 12, str);
		break;
	case 10:
		str = (LPSTR)"  ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 8, str);
		break;
	case 11:
		str = (LPSTR)"  ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 0, 7, str);
		break;
	case 12:
		str = (LPSTR)" ";
		setColorBGTextXY(toaDoX(SX) + 1, toaDoY(SY), 0, 13, str);
		break;
	case 13:
		str = (LPSTR)"P ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, str);
		break;
	case 14:
		str = (LPSTR)"Px";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 15, 6, str);
		break;
	case 15:
		str = (LPSTR)"B ";
		setColorBGTextXY(toaDoX(SX), toaDoY(SY), 12, 14, str);
		break;
	}
}
void veBang() {
	for (int i = 0; i < CTBang.SDong; ++i) {
		for (int j = 0; j < CTBang.SCot; ++j) {
			if (CTO[i][j].BCamCo == true) veO(j, i, 13);
			else if (CTO[i][j].SBomLanCan) veO(j, i, CTO[i][j].SBomLanCan);
			else if (CTO[i][j].BDaMo) veO(j, i, 0);
			else if ((i + j) % 2) veO(j, i, 10);
			else veO(j, i, 11);

			if (BSuDungPhim) veO(CViTriConTro.X, CViTriConTro.Y, 12);
		}
	}
}

void taoBomNgauNhien() {
	int SSoBom = CTBang.SSoBom;
	int SI, SJ;
	srand(time(NULL));
	while (SSoBom) {
		SI = rand() % CTBang.SDong;
		SJ = rand() % CTBang.SCot;
		if (CTO[SI][SJ].BCoBom) continue;
		CTO[SI][SJ].BCoBom = true;
		--SSoBom;
	}
}


void clickPhai(int SX, int SY) {
	if (!(CTO[SX][SY].BDaMo)) {
		if (CTO[SX][SY].BCamCo) {
			CTO[SX][SY].BCamCo = false;
			CTBang.SSoCo--;
		}
		else {
			if (CTBang.SSoCo <= CTBang.SSoBom) {
				CTO[SX][SY].BCamCo = true;
				CTBang.SSoCo++;
			}
		}
	}
	veBang();

	deleteRow(4, 1);
	veTrangThaiChoiGame(1, 0, 0);
}

int demBomLanCan(int SX, int SY) {
	int SDem = 0;
	for (int i = SX - 1; i <= SX + 1; ++i) {
		for (int j = SY - 1; j <= SY + 1; ++j) {
			if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
				continue;
			if (CTO[i][j].BCoBom) ++SDem;
		}
	}
	return SDem;
}

void moO(int SX, int SY) {
	if (!(CTO[SX][SY].BDaMo) && !CTO[SX][SY].BCamCo) {
		CTO[SX][SY].BDaMo = true;
		CTBang.SSoODaMo++;
		if (CTO[SX][SY].BCoBom) {
			thua();
		}
		else {
			int SSoBomLanCan = demBomLanCan(SX, SY);
			if (SSoBomLanCan) {
				CTO[SX][SY].SBomLanCan = SSoBomLanCan;
			}
			else {
				for (int i = SX - 1; i <= SX + 1; ++i) {
					for (int j = SY - 1; j <= SY + 1; ++j) {
						if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
							continue;
						moO(i, j);
					}
				}
			}
		}
	}
}

void clickTrai(int SX, int SY) {
	if (!(CTO[SX][SY].BDaMo) && !CTO[SX][SY].BCamCo) {
		moO(SX, SY);
		if (BTrangThaiChoiGame) {
			veBang();
			if (thongKeCo()) {
				thang();
			}
		}
	}
}

bool thongKeCo() {
	if ((CTBang.SSoODaMo + CTBang.SSoBom) == (CTBang.SDong * CTBang.SCot))
		return true;
	else return false;
}

void thang() {
	BTrangThaiChoiGame = false;
	xoaMang_2_chieu();
	STrang = 5;
	deleteRow(4, 1);
	veTrangThaiChoiGame(2, 2, 0);
}

void thua() {
	for (int i = 0; i < CTBang.SDong; i++) {
		for (int j = 0; j < CTBang.SCot; j++) {
			if (CTO[i][j].BCamCo) {
				if (CTO[i][j].BCoBom) veO(j, i, 15); // cắm cờ đúng
				else veO(j, i, 14);  // cắm cờ không có bom
			}
			else {
				if (CTO[i][j].BCoBom) veO(j, i, 9); // hiện bom ẩn

			}
		}
	}
	BTrangThaiChoiGame = false;
	xoaMang_2_chieu();
	STrang = 4;
	deleteRow(4, 1);
	veTrangThaiChoiGame(3, 3, 0);
}

void xuLyPhim(KEY_EVENT_RECORD key) {
	if (key.bKeyDown) {
		switch (key.wVirtualKeyCode) {
		case VK_UP:   // mũi tên lên
			switch (STrang) {
			case 1:
				if (STongMuc == 3) {
					if (SViTriChon == 0) SViTriChon = STongMuc - 1;
					else SViTriChon -= 1;
					veMenuChinh(SViTriChon);
				}
				break;
			case 2:
				if (STongMuc == 4) {
					if (SViTriChon == 0) SViTriChon = STongMuc - 1;
					else SViTriChon -= 1;
					veMenuCapDo(SViTriChon);
				}
				break;
			case 3:
				if (BTrangThaiChoiGame) {
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == 0) ? CTBang.SDong - 1 : CViTriConTro.Y - 1);
					veBang();
				}
				break;
			case 4:
				veTrangThaiChoiGame(3, 3, (SViTriChon == 1) ? 0 : 1);
				break;
			case 5:
				veTrangThaiChoiGame(2, 2, (SViTriChon == 1) ? 0 : 1);
				break;
			}
			break;
		case VK_DOWN:  // mũi tên xuống
			switch (STrang) {
			case 1:
				if (STongMuc == 3) {
					if (SViTriChon == STongMuc - 1) SViTriChon = 0;
					else SViTriChon += 1;
					veMenuChinh(SViTriChon);
				}
				break;
			case 2:
				if (STongMuc == 4) {
					if (SViTriChon == STongMuc - 1) SViTriChon = 0;
					else SViTriChon += 1;
					veMenuCapDo(SViTriChon);
				}
				break;
			case 3:
				if (BTrangThaiChoiGame) {
					BSuDungPhim = true;
					CViTriConTro.Y = ((CViTriConTro.Y == CTBang.SDong - 1) ? 0 : CViTriConTro.Y + 1);
					veBang();
				}
				break;
			case 4:
				veTrangThaiChoiGame(3, 3, (SViTriChon == 0) ? 1 : 0);
				break;
			case 5:
				veTrangThaiChoiGame(2, 2, (SViTriChon == 0) ? 1 : 0);
				break;
			}
			break;
		case VK_LEFT:  // mũi tên trái
			if (BTrangThaiChoiGame) {
				BSuDungPhim = true;
				CViTriConTro.X = ((CViTriConTro.X == 0) ? CTBang.SCot - 1 : CViTriConTro.X - 1);
				veBang();
			}
			break;
		case VK_RIGHT:  // mũi tên phải
			if (BTrangThaiChoiGame) {
				BSuDungPhim = true;
				CViTriConTro.X = ((CViTriConTro.X == CTBang.SCot - 1) ? 0 : CViTriConTro.X + 1);
				veBang();
			}
			break;
		case VK_RETURN:   // Enter
			switch (STrang) {
			case 1:
				if (SViTriChon == 0) {
					STrang = 2;
					deleteRow(4, 5);
					veMenuCapDo(0);
				}
				else if (SViTriChon == 1) {
					STrang = 6;
					deleteRow(4, 10);
					thongTin();
				}
				else if (SViTriChon == 2) {

				}
				else exit(0);
				break;
			case 2:
				if (SViTriChon == 0) {
					STrang = 3;
					deleteRow(4, 10);
					khoiTao(9, 9, 10);

				}
				else if (SViTriChon == 1) {
					STrang = 3;
					deleteRow(4, 10);
					khoiTao(16, 16, 40);
				}
				else if (SViTriChon == 2) {
					STrang = 3;
					deleteRow(4, 10);
					khoiTao(24, 24, 90);
				}
				else {
					STrang = 1;
					deleteRow(4, 10);
					veMenuChinh(0);
				}
				break;
			case 4:
				if (SViTriChon == 1) {
					STrang = 1;
					deleteRow(3, 4);
					deleteRow(6, 24);
					veMenuChinh(0);
					
				}
				else {
					STrang = 3;
					deleteRow(3, 2);
					khoiTao(CTBang.SDong, CTBang.SCot, CTBang.SSoBom);
					veTrangThaiChoiGame(1, 0, 0);

				}
				break;
			case 5:
				if (SViTriChon == 1) {
					STrang = 1;
					deleteRow(3, 4);
					deleteRow(6, 24);
					veMenuChinh(0);

				}
				else {
					STrang = 3;
					deleteRow(3, 2);
					khoiTao(CTBang.SDong, CTBang.SCot, CTBang.SSoBom);
					veTrangThaiChoiGame(1, 0, 0);

				}
				break;
			case 6:
				break;
			}
			break;
		case VK_ESCAPE:  // Phím ÉC để thoát
			switch (STrang) {
			case 1:
				exit(0);
				break;
			case 2:
				STrang = 1;
				deleteRow(4, 10);
				veMenuChinh(0);
				break;
			case 3:
				STrang = 2;
				deleteRow(3, 27);
				veMenuCapDo(0);
				break;
			case 4:
				STrang = 2;
				deleteRow(3, 27);
				veMenuCapDo(0);
				break;
			case 5:
				STrang = 2;
				deleteRow(4, ConsoleHeight - 3);
				veMenuCapDo(0);
				break;
			case 6:
				STrang = 1;
				deleteRow(3, 17);
				veMenuChinh(0);
				break;
			}
			break;
		case ClickTrai:  //Phím z để mở Ô
			clickTrai(CViTriConTro.Y, CViTriConTro.X);

			break;
		case ClickPhai:  // phím x để đánh dấu cờ
			clickPhai(CViTriConTro.Y, CViTriConTro.X);

			break;
		}
	}
}

// số 1 là Menu chính. 
// số 2 là menu chọn cấp độ
// số 3 trang chơi game
// số 4 là trng thua
// số 5 trang thắng
// số 6 trang lưu game





void xuLySuKien() {
	while (1) {
		DWORD DWNumberOfEvents = 0;  //lưu sự kiện hiện tại
		DWORD DWNumberOfEventsRead = 0;  // lưu số lượng sự kiện đã được lọc

		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE); // thiết bị đầu vào
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents);  // dắt sự kiện đầu vào của giao diện cho biến
		if (DWNumberOfEvents) {
			INPUT_RECORD* IREventBuffer = new INPUT_RECORD;
			ReadConsoleInput(HConsoleInput, IREventBuffer, DWNumberOfEvents, &DWNumberOfEventsRead); // dắt các sự kiện được lưu vào con trỏ EventBuffer

			for (DWORD i = 0; i < DWNumberOfEvents; i++) {
				if (IREventBuffer[i].EventType == KEY_EVENT) {
					xuLyPhim(IREventBuffer[i].Event.KeyEvent);
				}
				/*else if (IREventBuffer[i].EventType == MOUSE_EVENT) {

				}*/
			}
		}
	}

}


void veTieuDe() {
	int i;
	for (i = 0; i < ConsoleWidth; i++) {
		printf("%c", 45);
	}
	cout << endl;
	LPSTR str = (LPSTR)"Game Do Min";
	setColorBGTextXY((ConsoleWidth / 2) - 5, 1, 5, 0, str);
	cout << endl;
	setColor(7);
	for (i = 0; i < ConsoleWidth; i++) {
		printf("%c", 45);
	}
}

void veTrangThaiChoiGame(int STrangThai, int SCheDo, int SIndex) {
	SViTriChon = SIndex;
	STongMuc = 2;

	char str1[50];
	sprintf_s(str1, sizeof(str1), "Ban Do: %d * %d", CTBang.SDong, CTBang.SCot);
	LPSTR lpstr1 = str1;
	setColorBGTextXY(1, 3, 15, 0, lpstr1);

	char str2[50];
	sprintf_s(str2, sizeof(str2), "So Bom: %d", CTBang.SSoBom - CTBang.SSoCo);
	LPSTR lpstr2 = str2;
	setColorBGTextXY(1, 4, 15, 0, lpstr2);

	if (SCheDo == 1) {
		string STRNewGame1 = "  CHOI LAI  ";
		LPSTR str1 = (LPSTR)STRNewGame1.c_str();
		setColorBGTextXY((ConsoleWidth / 2) - (STRNewGame1.length() / 2), 3, 15, ((SIndex == 0) ? 2 : 0), str1);
	}
	if (SCheDo == 2) {
		string STRNewGame1 = "  CHOI LAI  ";
		LPSTR str1 = (LPSTR)STRNewGame1.c_str();
		setColorBGTextXY((ConsoleWidth / 2) - (STRNewGame1.length() / 2), 3, 15, ((SIndex == 0) ? 2 : 0), str1);
	}
	if (SCheDo == 3) {
		string STRNewGame1 = "  CHOI LAI  ";
		LPSTR str1 = (LPSTR)STRNewGame1.c_str();
		setColorBGTextXY((ConsoleWidth / 2) - (STRNewGame1.length() / 2), 3, 15, ((SIndex == 0) ? 2 : 0), str1);
	}
	if (SCheDo >= 1) {
		string STRNewGame = "  THOAT  ";
		LPSTR str = (LPSTR)STRNewGame.c_str();
		setColorBGTextXY((ConsoleWidth / 2) - (STRNewGame.length() / 2), 4, 15, ((SIndex == 1) ? 2 : 0), str);
	}

	if (STrangThai == 1) { // đang chơi
		LPSTR str3 = (LPSTR)"Trang Thai: Dang Choi";
		setColorBGTextXY(ConsoleWidth - 22, 4, 15, 0, str3);
	}
	if (STrangThai == 2) { // thắng 
		LPSTR str3 = (LPSTR)"Trang Thai: Thang";;
		setColorBGTextXY(ConsoleWidth - 22, 4, 4, 0, str3);
	}
	if (STrangThai == 3) { // thua
		LPSTR str3 = (LPSTR)"Trang Thai: Thua";
		setColorBGTextXY(ConsoleWidth - 22, 4, 4, 0, str3);
	}
	cout << endl;
	setColor(7);
	int i;
	for (i = 0; i < ConsoleWidth; i++) {
		printf("%c", 45);
	}

}

void veMenuChinh(int SIndex) {
	SViTriChon = SIndex;
	STongMuc = 3;
	// vẽ menu
	string STRNewGame1 = "  TRO CHOI MOI  ";
	LPSTR str1 = (LPSTR)STRNewGame1.c_str();
	setColorBGTextXY((ConsoleWidth / 2) - (STRNewGame1.length() / 2) + 1, 7, 15, ((SIndex == 0) ? 2 : 0), str1);

	string STRNewGame2 = "  THONG TIN  ";
	LPSTR str2 = (LPSTR)STRNewGame2.c_str();
	setColorBGTextXY((ConsoleWidth / 2) - (STRNewGame2.length() / 2), 8, 15, ((SIndex == 1) ? 2 : 0), str2);

	string STRNewGame3 = "  THOAT  ";
	LPSTR str3 = (LPSTR)STRNewGame3.c_str();
	setColorBGTextXY((ConsoleWidth / 2) - (STRNewGame3.length() / 2), 9, 15, ((SIndex == 2) ? 2 : 0), str3);

	/*string STRNewGame4 = "  THOAT  ";
	LPSTR str4 = (LPSTR)STRNewGame4.c_str();
	setColorBGTextXY((ConsoleWidth / 2) - (STRNewGame4.length() / 2), 10, 15, ((SIndex == 3) ? 2 : 0), str4);*/
}

void veMenuCapDo(int SIndex) {
	SViTriChon = SIndex;
	STongMuc = 4;
	// vẽ menu
	string STRNewGame0 = "CHON CAP DO";
	LPSTR str0 = (LPSTR)STRNewGame0.c_str();
	setColorBGTextXY((ConsoleWidth / 2) - (STRNewGame0.length() / 2), 4, 1, 0, str0);


	string STRNewGame1 = "  DE (9 * 9 VA 10 BOM)  ";
	LPSTR str1 = (LPSTR)STRNewGame1.c_str();
	setColorBGTextXY((ConsoleWidth / 2) - (STRNewGame1.length() / 2), 7, 15, ((SIndex == 0) ? 2 : 0), str1);

	string STRNewGame2 = "  TRUNG BINH (16 * 16 VA 40 BOM)  ";
	LPSTR str2 = (LPSTR)STRNewGame2.c_str();
	setColorBGTextXY((ConsoleWidth / 2) - (STRNewGame2.length() / 2), 8, 15, ((SIndex == 1) ? 2 : 0), str2);

	string STRNewGame3 = "  KHO (24 * 24 VA 99 BOM)  ";
	LPSTR str3 = (LPSTR)STRNewGame3.c_str();
	setColorBGTextXY((ConsoleWidth / 2) - (STRNewGame3.length() / 2), 9, 15, ((SIndex == 2) ? 2 : 0), str3);

	string STRNewGame4 = "  QUAY LAI  ";
	LPSTR str4 = (LPSTR)STRNewGame4.c_str();
	setColorBGTextXY((ConsoleWidth / 2) - (STRNewGame4.length() / 2), 10, 15, ((SIndex == 3) ? 2 : 0), str4);
}

void thongTin() {

	LPSTR str = (LPSTR)"THONG TIN GAME";
	setColorBGTextXY(ConsoleWidth / 2 - 6, 5, 5, 0, str);

	LPSTR str1 = (LPSTR)" \n"
						"       +) DUNG CAC MUI TEN TREN PHIM DE DI CHUYEN GIUA CAC O VA CAC MUC.\n"
						"       +) NHAN 'ENTER' DE CHON CAC MUC CHOI MUON CHON.\n"
						"       +) NHAN 'Z' DE MO O MUON CHON.\n"
						"       +) NHAN 'X' DE CAM CO.\n"
						"       +) NHAN 'EXC' DE THOAT.\n"
						"       *) LUAT CHOI: NGUOI CHOI SE DI TIM VA MO CAC O KHONG CO MIN. \n"
						"     NEU MO TRUNG O CO MIN NGUOI CHOI SE THUA, CON KHI DA MO HET CAC O KHONG CO      MIN NGUOI CHOI SE CHIEN THANG";
	setColorBGTextXY(10, 6, 10, 0, str1);

}
