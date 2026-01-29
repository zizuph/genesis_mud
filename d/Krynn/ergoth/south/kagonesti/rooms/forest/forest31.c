#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest26", "northwest");
    add_exit(FOREST + "forest27", "north");
    add_exit(FOREST + "forest32", "east");
    add_exit(FOREST + "forest36", "southeast");
}
