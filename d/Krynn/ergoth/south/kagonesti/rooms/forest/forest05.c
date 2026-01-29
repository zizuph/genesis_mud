#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest12", "southwest");
    add_exit(FOREST + "forest13", "south");

    set_structure_here(HUTS + "hut04");
}
