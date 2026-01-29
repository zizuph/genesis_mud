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
    add_item(({"estuary","vingaard river","river",
	"ocean","turbidus ocean"}),
      "@@north_wall");
    add_item(({"tower","lookout tower","towers","lookout towers"}),
      "To your east is the entrance to a stone lookout tower, situated on " +
      "the wall surrounding Kalaman.\n");

    add_exit(WALL + "t1","east",0);
    add_exit(WALL + "e1","south",0);
    add_exit(WALL + "n2","northwest",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand high up on the battlements on the wall " +
    "surrounding Kalaman. " + season_battlements() +
    "To your east is the entrance to one of the walls lookout towers. " +
    north_desc();
}
