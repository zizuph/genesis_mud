#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest15", "west");
    add_exit(FOREST + "forest07", "northwest");
    add_exit(FOREST + "forest08", "north");
    add_exit(FOREST + "forest17", "east");
    add_exit(FOREST + "forest23", "southeast");

    set_lake_dir("south");
}
