#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KALAMAN_IN;
object g1;

void
reset_kalaman_room()
{
    if(!objectp(g1))
    {
	g1 = clone_object(KNPC + "militiaman");
	g1->move(TO);
	g1->arm_me();
    }
}

create_kalaman_room()
{
    set_long("@@long_descr");
    set_short("sleeping quarters");

    add_item("bunks","Fairly simple bunks fill this room. " +
      "While they don't seem to be incredibly comfortable, you don't " +
      "think the militia really care after a long " +
      "day on the battlements.\n");

    add_exit(CITY + "b5","south",0);

    reset_kalaman_room();
}

string
long_descr()
{
    return "You stand in a room full of bunks, the sleeping " +
    "quarters of the local militia of Kalaman. To the " +
    "south " +
    "you can exit the sleeping quarters.\n";
}
