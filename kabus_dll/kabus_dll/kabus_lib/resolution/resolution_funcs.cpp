#include "lib/stdafx.h"
#include "resolution_funcs.h"
#include "init.h"

DEVMODE resolution_struct;
int resolution_available_list[2][99]; // list of all available resolutions for currently used PC
int total_resolutions = 0;            // total amount of resolutions available for currently used PC
int desktop_resolution_id = 0;        // id of the desktop resolution
// desktop resolution
int desktop_size_x = 0;
int desktop_size_y = 0;

// sort list of resolutions in ascending order
void engine_sort_resolutions_ascending()
{
    int i = 0, j = 0;

    for (i = 0; i < total_resolutions; ++i)
    {
        for (j = i + 1; j < total_resolutions; ++j)
        {
            if (resolution_available_list[RESOLUTION_WIDTH][i] > resolution_available_list[RESOLUTION_WIDTH][j])
            {
                int width = resolution_available_list[RESOLUTION_WIDTH][i];
                int height = resolution_available_list[RESOLUTION_HEIGHT][i];

                resolution_available_list[RESOLUTION_WIDTH][i] = resolution_available_list[RESOLUTION_WIDTH][j];
                resolution_available_list[RESOLUTION_HEIGHT][i] = resolution_available_list[RESOLUTION_HEIGHT][j];

                resolution_available_list[RESOLUTION_WIDTH][j] = width;
                resolution_available_list[RESOLUTION_HEIGHT][j] = height;
            }
        }
    }
}

// check if given resolution was already added into the list or not
int is_engine_resolution_added(int width, int height)
{
    int i = 0;
    for (i = 0; i < total_resolutions; i++)
    {
        if (resolution_available_list[RESOLUTION_WIDTH][i] == width && resolution_available_list[RESOLUTION_HEIGHT][i] == height)
        {
            return true;
        }
    }

    return false;
}

// add given resolution into the list
void engine_add_resolution_to_list(int width, int height)
{
    resolution_available_list[RESOLUTION_WIDTH][total_resolutions] = width;
    resolution_available_list[RESOLUTION_HEIGHT][total_resolutions] = height;
    total_resolutions++;
}

// find all available resolutions
struct screen screen_resolutions_find_all()
{
    struct screen resolution;
    int i = 0;
    resolution_struct.dmSize = sizeof(DEVMODE);
    for (i = 1; EnumDisplaySettings(NULL, i, &resolution_struct) != 0; ++i)
    {
        int width = resolution_struct.dmPelsWidth;
        int height = resolution_struct.dmPelsHeight;
		
		if((width < RESOLUTION_MIN_X || height < RESOLUTION_MIN_Y) || ((width > RESOLUTION_MAX_X || height > RESOLUTION_MAX_Y)))
		{
			continue;
		}

        if (is_engine_resolution_added(width, height) == 0)
        {
            engine_add_resolution_to_list(width, height);
        }
    }

    engine_sort_resolutions_ascending();

    // find id of the desktop resolution
    for (i = 0; i < total_resolutions; i++)
    {
        int width = resolution_available_list[RESOLUTION_WIDTH][i];
        int height = resolution_available_list[RESOLUTION_HEIGHT][i];
        if (desktop_size_x == width && desktop_size_y == height)
        {
            desktop_resolution_id = i;
        }
    }

	resolution.total_screen = total_resolutions;
	resolution.current_screen = desktop_resolution_id;
	for (int i = 0; i < total_resolutions; i++)
    {
		resolution.x[i] = resolution_available_list[RESOLUTION_WIDTH][i];
		resolution.y[i] = resolution_available_list[RESOLUTION_HEIGHT][i];
	}

	return resolution;
}