#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest14", "west");
    add_exit(FOREST + "forest06", "northwest");
    add_exit(FOREST + "forest07", "north");
    add_exit(FOREST + "forest08", "northeast");
    add_exit(FOREST + "forest16", "east");
    add_exit(FOREST + "forest22", "southwest");

    set_lake_dir("south");
}
