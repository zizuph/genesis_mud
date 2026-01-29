#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest26", "west");
    add_exit(FOREST + "forest32", "southeast");
    add_exit(FOREST + "forest31", "south");

    set_structure_here(HUTS + "hut05");

    set_lake_dir("east");
}
