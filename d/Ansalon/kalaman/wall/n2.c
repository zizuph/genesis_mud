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
    set_short("Up on the battlements on the wall surrounding Kalaman");
    add_item_wall();
    add_item(({"estuary","vingaard river","river",
	"ocean","turbidus ocean"}),
      "@@north_wall");

    add_exit(WALL + "n1","southeast",0);
    add_exit(WALL + "n3","west",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand high up on the battlements on the wall " +
    "surrounding Kalaman. " + season_battlements() +
    north_desc();
}
