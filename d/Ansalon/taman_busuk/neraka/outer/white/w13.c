#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET

/* Ashlar, 14 Jun 97 */

inherit OUTER_OUT;

object d;

void
reset_neraka_room()
{
    if (!objectp(d))
    	d = clone_npc(GET_RANDOM_NAME(NT_OUTER),"white");
}

void
create_neraka_room()
{
	set_short("dirt road in White Quarter");
    set_extra_long("You are walking on a dirt road in the White Quarter. " +
        "The road leads south towards the Green Quarter, and northwest " +
        "towards the heart of the White Quarter. There are wooden sidewalks " +
        "along the roads here, since the roads are often used for wagons " +
        "and horses.");
    set_quarter(WHITE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

    add_exit(NOUTER+"white/w12","northwest");
    add_exit(NOUTER+"white/w14","south");

    reset_room();
}

