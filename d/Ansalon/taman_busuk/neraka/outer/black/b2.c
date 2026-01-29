#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET

/* Ashlar, 19 May 97 */

inherit OUTER_OUT;

object d1;

void
reset_neraka_room()
{
    if (!objectp(d1))
        d1 = clone_npc(GET_RANDOM_NAME(NT_OUTER),"black");
}

void
create_neraka_room()
{
	set_short("Dirt road in Black Quarter");
    set_extra_long("You are walking on a dirt road in the Black Quarter. " +
        "The road leads south towards the Blue Quarter, and north " +
        "towards the heart of the Black Quarter. There are wooden sidewalks " +
        "along the roads here, since the roads are often used for wagons " +
        "and horses.");
    set_quarter(BLACK);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

    add_exit(NOUTER+"black/b3","north");
    add_exit(NOUTER+"black/b1","south");

    reset_room();
}

