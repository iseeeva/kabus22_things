#include "../kabus_fun/kabus_function.h"
#include <sstream>

#ifndef _ENGINE_RESOLUTIONS_H_
#define _ENGINE_RESOLUTIONS_H_

// resolution list indexes
#define RESOLUTION_WIDTH 0
#define RESOLUTION_HEIGHT 1

// display mode
#define MAX_DISPLAY_MODES 3
#define DISPLAY_WINDOWED 0
#define DISPLAY_BORDERLESS 1
#define DISPLAY_FULLSCREEN 2

// define smallest resolution to clip unnecessary ones
#define RESOLUTION_MAX_X 1920
#define RESOLUTION_MAX_Y 1200

#define RESOLUTION_MIN_X 1280
#define RESOLUTION_MIN_Y 720

// sort list of resolutions in ascending order
void engine_sort_resolutions_ascending();

// check if given resolution was already added into the list or not
int is_engine_resolution_added(int width, int height);

// add given resolution into the list
void engine_add_resolution_to_list(int width, int height);

struct screen
{
  int total_screen;
  int x;
  int y;
};
// find all available resolutions
screen find_resolution(int res_id);

#endif