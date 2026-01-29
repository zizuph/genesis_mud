#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include ARND_MEET

/* Ashlar, 24 May 97 */

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
	set_short("Small dirt road in Black Quarter");
    set_extra_long("You are walking along a small dirt road in the Black " +
        "Quarter. The road leads east and southwest, while to the " +
        "northwest is the market square. " +
        "There are wooden sidewalks along the " +
        "roads here, since the roads are often used for wagons and horses.");
    set_quarter(BLACK);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");

    add_exit(NOUTER+"black/b18","east");
    add_exit(NOUTER+"black/b13","northwest");
    add_exit(NOUTER+"black/b14","southwest");
    add_exit(NOUTER+"black/yard","south");
    reset_room();
}

