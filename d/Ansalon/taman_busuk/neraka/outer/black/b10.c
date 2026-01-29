#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 21 May 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Dirt road in Black Quarter");
    set_extra_long("You are walking on a dirt road in the Black Quarter. " +
        "The road leads northwest and southeast. " +
        "There are wooden sidewalks along the roads " +
        "here, since the roads are often used for wagons and horses.");
    set_quarter(BLACK);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

    add_exit(NOUTER+"black/b9","southeast");
    add_exit(NOUTER+"black/b11","northwest");
}

