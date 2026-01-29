#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest12", "northwest");
    add_exit(FOREST + "forest13", "north");
    add_exit(FOREST + "forest14", "northeast");
    add_exit(FOREST + "forest22", "east");

    set_creek_dir("south");
}
