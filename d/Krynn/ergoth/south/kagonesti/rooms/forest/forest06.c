#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest04", "northeast");
    add_exit(FOREST + "forest07", "east");
    add_exit(FOREST + "forest15", "southeast");
    add_exit(FOREST + "forest14", "south");

    set_structure_here(HUTS + "hut03");
}
