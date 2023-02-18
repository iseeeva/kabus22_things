// kabus_launcher.cpp : Defines the entry point for the application.
//
#include "stdafx.h"
#include "kabus_launcher.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPTSTR lpCmdLine,_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_KABUS_LAUNCHER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow)){return FALSE;}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_KABUS_LAUNCHER));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0)){
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int) msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_KABUS_LAUNCHER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)CreatePatternBrush(LoadBitmap(GetModuleHandle(NULL),(LPCSTR)K22_BACKGROUND));
	wcex.lpszMenuName	= NULL; //MAKEINTRESOURCE(IDC_KABUS_LAUNCHER)
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;
   hInst = hInstance;
   hWnd = CreateWindow(szWindowClass, szTitle,WS_CLIPCHILDREN|WS_POPUP,0, 0, 640, 480, NULL, NULL, hInstance, NULL);
   if (!hWnd){return FALSE;}
   GetWindowRect(hWnd,&screen_pos);
   SetWindowPos(hWnd,0, 
  (GetSystemMetrics(SM_CXSCREEN)-screen_pos.right)/2,(GetSystemMetrics(SM_CYSCREEN)-screen_pos.bottom)/2,
   0,0,SWP_NOZORDER|SWP_NOSIZE);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   return TRUE;
}

void K22_loadMenus(HWND hWnd){
try{

#pragma region "LOAD MAIN_MENU"
MAIN_MENU = CreateWindow("STATIC", NULL,WS_CHILD|WS_VISIBLE,Launcher_XY[2*MAIN_FORM+1][0],Launcher_XY[2*MAIN_FORM+1][1],Launcher_XY[2*MAIN_FORM][0],Launcher_XY[2*MAIN_FORM][1],hWnd, (HMENU)MAIN_FORM, NULL, NULL);
SetWindowLongPtr(MAIN_MENU, GWL_WNDPROC, (LONG_PTR)&WndProc);
BTN_RUN_HWND = CreateWindow(TEXT("button"), NULL,WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON|BS_OWNERDRAW,Launcher_XY[2*BTN_RUN+1][0],Launcher_XY[2*BTN_RUN+1][1],Launcher_XY[2*BTN_RUN][0],Launcher_XY[2*BTN_RUN][1],MAIN_MENU, (HMENU)BTN_RUN, NULL, NULL);
BTN_WEB_HWND = CreateWindow(TEXT("button"), NULL,WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON|BS_OWNERDRAW,Launcher_XY[2*BTN_WEB+1][0],Launcher_XY[2*BTN_WEB+1][1],Launcher_XY[2*BTN_WEB][0],Launcher_XY[2*BTN_WEB][1],MAIN_MENU, (HMENU)BTN_WEB, NULL, NULL);
BTN_OPT_HWND = CreateWindow(TEXT("button"), NULL,WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON|BS_OWNERDRAW,Launcher_XY[2*BTN_OPT+1][0],Launcher_XY[2*BTN_OPT+1][1],Launcher_XY[2*BTN_OPT][0],Launcher_XY[2*BTN_OPT][1],MAIN_MENU, (HMENU)BTN_OPT, NULL, NULL);
BTN_EXT_HWND = CreateWindow(TEXT("button"), NULL,WS_VISIBLE|WS_CHILD|BS_PUSHBUTTON|BS_OWNERDRAW,Launcher_XY[2*BTN_EXIT+1][0],Launcher_XY[2*BTN_EXIT+1][1],Launcher_XY[2*BTN_EXIT][0],Launcher_XY[2*BTN_EXIT][1],MAIN_MENU, (HMENU)BTN_EXIT, NULL, NULL);
SetWindowSubclass(MAIN_MENU, &BOYA, MAIN_FORM, 0);
SetWindowSubclass(BTN_RUN_HWND, &BUTTONBOYA, BTN_RUN, 2);
SetWindowSubclass(BTN_WEB_HWND, &BUTTONBOYA, BTN_WEB, 3);
SetWindowSubclass(BTN_OPT_HWND, &BUTTONBOYA, BTN_OPT, 4);
SetWindowSubclass(BTN_EXT_HWND, &BUTTONBOYA, BTN_EXIT, 5);
#pragma endregion

#pragma region "LOAD OPT_MENU"
OPT_MENU = CreateWindow("STATIC", NULL,WS_CHILD|WS_VISIBLE,Launcher_XY[2*OPT_FORM+1][0],Launcher_XY[2*OPT_FORM+1][1],Launcher_XY[2*OPT_FORM][0],Launcher_XY[2*OPT_FORM][1],hWnd, (HMENU)OPT_FORM, NULL, NULL);
SetWindowLongPtr(OPT_MENU, GWL_WNDPROC, (LONG_PTR)&WndProc);
SetWindowSubclass(OPT_MENU, &BOYA, OPT_FORM, 1);
ShowWindow(OPT_MENU,0);

#pragma region "INIT CBOX_WMODE_HWND"
CBOX_WMODE_HWND = CreateWindow("COMBOBOX", NULL,WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|BS_DEFSPLITBUTTON|CBS_DROPDOWN|CBS_HASSTRINGS|WS_VSCROLL,Launcher_XY[2*CBOX_WMODE+1][0],Launcher_XY[2*CBOX_WMODE+1][1],Launcher_XY[2*CBOX_WMODE][0],Launcher_XY[2*CBOX_WMODE][1],OPT_MENU, (HMENU)CBOX_WMODE, NULL, NULL);
for (int i = 0; i < sizeof(CBOX_WMODE_ITEMS)/sizeof(*CBOX_WMODE_ITEMS); i++)
{
strcpy_s(char_dummy, CBOX_WMODE_ITEMS[i]);
SendMessage(CBOX_WMODE_HWND, CB_ADDSTRING, 0, (LPARAM) char_dummy);
}
if(get_ini(ini_fName).wmode_id > sizeof(CBOX_WMODE_ITEMS)/sizeof(*CBOX_WMODE_ITEMS)){
	set_ini(ini_fName,ini_variables[screen_wmode_id], std::to_string(0));
}
SendMessage(CBOX_WMODE_HWND, CB_SETCURSEL, get_ini(ini_fName).wmode_id, 0);
#pragma endregion

#pragma region "INIT CBOX_RES_HWND"
CBOX_RES_HWND = CreateWindow("COMBOBOX", NULL,WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|BS_DEFSPLITBUTTON|CBS_DROPDOWN|CBS_HASSTRINGS|WS_VSCROLL,Launcher_XY[2*CBOX_RES+1][0],Launcher_XY[2*CBOX_RES+1][1],Launcher_XY[2*CBOX_RES][0],Launcher_XY[2*CBOX_RES][1],OPT_MENU, (HMENU)CBOX_RES, NULL, NULL);
for (int i = 0; i < find_resolution(0).total_screen; i++)
{
sprintf_s(char_dummy, "%ld x %ld", find_resolution(i).x,find_resolution(i).y);
SendMessage(CBOX_RES_HWND, CB_ADDSTRING, 0, (LPARAM) char_dummy);
}
if(get_ini(ini_fName).resolution_id > find_resolution(0).total_screen){
	set_ini(ini_fName,ini_variables[screen_resolution_id], std::to_string(0));
}
set_ini(ini_fName,ini_variables[screen_screen_x], std::to_string(find_resolution(get_ini(ini_fName).resolution_id).x));
set_ini(ini_fName,ini_variables[screen_screen_y], std::to_string(find_resolution(get_ini(ini_fName).resolution_id).y));
SendMessage(CBOX_RES_HWND, CB_SETCURSEL, get_ini(ini_fName).resolution_id, 0);
#pragma endregion

#pragma region "INIT CBOX_DUB_HWND"
CBOX_DUB_HWND = CreateWindow("COMBOBOX", NULL,WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|BS_DEFSPLITBUTTON|CBS_DROPDOWN|CBS_HASSTRINGS|WS_VSCROLL,Launcher_XY[2*CBOX_DUB+1][0],Launcher_XY[2*CBOX_DUB+1][1],Launcher_XY[2*CBOX_DUB][0],Launcher_XY[2*CBOX_DUB][1],OPT_MENU, (HMENU)CBOX_DUB, NULL, NULL);
for (int i = 0; i < sizeof(CBOX_DUB_ITEMS)/sizeof(*CBOX_DUB_ITEMS); i++)
{
strcpy_s(char_dummy, CBOX_DUB_ITEMS[i]);
SendMessage(CBOX_DUB_HWND, CB_ADDSTRING, 0, (LPARAM) char_dummy);
}
if(get_ini(ini_fName).dub_id > sizeof(CBOX_DUB_ITEMS)/sizeof(*CBOX_DUB_ITEMS)){
	set_ini(ini_fName,ini_variables[others_dubbing_id], std::to_string(0));
}
SendMessage(CBOX_DUB_HWND, CB_SETCURSEL, get_ini(ini_fName).dub_id, 0);
#pragma endregion

#pragma region "INIT CBOX_SUB_HWND"
CBOX_SUB_HWND = CreateWindow("COMBOBOX", NULL,WS_VISIBLE|WS_CHILD|CBS_DROPDOWNLIST|BS_DEFSPLITBUTTON|CBS_DROPDOWN|CBS_HASSTRINGS|WS_VSCROLL,Launcher_XY[2*CBOX_SUB+1][0],Launcher_XY[2*CBOX_SUB+1][1],Launcher_XY[2*CBOX_SUB][0],Launcher_XY[2*CBOX_SUB][1],OPT_MENU, (HMENU)CBOX_SUB, NULL, NULL);
for (int i = 0; i < sizeof(CBOX_SUB_ITEMS)/sizeof(*CBOX_SUB_ITEMS); i++)
{
strcpy_s(char_dummy, CBOX_SUB_ITEMS[i]);
SendMessage(CBOX_SUB_HWND, CB_ADDSTRING, 0, (LPARAM) char_dummy);
}
if(get_ini(ini_fName).sub_id > sizeof(CBOX_SUB_ITEMS)/sizeof(*CBOX_SUB_ITEMS)){
	set_ini(ini_fName,ini_variables[others_subtitle_id], std::to_string(0));
}
SendMessage(CBOX_SUB_HWND, CB_SETCURSEL, get_ini(ini_fName).sub_id, 0);
#pragma endregion

#pragma endregion

}catch(...){MessageBox(NULL,"K22_loadMenu: Menus Cant Created",NULL,MB_OK);PostQuitMessage(0);}}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	switch (message)
	{
	case WM_CREATE:
		DEBUGLOG(comm_count++ << L" WM_CREATE"<< "\n");
		K22_loadMenus(hWnd);
	    break;
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		#pragma region "CONTROLS MAIN_MENU"
		if(wmId == BTN_RUN && wmEvent == BN_CLICKED){
			DEBUGLOG(comm_count++ << L" BTN_RUN " << wmEvent << "\n");
			K22_StartGame();
		}
		if(wmId == BTN_WEB && wmEvent == BN_CLICKED){
			DEBUGLOG(comm_count++ << L" BTN_WEB " << wmEvent << "\n");
		}
		if(wmId == BTN_OPT && wmEvent == BN_CLICKED){
			DEBUGLOG(comm_count++ << L" BTN_OPT " << wmEvent << "\n");
			ShowWindow(MAIN_MENU,0);
			ShowWindow(OPT_MENU,1);
		}
		if(wmId == BTN_EXIT && wmEvent == BN_CLICKED){
			DEBUGLOG(comm_count++ << L" BTN_EXIT " << wmEvent << "\n");
		}
        #pragma endregion

		#pragma region "CONTROLS OPT_MENU"
		if(wmId == CBOX_WMODE && wmEvent == CBN_SELCHANGE)
        {
			DEBUGLOG(comm_count++ << L" CBOX_WMODE " << wmEvent << "\n");
            int ItemIndex = SendMessage(CBOX_WMODE_HWND, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
            TCHAR  ListItem[256];
            (TCHAR) SendMessage(CBOX_WMODE_HWND, (UINT) CB_GETLBTEXT, (WPARAM) ItemIndex, (LPARAM) ListItem);
			set_ini(ini_fName,ini_variables[screen_wmode_id], std::to_string(ItemIndex));
			DEBUGLOG(comm_count++ << L" CBOX_WMODE: "<< ItemIndex << " " << ListItem << " " << wmEvent << "\n");
		}
		if(wmId == CBOX_RES && wmEvent == CBN_SELCHANGE)
        {
			DEBUGLOG(comm_count++ << L" CBOX_RES " << wmEvent << "\n");
            int ItemIndex = SendMessage(CBOX_RES_HWND, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
            TCHAR  ListItem[256];
            (TCHAR) SendMessage(CBOX_RES_HWND, (UINT) CB_GETLBTEXT, (WPARAM) ItemIndex, (LPARAM) ListItem);
			set_ini(ini_fName,ini_variables[screen_resolution_id], std::to_string(ItemIndex));
			set_ini(ini_fName,ini_variables[screen_screen_x], std::to_string(find_resolution(ItemIndex).x));
			set_ini(ini_fName,ini_variables[screen_screen_y], std::to_string(find_resolution(ItemIndex).y));
			DEBUGLOG(comm_count++ << L" CBOX_RES: "<< ItemIndex << " " << ListItem << " " << wmEvent << "\n");
		}
		if(wmId == CBOX_DUB && wmEvent == CBN_SELCHANGE)
        {
			DEBUGLOG(comm_count++ << L" CBOX_DUB " << wmEvent << "\n");
            int ItemIndex = SendMessage(CBOX_DUB_HWND, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
            TCHAR  ListItem[256];
            (TCHAR) SendMessage(CBOX_DUB_HWND, (UINT) CB_GETLBTEXT, (WPARAM) ItemIndex, (LPARAM) ListItem);
			set_ini(ini_fName,ini_variables[others_dubbing_id], std::to_string(ItemIndex));
			DEBUGLOG(comm_count++ << L" CBOX_DUB: "<< ItemIndex << " " << ListItem << " " << wmEvent << "\n");
		}
		if(wmId == CBOX_SUB && wmEvent == CBN_SELCHANGE)
        {
			DEBUGLOG(comm_count++ << L" CBOX_SUB " << wmEvent << "\n");
            int ItemIndex = SendMessage(CBOX_SUB_HWND, (UINT) CB_GETCURSEL, (WPARAM) 0, (LPARAM) 0);
            TCHAR  ListItem[256];
            (TCHAR) SendMessage(CBOX_SUB_HWND, (UINT) CB_GETLBTEXT, (WPARAM) ItemIndex, (LPARAM) ListItem);
			set_ini(ini_fName,ini_variables[others_subtitle_id], std::to_string(ItemIndex));
			DEBUGLOG(comm_count++ << L" CBOX_SUB: "<< ItemIndex << " " << ListItem << " " << wmEvent << "\n");
		}
		#pragma endregion

		break;
   case WM_CLOSE:
        DestroyWindow(hWnd);
        break;
   case WM_DESTROY:
        PostQuitMessage(0);
        break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}