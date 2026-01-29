#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest39", "west");
    add_exit(FOREST + "forest34", "northwest");
    add_exit(FOREST + "forest35", "north");
    add_exit(FOREST + "forest41", "southwest");
}
