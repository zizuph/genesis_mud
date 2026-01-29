#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest18", "southwest");
    add_exit(FOREST + "forest19", "south");

    set_structure_here(HUTS + "hut10");
}
