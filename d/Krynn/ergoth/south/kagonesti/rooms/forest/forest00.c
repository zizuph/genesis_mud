#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest01", "southwest");

    set_structure_here(HUTS + "hut01");
}
