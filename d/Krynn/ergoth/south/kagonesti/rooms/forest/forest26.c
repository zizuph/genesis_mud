#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest25", "west");
    add_exit(FOREST + "forest27", "east");
    add_exit(FOREST + "forest31", "southeast");

    set_creek_dir("north");
}
