#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest06", "west");
    add_exit(FOREST + "forest03", "northwest");
    add_exit(FOREST + "forest04", "north");
    add_exit(FOREST + "forest08", "east");
    add_exit(FOREST + "forest16", "southeast");
    add_exit(FOREST + "forest15", "south");
    add_exit(FOREST + "forest14", "southwest");
}
