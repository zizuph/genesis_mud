#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest06", "north");
    add_exit(FOREST + "forest07", "northeast");
    add_exit(FOREST + "forest15", "east");
    add_exit(FOREST + "forest22", "south");
    add_exit(FOREST + "forest21", "southwest");
}
