#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest37", "west");
    add_exit(FOREST + "forest33", "northwest");
    add_exit(FOREST + "forest39", "east");
    add_exit(FOREST + "forest41", "southeast");

    set_lake_dir("north");
}
