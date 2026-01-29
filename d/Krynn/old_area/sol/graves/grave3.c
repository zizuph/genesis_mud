/* The graveyard
 *
 * Nick & Dorak
 */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit GRAVE_STD;

object skdog1, skrat1, skbadger1;

reset_solace_room()
{
    set_alarm(1.0,0.0,"loada");
    set_alarm(2.0,0.0,"loadb");
    set_alarm(3.0,0.0,"loadc");
}

loada()
{
    if (skdog1)
	return;
    skdog1 = clone_object(MONSTER + "skeletal_dog");
    skdog1->move_living("xxx", TO);
}

loadb()
{
    if (skrat1)
	return;
    skrat1 = clone_object(MONSTER + "skeletal_rat");
    skrat1->move_living("xxx", TO);
}

loadc()
{
    if (skbadger1)
	return;
    skbadger1 = clone_object(MONSTER + "skeletal_badger");
    skbadger1->move_living("xxx", TO);
}


create_solace_room()
{
    set_short("Graveyard");
    set_long(BS(
	"You are in the north part of the graveyard in Solace. Graves are " +
	"all around you. You get nervous at the presence of all these " +
	"graves.", 70));

    ADD_GRAVES
    ADD_GRAVEYARD
    READ_GRAVE

    add_exit(TDIR + "grave2", "west", 0);
    add_exit(TDIR + "grave4", "east", 0);
}

query_grave_room() { return 3; }
