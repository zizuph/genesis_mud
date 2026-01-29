#include "../local.h"

inherit ROAD_BASE;

void
create_road_room()
{
    set_short("A winding road in the Shire");

    add_exit(EXAMPLE_ROAD + "road4","north",0,2);
}
