#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest24", "north");
    add_exit(FOREST + "forest29", "east");
    add_exit(FOREST + "forest35", "southeast");

    set_lake_dir("west");
}
