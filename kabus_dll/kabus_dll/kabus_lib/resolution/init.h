// find all available resolutions
struct screen screen_resolutions_find_all();

struct screen
{
  int total_screen;
  int current_screen;
  int x[256];
  int y[256];
};