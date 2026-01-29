#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest38", "west");
    add_exit(FOREST + "forest40", "east");
    add_exit(FOREST + "forest41", "south");

    set_lake_dir("northwest");
}
