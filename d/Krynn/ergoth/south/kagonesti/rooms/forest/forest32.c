#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest31", "west");
    add_exit(FOREST + "forest27", "northwest");
    add_exit(FOREST + "forest33", "east");
    add_exit(FOREST + "forest37", "southeast");
    add_exit(FOREST + "forest36", "south");

    set_lake_dir("northeast");
}
