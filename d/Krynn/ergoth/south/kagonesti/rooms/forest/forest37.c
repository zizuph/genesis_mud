#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest36", "west");
    add_exit(FOREST + "forest32", "northwest");
    add_exit(FOREST + "forest33", "north");
    add_exit(FOREST + "forest38", "east");
}
