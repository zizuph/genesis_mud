#pragma strict_types

#include "defs.h"
inherit TBASE;

public void
tunnel_room(void)
{
    set_short("circular landing");
    set_long("A flat ledge circles around a wide opening descending "+
	"into a dark abyss. The ledge leads around to top of "+
	"circular stairs that descend around the sides of the "+
	"opening. A hot, dry wind rises from the depths and flows "+
	"out through an archway to the north.\n");

    add_item(({"arch","archway","north"}),
	"The archway is made from soft white alabaster, framing an "+
	"opening to the north that leads out onto a ledge.\n");
    add_item("ledge", "The ledge circles around the dark opening, "+
	"and leads to the beginning of a circular stairwell that "+
	"descends into the gloom.\n");
    add_item(({"stair","stairs","step","steps","stairwell"}),
	"The circular stairs run along the interior of the gaping "+
	"opening, fixed against the wall. The center of the "+
	"stairwell is open, with no bannister at the inner edge.\n");

    add_exit(ROOM + "overhang_steps", "north");
    add_exit("stair_top", "down");

    ANTIMAGIC;
}
