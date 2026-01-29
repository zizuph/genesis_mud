#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest21", "west");
    add_exit(FOREST + "forest13", "northwest");
    add_exit(FOREST + "forest14", "north");
    add_exit(FOREST + "forest15", "northeast");

    set_lake_dir("southeast");
}
