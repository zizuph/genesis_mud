#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object g1,g2;

void
reset_kalaman_room()
{
    if(!objectp(g1))
    {
	g1 = clone_object(KNPC + "sentry");
	g1->arm_me();
	g1->move(TO);
    }

    if(!objectp(g2))
    {
	g2 = clone_object(KNPC + "sentry");
	g2->arm_me();
	g2->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Up on the battlements near a lookout tower");
    add_item_wall();
    add_item(({"east","harbour","harbour district"}),
      "@@east_wall");
    add_item(({"lookout tower","tower","lookout towers","towers"}),
      "To your east is the entrance to a stone lookout tower, " +
      "situated on the wall surrounding Kalaman.\n");

    add_exit(WALL + "e4","west",0);
    add_exit(WALL + "t2","east",0);
    add_exit(WALL + "s1","southeast",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand high up on the battlements on the wall " +
    "surrounding Kalaman. " + season_battlements() +
    "To your east is the entrance to one of the walls " +
    "lookout towers. " +
    east_desc();
}
