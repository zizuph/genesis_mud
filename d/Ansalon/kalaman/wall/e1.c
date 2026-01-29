#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;

void
reset_kalaman_room()
{
    return;
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Up on the battlements near a lookout tower");
    add_item_wall();
    add_item(({"east","harbour","harbour district"}),
      "@@east_wall");

    add_item(({"lookout tower","tower","lookout towers","towers","entrance"}),
      "To your northeast is the entrance to a stone lookout tower, situated on " +
      "the wall surrounding Kalaman.\n");

    add_exit(WALL + "t1","northeast",0);
    add_exit(WALL + "n1","north",0);
    add_exit(WALL + "e2","south",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand high up on the battlements on the wall " +
    "surrounding Kalaman. " + season_battlements() +
    "To your northeast is the entrance to one of the walls lookout towers. " +
    east_desc();
}
