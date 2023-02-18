#include "stdafx.h"
#include "kabus_function.h"

void K22_StartGame(){
	struct stat buf;
	std::string exe = (get_ini(ini_fName).is4GB == false) ? get_ini(ini_fName).starter : get_ini(ini_fName).starter_64;
	if(stat(exe.c_str(), &buf) == 0){
	std::string arg =  exe + " " + get_ini(ini_fName).arg;
	DEBUGLOG(comm_count++ << L" K22_StartGame: "<< exe.c_str() << " " << get_ini(ini_fName).arg.c_str() << "\n");
    exec((LPCTSTR)exe.c_str(),(LPSTR)arg.c_str());
	}else{MessageBox(NULL,"K22_StartGame: game cant finded",NULL,MB_OK);PostQuitMessage(0);}
}

ini_struct get_ini(std::string ini_file){
	INI::File ini;
	ini_struct variables;
	if (ini.Load(ini_file))
	{
		//starters
		variables.is4GB = ini.GetValue(ini_variables[starters_4GPatch],NULL).AsBool();
		variables.starter = ini.GetValue(ini_variables[starters_starter],NULL).AsString();
		variables.starter_64 = ini.GetValue(ini_variables[starters_starter64],NULL).AsString();
		//arguments
		variables.arg = ini.GetValue(ini_variables[arguments_arg],NULL).AsString();
		//screen
		variables.wmode_id = ini.GetValue(ini_variables[screen_wmode_id],NULL).AsInt();
		variables.resolution_id = ini.GetValue(ini_variables[screen_resolution_id],NULL).AsInt();
		variables.resolution_lock = ini.GetValue(ini_variables[screen_resolution_lock],NULL).AsBool();
		variables.screen_x = ini.GetValue(ini_variables[screen_screen_x],NULL).AsInt();
		variables.screen_y = ini.GetValue(ini_variables[screen_screen_y],NULL).AsInt();
		//others
		variables.sub_id = ini.GetValue(ini_variables[others_subtitle_id],NULL).AsInt();
		variables.dub_id = ini.GetValue(ini_variables[others_dubbing_id],NULL).AsInt();
	}else{MessageBox(NULL,"get_ini: ini cant loaded",NULL,MB_OK);exit(0);}
	return variables;
}

void reset_ini(std::string ini_file){
	INI::File ini;
	if (ini.Load(ini_file))
	{
		//starters
		ini.SetValue(ini_variables[starters_4GPatch],false);
		ini.SetValue(ini_variables[starters_starter],"K22.exe");
		ini.SetValue(ini_variables[starters_starter64],"K22_64.exe");
		//arguments
		ini.SetValue(ini_variables[arguments_arg],"test argument");
		//screen
		ini.SetValue(ini_variables[screen_wmode_id],0);
		ini.SetValue(ini_variables[screen_resolution_id],0);
		ini.SetValue(ini_variables[screen_resolution_lock],true);
		ini.SetValue(ini_variables[screen_screen_x],find_resolution(0).x);
		ini.SetValue(ini_variables[screen_screen_y],find_resolution(0).y);
		//others
		ini.SetValue(ini_variables[others_subtitle_id],0);
		ini.SetValue(ini_variables[others_dubbing_id],0);
		ini.Save(ini_file);
	}else{MessageBox(NULL,"reset_ini: ini cant loaded",NULL,MB_OK);PostQuitMessage(0);}
}

void set_ini(std::string ini_file,std::string ini_var, std::string ini_value){
	INI::File ini;
	if (ini.Load(ini_file))
	{
		ini.SetValue(ini_var,ini_value);
		ini.Save(ini_file);
	}else{MessageBox(NULL,"set_ini: ini cant loaded",NULL,MB_OK);PostQuitMessage(0);}
}

void exec(LPCTSTR lpApplicationName,LPSTR lpCommandLine)
{
   STARTUPINFO si;     
   PROCESS_INFORMATION pi;

   ZeroMemory( &si, sizeof(si) );
   si.cb = sizeof(si);
   ZeroMemory( &pi, sizeof(pi) );

   CreateProcess( lpApplicationName,lpCommandLine,NULL,NULL,FALSE,0,NULL,NULL,&si,&pi);

   CloseHandle( pi.hProcess );
   CloseHandle( pi.hThread );
}

LRESULT CALLBACK BUTTONBOYA(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    BITMAP          bitmap01;
    HDC             hdcMem01;
    HGDIOBJ         oldBitmap01;
	//DEBUGLOG(comm_count++ << L" BUTTONBOYA " << LOWORD(wParam) << " " << uMsg << " " << dwRefData << "\n");
    switch (uMsg)
    {
    case WM_LBUTTONDOWN:
    {
        HDC hdc = GetDC(hWnd);
        hdcMem01 = CreateCompatibleDC(hdc);
		oldBitmap01 = SelectObject(hdcMem01, LoadBitmap(GetModuleHandle(NULL),(LPCSTR)Launcher_Bitmap[2*dwRefData+1]));
        GetObject(LoadBitmap(GetModuleHandle(NULL),(LPCSTR)Launcher_Bitmap[2*dwRefData+1]), sizeof(bitmap01), &bitmap01);
        BitBlt(hdc, 0, 0, bitmap01.bmWidth, bitmap01.bmHeight, hdcMem01, 0, 0, SRCCOPY);
        SelectObject(hdcMem01, oldBitmap01);  
        DeleteDC(hdcMem01);
    }
    break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        hdcMem01 = CreateCompatibleDC(hdc);
        oldBitmap01 = SelectObject(hdcMem01, LoadBitmap(GetModuleHandle(NULL),(LPCSTR)Launcher_Bitmap[2*dwRefData]));
        GetObject(LoadBitmap(GetModuleHandle(NULL),(LPCSTR)Launcher_Bitmap[2*dwRefData]), sizeof(bitmap01), &bitmap01);
        BitBlt(hdc, 0, 0, bitmap01.bmWidth, bitmap01.bmHeight, hdcMem01, 0, 0, SRCCOPY);
        SelectObject(hdcMem01, oldBitmap01);
        DeleteDC(hdcMem01);
        EndPaint(hWnd, &ps);   
    }
    break;
    case WM_LBUTTONUP:
    {
        HDC hdc = GetDC(hWnd);
        hdcMem01 = CreateCompatibleDC(hdc);
        oldBitmap01 = SelectObject(hdcMem01, LoadBitmap(GetModuleHandle(NULL),(LPCSTR)Launcher_Bitmap[2*dwRefData]));
        GetObject(LoadBitmap(GetModuleHandle(NULL),(LPCSTR)Launcher_Bitmap[2*dwRefData]), sizeof(bitmap01), &bitmap01);
        BitBlt(hdc, 0, 0, bitmap01.bmWidth, bitmap01.bmHeight, hdcMem01, 0, 0, SRCCOPY);
        SelectObject(hdcMem01, oldBitmap01);
        DeleteDC(hdcMem01);
    }
    break;
    case WM_NCDESTROY:
        RemoveWindowSubclass(hWnd, &BUTTONBOYA, 1);
        break;
    }
    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK BOYA(HWND hWnd, UINT uMsg, WPARAM wParam,LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData)
{
    BITMAP          bitmap01;
    HDC             hdcMem01;
    HGDIOBJ         oldBitmap01;
	//DEBUGLOG(comm_count++ << L" BOYA " << LOWORD(wParam) << " " << uMsg << " " << dwRefData << "\n");
    switch (uMsg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        hdcMem01 = CreateCompatibleDC(hdc);
        oldBitmap01 = SelectObject(hdcMem01, LoadBitmap(GetModuleHandle(NULL),(LPCSTR)Launcher_Bitmap[2*dwRefData]));
        GetObject(LoadBitmap(GetModuleHandle(NULL),(LPCSTR)Launcher_Bitmap[2*dwRefData]), sizeof(bitmap01), &bitmap01);
        BitBlt(hdc, 0, 0, bitmap01.bmWidth, bitmap01.bmHeight, hdcMem01, 0, 0, SRCCOPY);
        SelectObject(hdcMem01, oldBitmap01);
        DeleteDC(hdcMem01);
        EndPaint(hWnd, &ps);
		break;
    }
    case WM_NCDESTROY:
        RemoveWindowSubclass(hWnd, &BOYA, 1);
        break;
    }
    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}