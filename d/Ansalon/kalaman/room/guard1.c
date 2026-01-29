#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;
object guard1, guard2, guard3;

void
reset_kalaman_room()
{
    if(!objectp(guard1))
    {
	guard1 = clone_object(KNPC + "guard");
	guard1->arm_me();
	guard1->move(TO);
    }
    if(!objectp(guard2))
    {
	guard2 = clone_object(KNPC + "guard");
	guard2->arm_me();
	guard2->move(TO);
    }
    if(!objectp(guard3))
    {
	guard3 = clone_object(KNPC + "guard");
	guard3->arm_me();
	guard3->move(TO);
    }
}

create_kalaman_room()
{
    set_short("Guard room for the harbour gates of Kalaman");
    set_long("@@long_descr");

    add_item(({"barracks","guard rooms","guard room","room"}),
      "@@long_descr");
    add_item(({"stone stairway","stairway","stairs"}),
      BSN("A stone stairway rises from the guard room up through a hatch in the roof, " +
	"you would gather to the city wall's battlements."));
    add_item(({"walls","wall","city walls"}),
      BSN("Being inside a guard room, it is not possible to look upon the city walls."));

    add_exit(KROOM + "gate","southeast",0);
    add_exit(WALL + "g1","up","@@no_go");
    reset_kalaman_room();
}

string
long_descr()
{
    string str;

    str = "You stand within one of the guard rooms that act as barracks for those " +
    "soldiers charged to guard the harbour gates of Kalaman. Here a stone stairway " +
    "rises up to the wall's battlements, and an open exit leads out to the " +
    "harbour gates.";

    return BSN(str);
}


int
no_go()
{
    if((objectp(guard1) && E(guard1) == TO) || 
       (objectp(guard2) && E(guard2) == TO) || 
       (objectp(guard3) && E(guard3) == TO))
    {
	write("A well-armoured guard stops you from going up.\n");
	say("A well-armoured guard stops " +QTNAME(TP)+ " from going up.\n");
	return 1;
    }
    write("You climb the stone stairway to the battlements above.\n");
    return 0;
}
