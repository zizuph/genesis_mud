#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest31", "northwest");
    add_exit(FOREST + "forest32", "north");
    add_exit(FOREST + "forest33", "northeast");
    add_exit(FOREST + "forest37", "east");
}
