/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

object draco, human;

#include RND_MEET

reset_tantallon_room()
{
    if (draco)
        return;
    draco = RANDOM_MEET(DRACOS);/*clone_object(MON + "draconian");*/
    if (draco->query_prop(OBJ_I_COLORABLE))
    draco->set_color("red");
    draco->set_random_move(30);
    draco->move_living("xx", TO);

    if (!human)
      set_alarm(6.0,0.0,"load_human");
}

load_human()
{
    int i;

    human = clone_object(MON + "ne_hum_g");
    human->move_living("xxx", TO);

    if (random(3))
        human->set_random_move(random(100));

}

create_tantallon_room()
{
    set_short("Four way crossing");
    set_long(BS(
        "You are standing on a small road at a four way crossing. The road " +
    "itself goes north and south. All you see east is dirt. You could " +
    "also walk west in between some tents.", SL));

    add_item(({"tent", "tents", "some tents"}),
        "You can't make out much at this distance.\n");
    add_item("road",
        "It leads off north and south. It's made out of small stones.\n");
    add_item(({"stone", "stones"}), BS(
        "The stones are small and round but they stick to the ground so you " +
        "can't pick them up.", SL));

    add_exit(TDIR + "city24", "south",0);
    add_exit(TDIR + "city23", "east", 0);
    add_exit(TDIR + "city19", "north",0);
    add_exit(TDIR + "city21", "west", 0);

    set_alarm(1.0,0.0,"reset_room");
}

