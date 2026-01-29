#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest03", "west");
    add_exit(FOREST + "forest02", "northwest");
    add_exit(FOREST + "forest08", "southeast");
    add_exit(FOREST + "forest07", "south");
    add_exit(FOREST + "forest06", "southwest");
}
