#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest32", "west");
    add_exit(FOREST + "forest38", "southeast");
    add_exit(FOREST + "forest37", "south");
    add_exit(FOREST + "forest36", "southwest");

    set_structure_here(HUTS + "hut06");

    set_lake_dir("northeast");
}
