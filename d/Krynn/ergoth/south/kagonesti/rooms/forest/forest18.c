#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest17", "west");
    add_exit(FOREST + "forest09", "northeast");
    add_exit(FOREST + "forest19", "east");
    add_exit(FOREST + "forest23", "southwest");
}
