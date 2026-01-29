#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest16", "west");
    add_exit(FOREST + "forest08", "northwest");
    add_exit(FOREST + "forest18", "east");
    add_exit(FOREST + "forest24", "southeast");
    add_exit(FOREST + "forest23", "south");
}
