#include <windows.h>
#include <cassert>
#include <iostream>
#include <bitset>
#include <WinUser.h>
#include <windowsx.h>
#include <string>
#include <TlHelp32.h>

auto wide_to_char(const WCHAR* source) {
	const auto wide_char_file_path_length = wcslen(source);
	auto destination_buffer = std::make_unique<char[]>(wide_char_file_path_length + 1);

	auto array_index = 0;
	while (source[array_index] != '\0') {
		destination_buffer.get()[array_index] = static_cast<CHAR>(source[array_index]);
		array_index++;
	}

	destination_buffer.get()[array_index] = '\0';
	return destination_buffer;
}





#define consoleDEBUG
#define ID_BIT_0 100
#define ID_BIT_1 101
#define ID_BIT_2 102
#define ID_BIT_3 103
#define ID_BIT_4 104
#define ID_BIT_5 105
#define ID_BIT_6 106
#define ID_BIT_7 107

#define ID_DEC 800
#define ID_HEX 810
#define ID_OCT 820
#define ID_B32 830

#define ID_ADDR_INPUT 500
#define ID_ADDR_READ 510
#define ID_ADDR_WRITE 520

	HWND hButton_bit_0;
	HWND hButton_bit_1;
	HWND hButton_bit_2;
	HWND hButton_bit_3;
	HWND hButton_bit_4;
	HWND hButton_bit_5;
	HWND hButton_bit_6;
	HWND hButton_bit_7;

	HWND int_dec;
	HWND idec_gbox;

	HWND int_hex;
	HWND int_oct;
	HWND int_b32;

	HWND hEditIaddr;
	HWND hEditREADaddr;
	HWND hEditWRITEaddr;

std::bitset<8> bits(0);

bool change = false;
long long count = 0;
HWND hEdit;
WCHAR hEdit_buffer[128];

wchar_t* dec_buf = new wchar_t;
wchar_t* hex_buf = new wchar_t;
wchar_t* oct_buf = new wchar_t;
wchar_t* b32_buf = new wchar_t;

int old = 0;
wchar_t* oval = new wchar_t;

int lchangedbit = 0;
int lchanger = 0;
wchar_t* READBUFFER = new wchar_t;
int counterREAD = 0;

LRESULT CALLBACK MessageHandler(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	
	switch (uMsg) {
	case WM_CLOSE:
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

		

	case WM_COMMAND:
		
		switch (LOWORD(wParam))
		{

		case ID_ADDR_READ:
		{

			GetWindowText(hEditIaddr, READBUFFER, 20);
			try {
				char* ch = reinterpret_cast<char*>(READBUFFER);
				std::bitset<8> new_bits(ch);
				bits = new_bits;
				change = true;
				break;
			}
			catch (std::invalid_argument)
			{
#ifdef _WIN64
				MessageBox(hWnd, (LPCWSTR)((std::wstring)READBUFFER + (std::wstring)L"is not an valid 64 bit address").c_str(), L"Invalid Address", MB_ICONERROR | MB_OK);
#else
				MessageBox(hWnd, (LPCWSTR)((std::wstring)READBUFFER + (std::wstring)L"is not an valid 32 bit address").c_str(), L"Invalid Address", MB_ICONERROR | MB_OK);
#endif
			}
		}

		case ID_ADDR_WRITE:
		{
			GetWindowText(hEditIaddr, READBUFFER, 20);
			try {
				char* ch = reinterpret_cast<char*>(READBUFFER);
				*ch = (char)bits.to_ulong();
				change = true;
				break;
			}
			catch (std::invalid_argument)
			{
#ifdef _WIN64
				MessageBox(hWnd, (LPCWSTR)((std::wstring)READBUFFER + (std::wstring)L"is not an valid 64 bit address").c_str(), L"Invalid Address", MB_ICONERROR | MB_OK);
#else
				MessageBox(hWnd, (LPCWSTR)((std::wstring)READBUFFER + (std::wstring)L"is not an valid 32 bit address").c_str(), L"Invalid Address", MB_ICONERROR | MB_OK);
#endif
			}

		}





		case ID_BIT_0:
			change = true;
			bits[0] = bits[0] ? 0 : 1;
			std::cout << "Manipulating Bit 0\tNew state: " << bits[0] << "\n";
			lchangedbit = 0;
			break;
		case ID_BIT_1:
			change = true;
			bits[1] = bits[1] ? 0 : 1;
			std::cout << "Manipulating Bit 1\tNew state: " << bits[1] << "\n";
			lchangedbit = 1;
		break;
		case ID_BIT_2:
			change = true;
			bits[2] = bits[2] ? 0 : 1;
			std::cout << "Manipulating Bit 2\tNew state: " << bits[2] << "\n";
			lchangedbit = 2;
			break;
		case ID_BIT_3:
			change = true;
			bits[3] = bits[3] ? 0 : 1;
			std::cout << "Manipulating Bit 3\tNew state: " << bits[2] << "\n";
			lchangedbit = 3;
			break;
		case ID_BIT_4:
			change = true;
			bits[4] = bits[4] ? 0 : 1;
			std::cout << "Manipulating Bit 4\tNew state: " << bits[2] << "\n";
			lchangedbit = 4;
			break;
		case ID_BIT_5:
			change = true;
			bits[5] = bits[5] ? 0 : 1;
			std::cout << "Manipulating Bit 5\tNew state: " << bits[2] << "\n";
			lchangedbit = 5;
			break;
		case ID_BIT_6:
			change = true;
			bits[6] = bits[6] ? 0 : 1;
			std::cout << "Manipulating Bit 6\tNew state: " << bits[2] << "\n";
			lchangedbit = 6;
			break;
		case ID_BIT_7: 
			change = true;
			bits[7] = bits[7] ? 0 : 1;
			std::cout << "Manipulating Bit 7\tNew state: " << bits[2] << "\n";
			lchangedbit = 7;
			break;
		case ID_DEC:
			
		{
			
			GetWindowText(int_dec, dec_buf, 5);
			if (iswdigit(dec_buf[0]))
			{
					std::bitset<8> bitbuffer(_wtoi(dec_buf));
					bits = bitbuffer;
					change = true;
					lchanger = 0;
			}
			break;
		}
			
		case ID_HEX:
			GetWindowText(int_hex, hex_buf, 5);
			std::cout << "Received Hex value\n";
			{
				
				if (iswxdigit(hex_buf[0])) {
					std::bitset<8> bitbuffer_hex(std::stoi(hex_buf, nullptr, 16));
					bits = bitbuffer_hex;
					std::cout << bits << "\n";
					change = true;
					lchanger = 1;
					break;
				}
				
			}
		case ID_OCT:
			GetWindowText(int_oct, oct_buf, 5);
			std::cout << "Received Octal value\n";
			{

				if (iswxdigit(oct_buf[0])) {
					std::bitset<8> bitbuffer_oct(std::stoi(oct_buf, nullptr, 8));
					bits = bitbuffer_oct;
					std::cout << bits << "\n";
					change = true;
					lchanger = 2;
					break;
				}

			}
		case ID_B32:
			GetWindowText(int_b32, b32_buf, 5);
			std::cout << "Received Base32 value\n";
			{

				if (iswalpha(b32_buf[0]) || iswdigit(b32_buf[0])) {
					std::bitset<8> bit_buf_new;
					try {
						std::bitset<8> bitbuffer_b32(std::stoi(b32_buf, nullptr, 32));
						bit_buf_new = bitbuffer_b32;
					}
					catch (std::invalid_argument)
					{
						break;
					}
					bits = bit_buf_new;
					std::cout << bits << "\n";
					change = true;
					lchanger = 3;
					break;
				}

			}
			break;
		

			
			


		}

			

		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

#ifndef consoleDEBUG
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
#endif
#ifdef consoleDEBUG

int main(){
	HINSTANCE hInstance = GetModuleHandle(0);
	int nCmdShow = 5;
#endif 
	   
	HWND HWnd;
	WNDCLASS MAINWINDOW;
	MSG msg;
	MAINWINDOW = {};

	MAINWINDOW.style = CS_HREDRAW | CS_VREDRAW;
	MAINWINDOW.lpfnWndProc = MessageHandler;
	MAINWINDOW.hInstance = hInstance;
	MAINWINDOW.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	MAINWINDOW.lpszClassName = L"Bit-manipulator";
	MAINWINDOW.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	MAINWINDOW.cbClsExtra = NULL;
	MAINWINDOW.cbWndExtra = NULL;
	MAINWINDOW.hCursor = LoadCursor(NULL, IDC_ARROW);

	

	assert(RegisterClass(&MAINWINDOW));
	HWnd = CreateWindow(L"Bit-manipulator", L"Bit-manipulator", WS_OVERLAPPEDWINDOW ^ WS_SIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 430, 250, 0, 0, hInstance, 0);
	
	

	int_dec = CreateWindow(L"edit", L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT | WS_BORDER, 10, 80, 80, 40, HWnd, (HMENU)ID_DEC, hInstance, 0);
	int_hex = CreateWindow(L"edit", L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT | WS_BORDER, 10, 150, 80, 40, HWnd, (HMENU)ID_HEX, hInstance, 0);
	int_oct = CreateWindow(L"edit", L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT | WS_BORDER, 125, 80, 80, 40, HWnd, (HMENU)ID_OCT, hInstance, 0);
	int_b32 = CreateWindow(L"edit", L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT | WS_BORDER, 125, 150, 80, 40, HWnd, (HMENU)ID_B32, hInstance, 0);
	
	idec_gbox = CreateWindow(L"groupbox", L"Decimal", WS_CHILD | WS_VISIBLE | WS_BORDER, 5, 75, 90, 50, HWnd, (HMENU)211, hInstance, 0);

#ifdef MEMORY_IMPLEMENT
	hEditIaddr = CreateWindow(L"edit", L"Adress", WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_BORDER, 230, 80, 170, 40, HWnd, (HMENU)ID_ADDR_WRITE, hInstance, 0);
	hEditREADaddr = CreateWindow(L"button", L"Read", WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT, 230, 150, 80, 40, HWnd, (HMENU)ID_ADDR_WRITE, hInstance, 0);
	hEditWRITEaddr = CreateWindow(L"button", L"Write", WS_TABSTOP | WS_CHILD | WS_VISIBLE | WS_BORDER | BS_FLAT, 320, 150, 80, 40, HWnd, (HMENU)ID_ADDR_WRITE, hInstance, 0);

#else
	HWND info = CreateWindow(L"edit", L"The manipulator supports(yet) only littler endian\nThe complete source code is available on Github under: LINK", WS_CHILD | ES_READONLY | WS_VISIBLE | ES_MULTILINE | WS_BORDER | BS_FLAT | ES_CENTER, 230, 80, 170, 110, HWnd, (HMENU)234, hInstance, 0);


#endif
	hButton_bit_7 = CreateWindow(L"button", bits[7] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 10, 10, 40, 40, HWnd, (HMENU)ID_BIT_7, hInstance, 0);
	hButton_bit_6 = CreateWindow(L"button", bits[6] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 60, 10, 40, 40, HWnd, (HMENU)ID_BIT_6, hInstance, 0);
	hButton_bit_5 = CreateWindow(L"button", bits[5] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 110, 10, 40, 40, HWnd, (HMENU)ID_BIT_5, hInstance, 0);
	hButton_bit_4 = CreateWindow(L"button", bits[4] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 160, 10, 40, 40, HWnd, (HMENU)ID_BIT_4, hInstance, 0);
	hButton_bit_3 = CreateWindow(L"button", bits[3] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 210, 10, 40, 40, HWnd, (HMENU)ID_BIT_3, hInstance, 0);
	hButton_bit_2 = CreateWindow(L"button", bits[2] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 260, 10, 40, 40, HWnd, (HMENU)ID_BIT_2, hInstance, 0);
	hButton_bit_1 = CreateWindow(L"button", bits[1] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 310, 10, 40, 40, HWnd, (HMENU)ID_BIT_1, hInstance, 0);
	hButton_bit_0 = CreateWindow(L"button", bits[0] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 360, 10, 40, 40, HWnd, (HMENU)ID_BIT_0, hInstance, 0);

	ShowWindow(HWnd, nCmdShow);
	SetForegroundWindow(HWnd);
	SetFocus(HWnd);
	UpdateWindow(HWnd);
	std::cout << "Created Window\n";
	wchar_t* buf = new wchar_t;
	wchar_t* bufhex = new wchar_t;
	wchar_t* bufoct = new wchar_t;
	wchar_t* bufb32 = new wchar_t;

	for (;;)
	{
		
		BOOL res = GetMessage(&msg, 0, 0, 0);
		if (res > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			if (change == true)
			{
				
				if (lchanger != 0) {
					_itow_s((int)bits.to_ulong(), buf, 4, 10);
					Edit_SetText(int_dec, (LPCWSTR)buf);
					std::wcout << "assigned new val to dec: " << buf << "\n";
				}

				if (lchanger != 1) {
					_itow_s((int)bits.to_ulong(), bufhex, 4, 16);
					Edit_SetText(int_hex, (LPCWSTR)bufhex);
					std::wcout << "assigned new val to hex: " << bufhex << "\n";
				}
				if (lchanger != 2) {
					_itow_s((int)bits.to_ulong(), bufoct, 4, 8);
					Edit_SetText(int_oct, (LPCWSTR)bufoct);
					std::wcout << "assigned new val to oct: " << bufoct << "\n";
				}
				if (lchanger != 3) {
					_itow_s((int)bits.to_ulong(), bufb32, 4, 32);
					Edit_SetText(int_b32, (LPCWSTR)bufb32);
					std::wcout << "assigned new val to oct: " << bufb32 << "\n";
				}
				switch (lchangedbit)
				{


				case 0:	DestroyWindow(hButton_bit_0); hButton_bit_0 = CreateWindow(L"button", bits[0] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 360, 10, 40, 40, HWnd, (HMENU)ID_BIT_0, hInstance, 0); break;
				case 1:	DestroyWindow(hButton_bit_1); hButton_bit_1 = CreateWindow(L"button", bits[1] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 310, 10, 40, 40, HWnd, (HMENU)ID_BIT_1, hInstance, 0); break;
				case 2:	DestroyWindow(hButton_bit_2); hButton_bit_2 = CreateWindow(L"button", bits[2] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 260, 10, 40, 40, HWnd, (HMENU)ID_BIT_2, hInstance, 0); break;
				case 3:	DestroyWindow(hButton_bit_3); hButton_bit_3 = CreateWindow(L"button", bits[3] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 210, 10, 40, 40, HWnd, (HMENU)ID_BIT_3, hInstance, 0); break;
				case 4:	DestroyWindow(hButton_bit_4); hButton_bit_4 = CreateWindow(L"button", bits[4] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 160, 10, 40, 40, HWnd, (HMENU)ID_BIT_4, hInstance, 0); break;
				case 5:	DestroyWindow(hButton_bit_5); hButton_bit_5 = CreateWindow(L"button", bits[5] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 110, 10, 40, 40, HWnd, (HMENU)ID_BIT_5, hInstance, 0); break;
				case 6:	DestroyWindow(hButton_bit_6); hButton_bit_6 = CreateWindow(L"button", bits[6] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 60, 10,  40, 40, HWnd, (HMENU)ID_BIT_6, hInstance, 0); break;
				case 7:	DestroyWindow(hButton_bit_7); hButton_bit_7 = CreateWindow(L"button", bits[7] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 10, 10,  40, 40, HWnd, (HMENU)ID_BIT_7, hInstance, 0); break;


				}


				if (lchangedbit == -1)
				{
					DestroyWindow(hButton_bit_0); hButton_bit_0 = CreateWindow(L"button", bits[0] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 360, 10, 40, 40, HWnd, (HMENU)ID_BIT_0, hInstance, 0);
					DestroyWindow(hButton_bit_1); hButton_bit_1 = CreateWindow(L"button", bits[1] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 310, 10, 40, 40, HWnd, (HMENU)ID_BIT_1, hInstance, 0); 
					DestroyWindow(hButton_bit_2); hButton_bit_2 = CreateWindow(L"button", bits[2] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 260, 10, 40, 40, HWnd, (HMENU)ID_BIT_2, hInstance, 0); 
					DestroyWindow(hButton_bit_3); hButton_bit_3 = CreateWindow(L"button", bits[3] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 210, 10, 40, 40, HWnd, (HMENU)ID_BIT_3, hInstance, 0); 
					DestroyWindow(hButton_bit_4); hButton_bit_4 = CreateWindow(L"button", bits[4] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 160, 10, 40, 40, HWnd, (HMENU)ID_BIT_4, hInstance, 0); 
					DestroyWindow(hButton_bit_5); hButton_bit_5 = CreateWindow(L"button", bits[5] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 110, 10, 40, 40, HWnd, (HMENU)ID_BIT_5, hInstance, 0); 
					DestroyWindow(hButton_bit_6); hButton_bit_6 = CreateWindow(L"button", bits[6] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 60, 10, 40, 40, HWnd, (HMENU)ID_BIT_6, hInstance, 0);
					DestroyWindow(hButton_bit_7); hButton_bit_7 = CreateWindow(L"button", bits[7] ? L"1" : L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_FLAT, 10, 10, 40, 40, HWnd, (HMENU)ID_BIT_7, hInstance, 0); 
				}


				lchangedbit = -1;

				change = false;
			}
		}
		else
		{
			return res;
		}
	}
	
	return 0;

}