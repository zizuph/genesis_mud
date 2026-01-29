#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET

/* Ashlar */

inherit OUTER_OUT;

object d1;

void
reset_neraka_room()
{
    if (!objectp(d1))
        d1 = clone_npc(GET_RANDOM_NAME(NT_OUTER),"blue");
}

void
create_neraka_room()
{
	set_short("Dirt road in Blue Quarter");
    set_extra_long("You are walking on a dirt road in the Blue Quarter. " +
        "The road leads southwest towards the Red Quarter, and north " +
        "towards an intersection. There are wooden sidewalks along the " +
        "roads here, since the roads are often used for wagons and horses.");
    set_quarter(BLUE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item("intersection","The intersection is further north, where " +
        "this road meets another going east and west.\n");

    add_exit(NOUTER+"blue/b4","north");
    add_exit(NOUTER+"blue/b2","southwest");
    
    reset_room();
}

