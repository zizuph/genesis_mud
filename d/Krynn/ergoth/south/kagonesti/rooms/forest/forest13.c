#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest12", "west");
    add_exit(FOREST + "forest05", "north");
    add_exit(FOREST + "forest22", "southeast");
    add_exit(FOREST + "forest21", "south");
}
