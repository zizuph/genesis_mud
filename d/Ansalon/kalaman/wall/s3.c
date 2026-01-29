#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object g1;

void
reset_kalaman_room()
{
    if(!objectp(g1))
    {
	g1 = clone_object(KNPC + "sentry");
	g1->arm_me();
	g1->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Up on the battlements on the wall surrounding Kalaman");
    add_item_wall();
    add_item(({"hills","plains","plains of estwilde","estwilde"}),
      "@@south_wall");

    add_exit(WALL + "s2","northeast",0);
    add_exit(WALL + "s4","southwest",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand high up on the battlements on the wall " +
    "surrounding Kalaman. " + season_battlements() +
    south_desc();
}
