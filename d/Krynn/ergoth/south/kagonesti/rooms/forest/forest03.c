#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest01", "northwest");
    add_exit(FOREST + "forest02", "north");
    add_exit(FOREST + "forest04", "east");
    add_exit(FOREST + "forest07", "southeast");

    set_structure_here(HUTS + "hut02");
}
