#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest01", "west");
    add_exit(FOREST + "forest04", "southeast");
    add_exit(FOREST + "forest03", "south");
}
