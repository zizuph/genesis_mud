#include "local.h"

inherit STD + "kagonesti_forest";

void create_kagonesti_forest()
{
    add_exit(FOREST + "forest20", "northwest");
    add_exit(FOREST + "forest26", "east");

    set_creek_dir("northeast");
}
