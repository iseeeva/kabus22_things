///////////////////////////////////////////////////////////////////////

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h.>
#include <string>

#define DLL_USE
#include "acknex_lib/adll.h"
#include "kabus_lib/kabus_fun.h"
#include "kabus_lib/resolution/init.h"

///////////////////////////////////////////////////////////////////////

BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved )
{
// make sure the library is linked
	engine_bind();
    return TRUE;
}

///////////////////////////////////////////////////////////////////////

KABUS_API void print_test(STRING* test_str)
{
	std::string test_text = ("[Bu hata test için döndürüldü\n]" + (std::string)_CHR(test_str));
	error(_strdup(test_text.c_str()));
}

KABUS_API void print_screen_test()
{
	screen screen_all = screen_resolutions_find_all();
	for (int i = 0; i < screen_all.total_screen; i++)
    {
		std::string screen_text = (std::to_string(screen_all.x[i]) + "x" + std::to_string(screen_all.y[i]));
		error(_strdup(screen_text.c_str()));
	}
}

KABUS_API char* replace_char(STRING* input_chr)
{
	//printf(_CHR(input_chr)); //debug stuff
	return _strdup(parse_escape(_CHR(input_chr)).c_str());
}

///////////////////////////////////////////////////////////////////////