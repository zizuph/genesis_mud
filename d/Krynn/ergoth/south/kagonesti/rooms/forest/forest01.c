#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest00", "northeast");
    add_exit(FOREST + "forest02", "east");
    add_exit(FOREST + "forest03", "southeast");
}
