#pragma once
#include "../default/resource.h"
#include "../ini.hpp"
#include "../../kabus_launcher.h"
#include "../resolution/engine_resolutions.h"
#include <sstream>
#include <sys/stat.h>
#include <commctrl.h>

#ifndef _KABUS_FUN_H_
#define _KABUS_FUN_H_

// Launcher Variables:
#define DEBUGLOG(msg) { std::wstringstream ss; ss << msg; OutputDebugStringW(ss.str().c_str());}
#define SSTR(msg) { std::wstringstream ss; ss << msg; return ss.str().c_str();}

static char char_dummy [100] = "";
static int comm_count = 0;	//dbg
static RECT screen_pos;

#pragma region "Launcher Stuff"

#pragma region "Menus Items"
static 
	HWND TEST,
    MAIN_MENU,	    //(HMENU)MAIN_FORM	//**MENU ENTRY
    BTN_RUN_HWND,	//(HMENU)BTN_RUN
    BTN_WEB_HWND,	//(HMENU)BTN_WEB
    BTN_OPT_HWND,	//(HMENU)BTN_OPT
    BTN_EXT_HWND,	//(HMENU)BTN_EXIT
    OPT_MENU,	    //(HMENU)OPT_FORM	//**MENU ENTRY
    CBOX_WMODE_HWND,//(HMENU)CBOX_WMODE
	CBOX_RES_HWND,  //(HMENU)CBOX_RES
	CBOX_DUB_HWND,  //(HMENU)CBOX_DUB
	CBOX_SUB_HWND;  //(HMENU)CBOX_SUB

static enum //Launcher Enums
{
	MAIN_FORM,	//**MENU ENTRY
	BTN_RUN,
	BTN_WEB,
	BTN_OPT,
	BTN_EXIT,
	OPT_FORM,	//**MENU ENTRY
	CBOX_WMODE,
	CBOX_RES,
	CBOX_DUB,
	CBOX_SUB
};

static int Launcher_XY[][2] = {	// Launcher Cordinates/Weights

	//W   H
	//X   Y
	{206,228},	//MAIN_MENU //**MENU ENTRY
	{93,200},

	{76,34},	//KEN_RUN_ON/OFF
	{65,25},	 //{158,224}

	{177,35},	//KEN_WEBSITE_ON/OFF
	{15,70},	 //{107,270}

	{177,35},	//KEN_OPTIONS_ON/OFF
	{15,115},	 //{107,315}

	{76,34},	//KEN_EXIT_ON/OFF
	{65,160},	 //{158,360}

	{206,228},	//OPT_MENU //**MENU ENTRY
	{93,200},

	{162,144},   //CBOX_WMODE
	{22,29},     //{115,229}

	{162,144},   //CBOX_RES
	{22,67},     //{115,229}

	{162,144},   //CBOX_DUB
	{22,105},    //{115,229}

	{162,144},   //CBOX_SUB
	{22,143}     //{115,229}

};

static int Launcher_Bitmap[] = {	// Launcher Bitmaps
	K22_MAINMENU,	 //Ana Menü 0 //**MENU ENTRY
	NULL,
	K22_OPTMENU,	 //Ayarlar Menü 1 //**MENU ENTRY
	NULL,
	KEN_RUN_ON,	     //K22_MAINMENU EN 2
	KEN_RUN_OFF,	 //K22_MAINMENU EN
	KEN_WEBSITE_ON,	 //K22_MAINMENU EN 3
	KEN_WEBSITE_OFF, //K22_MAINMENU EN
	KEN_OPTIONS_ON,	 //K22_MAINMENU EN 4
	KEN_OPTIONS_OFF, //K22_MAINMENU EN
	KEN_EXIT_ON,	 //K22_MAINMENU EN 5
	KEN_EXIT_OFF	 //K22_MAINMENU EN
};
#pragma endregion

#pragma region "OPT_MENU CBOX_ITEMS"
static
	char* CBOX_WMODE_ITEMS[] = {"Borderless Fullscreen","Fullscreen","Windowed"};
static
	char* CBOX_DUB_ITEMS[] = {"Turkish","English"};
static
	char* CBOX_SUB_ITEMS[] = {"Turkish","German","English"};
#pragma endregion

#pragma endregion

#pragma region "INI Stuff"
static std::string ini_fName = "kabus_launcher.ini";
static enum //ini_variables enums
{
	//starters
	starters_4GPatch,
	starters_starter,
	starters_starter64,
	//arguments
	arguments_arg,
	//screen
	screen_wmode_id,
	screen_resolution_id,
	screen_resolution_lock,
	screen_screen_x,
	screen_screen_y,
	//others
	others_subtitle_id,
	others_dubbing_id
};

static std::string ini_variables[] =
	{
		//starters
		"starters:4GB_Patch",         //starters_4GPatch
		"starters:starter",           //starters_starter
		"starters:starter_64",        //starters_starter64
		//arguments
		"arguments:arg",              //arguments_arg
		//screen
		"screen:wmode_id",            //screen_wmode_id
		"screen:resolution_id",       //screen_resolution_id
		"screen:resolution_lock",     //screen_resolution_lock
		"screen:screen_x",            //screen_screen_x
		"screen:screen_y",            //screen_screen_y
		//others
		"others:subtitle_id",         //others_subtitle_id
		"others:dubbing_id"           //others_dubbing_id
	};

struct ini_struct
{
	//starters
	bool is4GB;
	std::string starter;
	std::string starter_64;
	//arguments
	std::string arg;
	//screen
	int wmode_id;
	int resolution_id;
	bool resolution_lock;
	int screen_x;
	int screen_y;
	//others
	int dub_id;
	int sub_id;
};
#pragma endregion

// Launcher Functions:
LRESULT CALLBACK BOYA(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
LRESULT CALLBACK BUTTONBOYA(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
void K22_StartGame(); //start game
void exec(LPCTSTR lpApplicationName,LPSTR lpCommandLine); //process exec?
ini_struct get_ini(std::string ini_file); //load default ini variables from file (with struct)
void reset_ini(std::string ini_file); //reset default ini variables in file
void set_ini(std::string ini_file,std::string ini_var, std::string ini_value);
#endif