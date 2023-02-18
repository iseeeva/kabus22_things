#pragma once
#include "./lib/default/resource.h"
#include "./lib/resolution/engine_resolutions.h"
#include "./lib/kabus_fun/kabus_function.h"
#include <iostream>
#include <sstream>
#include <commctrl.h>

#define MAX_LOADSTRING 100

// Global Variables by Default:
static HINSTANCE hInst;								// current instance
static TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
static TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);