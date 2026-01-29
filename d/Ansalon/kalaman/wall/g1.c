#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit CITY_OUT;
object g1,g2,g3;

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

    if(!objectp(g3))
    {
	g3 = clone_object(KNPC + "militiaman");
	g3->arm_me();
	g3->move(TO);
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("Up on the battlements above the harbour gate");
    add_item_wall();
    add_item(({"east","harbour","harbour district"}),
      "@@east_wall");
    add_item(({"harbour gate","gate"}),
      "You are standing on the battlement overlooking the harbour gate " +
      "of Kalaman.\n");
    add_item(({"stone stairway","stairway"}),
      "A stone stairway leads down here.\n");

    add_exit(WALL + "e3","northwest",0);
    add_exit(WALL + "g2","southeast",0);
    add_exit(KROOM + "guard1","down",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand up on the battlements overlooking the harbour " +
    "gate of Kalaman. " +
    season_battlements() +
    "A stone stairway here leads down to the gate. " +
    east_desc();
}
