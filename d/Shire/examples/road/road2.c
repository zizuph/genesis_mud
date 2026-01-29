#include "../local.h"

inherit ROAD_BASE;

void
create_road_room()
{
    set_short("A winding road in the Shire");

    add_exit(EXAMPLE_ROAD + "road1","north",0,2);
    add_exit(EXAMPLE_TOWN + "hobbit_inn", "east");
    add_exit(EXAMPLE_ROAD + "road3", "southeast",0,2);
}
