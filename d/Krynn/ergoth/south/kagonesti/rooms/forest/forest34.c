#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest35", "east");
    add_exit(FOREST + "forest40", "southeast");

    set_structure_here(HUTS + "hut07");
    set_lake_dir("west");
}
