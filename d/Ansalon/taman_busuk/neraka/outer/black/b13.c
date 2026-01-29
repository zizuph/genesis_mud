#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 24 May 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("market square in Black Quarter");
    set_extra_long("You are in the middle of the market square in the Black " +
        "Quarter. Shops line the square, and other merchants wander around, " +
        "hawking their wares.");
    set_quarter(BLACK);

    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");

    add_exit(NOUTER+"black/b16","north");
    add_exit(NOUTER+"black/shop","northeast");
    add_exit(NOUTER+"black/b15","southeast");
    add_exit(NOUTER+"black/b8","west");
    add_exit(NOUTER+"black/b9","northwest");
}

