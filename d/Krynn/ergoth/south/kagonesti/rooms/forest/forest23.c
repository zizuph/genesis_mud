#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest16", "northwest");
    add_exit(FOREST + "forest17", "north");
    add_exit(FOREST + "forest18", "northeast");
    add_exit(FOREST + "forest24", "east");

    set_structure_here(HUTS + "hut09");
    set_lake_dir("southwest");
}
