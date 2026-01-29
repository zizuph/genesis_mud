#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest34", "west");
    add_exit(FOREST + "forest28", "northwest");
    add_exit(FOREST + "forest29", "north");
    add_exit(FOREST + "forest30", "northeast");
    add_exit(FOREST + "forest40", "south");
}
