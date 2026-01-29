#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest23", "west");
    add_exit(FOREST + "forest17", "northwest");
    add_exit(FOREST + "forest28", "south");

    set_lake_dir("southwest");
}
