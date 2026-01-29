/* The graveyard
 *
 * Nick, Eiram, and Dorak
 */

#include "local.h"
#include "/d/Krynn/common/defs.h"
inherit GRAVE_STD;

object skdog2, skrabbit1, skcat1;

reset_solace_room()
{
    set_alarm(1.0,0.0,"loada");
    set_alarm(2.0,0.0,"loadb");
    set_alarm(3.0,0.0,"loadc");
}

loada()
{
    if (skdog2)
	return;
    skdog2 = clone_object(MONSTER + "skeletal_dog");
    skdog2->move_living("xxx", TO);
}

loadb()
{
    if (skrabbit1)
	return;
    skrabbit1 = clone_object(MONSTER + "skeletal_rabbit");
    skrabbit1->move_living("xxx", TO);
}

loadc()
{
    if (skcat1)
	return;
    skcat1 = clone_object(MONSTER + "skeletal_cat");
    skcat1->move_living("xxx", TO);
}

create_solace_room()
{
    set_short("Graveyard");
    set_long(BS(
        "You are in the eastern part of the graveyard in Solace. This " +
        "seems to be one of the least visited part of this graveyard. " +
        "Probably the grave keeper has forgotten about this place." +
        "", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_exit(TDIR + "grave4", "north", 0);
    add_exit(TDIR + "grave14", "south", 0);
    set_alarm(10.0,0.0,"batsay");

    reset_room();

}

query_grave_room() { return 9; }

void
batsay()
{
    tell_room(TO, "A bat flapped its wings as it passed over your head.\n");
}
