#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest07", "west");
    add_exit(FOREST + "forest04", "northwest");
    add_exit(FOREST + "forest17", "southeast");
    add_exit(FOREST + "forest16", "south");
    add_exit(FOREST + "forest15", "southwest");
}
