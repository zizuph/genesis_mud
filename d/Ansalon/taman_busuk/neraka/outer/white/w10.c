#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 14 Jun 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Dirt road in White Quarter");
    set_extra_long("You are walking on a dirt road in the White Quarter. " +
        "The road leads southwest and northeast, where it meets a market square. " +
        "There are wooden sidewalks along the roads " +
        "here, since the roads are often used for wagons and horses.");
    set_quarter(WHITE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");

    add_exit(NOUTER+"white/w11","southwest");
    add_exit(NOUTER+"white/w6","northeast");

}

