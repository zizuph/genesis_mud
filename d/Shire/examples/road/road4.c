#include "../local.h"

inherit ROAD_BASE;

void
create_road_room()
{
    set_short("A winding road in the Shire");

    add_exit(EXAMPLE_ROAD + "road3","north",0,2);
    add_exit(EXAMPLE_ROAD + "road5","south",0,2);
    add_exit(EXAMPLE_TOWN + "hobbit_house", "west");
}
