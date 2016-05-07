// Win32Project13.cpp: определяет точку входа для приложения.
//

#include "stdafx.h"
#include "Win32Project13.h"
#include <Windowsx.h>
#include "resource.h"
#include <stdlib.h>
#include <cmath>
#include <iostream>
HWND hwnd, hwnd1;
UINT uMsg, uMsg1;
HINSTANCE hInst;
HINSTANCE hSyst;
HINSTANCE hIstatnce;

CHAR ST[128] = {0};		// Исходное (вводимое) число
CHAR RES_1[128] = {0};	// Целая часть
CHAR RES_2[128] = {0};	// Округление




int atof(const char* ST1[]);
int atoi(const char* ST2[]);
int atoi(const char* ST3[]);

double x;	// Исходное (вводимое) число (ST)
int y,	// Целая часть (REZ_1)
	z,	// Округление (REZ_2)
n=10;	// Cистема счисления (DEC - default)


/*BOOL CALLBACK DlgProc_main(HWND, UINT, WPARAM, LPARAM);		// "Основное" окно
BOOL CALLBACK DlgProc_history(HWND, UINT, WPARAM, LPARAM);	// История (мод. окно)
BOOL CALLBACK DlgProc_SS(HWND, UINT, WPARAM, LPARAM);		// Выбор системы счисления (мод. окно)
*/

BOOL CALLBACK DlgProc_SS(HWND hWnd1, UINT uMsg1, WPARAM wParam, LPARAM) 
{
	switch (uMsg1)
	{
	case WM_COMMAND:
		
			switch (LOWORD(wParam))
			{
				// Обработка RadioButton'ов
				if (IsDlgButtonChecked(hwnd1, IDC_BIN) == BST_CHECKED) n = 2; else
					if (IsDlgButtonChecked(hwnd1, IDC_HEX) == BST_CHECKED) n = 6; else
						if (IsDlgButtonChecked(hwnd1, IDC_OCT) == BST_CHECKED) n = 8; else
							if (IsDlgButtonChecked(hwnd1, IDC_DEC) == BST_CHECKED) n = 10;
			case IDCANCEL:
				EndDialog(hWnd1, 0);
				break;
			}
		case WM_CLOSE:
			EndDialog(hWnd1, 0);
			break;
	}
	return FALSE;
}

BOOL CALLBACK DlgProc_main(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM)
{
	FILE *pFile;
	fopen_s(&pFile, "history.txt", "w+");
	switch (uMsg)   // Обработка сообщения
	{
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_SS:	// Выбор СС (из нового окна)
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_SS), hwnd, DlgProc_SS);
		} break;

		case IDC_BUTTON2:	// Обработка кнопки "целая часть"
		{
			SendDlgItemMessageA(hwnd, IDC_EDIT1, WM_GETTEXT, 63, (LPARAM)ST);
			sscanf_s(ST, "%lf", &x);
			y = x;
			sprintf_s(RES_1, "%d", y);
			SetDlgItemTextA(hwnd, IDC_EDIT2, RES_1);
			fprintf_s(pFile, "[%s] = %s\n", ST, RES_1);
		} break;

		case IDC_BUTTON3:	// Обработка кнопки "округление"
		{
			SendDlgItemMessageA(hwnd, IDC_EDIT1, WM_GETTEXT, 63, (LPARAM)ST);
			/*switch (n)
			{
			case (2) : 
			{

			} break;
			case (6) :
			{

			} break;
			case (8) :
			{

			} break;
			case (10) :
			{

			} break;
			default:
				break;
			}*/
			sscanf_s(ST, "%lf", &x);	//default
			z = round(x);
			sprintf_s(RES_2, "%d", z);
			SetDlgItemTextA(hwnd, IDC_EDIT3, RES_2);
			fprintf(pFile, "%lf ~ %d\n", x, y);
		} break;

		case IDC_EXIT:
		{
			DestroyWindow(hwnd);
			PostQuitMessage(0);
		}
			break;




		case WM_CLOSE:
		{
			return FALSE;
		}
			break;
		}
	}
	return FALSE;
}


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_main), 0, (DlgProc_main), 0);
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_SS), 0, (DlgProc_SS), 0);

	hInst = hInstance;

	hwnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DIALOG_main), (HWND)NULL, DlgProc_main);
	if (!hwnd) return FALSE;

	MSG msg;
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		if (!IsWindow(hwnd) || !IsDialogMessage(hwnd, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}	// if (!IsWindow(hMainDlg) || !IsDialogMessage(hMainDlg, &msg))
	}	 //while (GetMessage(&msg, NULL, NULL, NULL))

	return TRUE;
}