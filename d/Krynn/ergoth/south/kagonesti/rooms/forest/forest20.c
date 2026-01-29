#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest10", "northwest");
    add_exit(FOREST + "forest25", "southeast");

    set_creek_dir("east");
}
