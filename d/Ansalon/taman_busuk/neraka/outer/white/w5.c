#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 11 Jun 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Dirt road in White Quarter");
    set_extra_long("You are walking on a dirt road in the White Quarter. " +
        "The road leads northeast and south towards a market square. " +
        "To the north stands a large warehouse. " +
        "There are wooden sidewalks along the roads " +
        "here, since the roads are often used for wagons and horses.");
    set_quarter(WHITE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");
    add_item(({"warehouse","large warehouse"}),
        "The warehouse is made of wood and is quite large.\n");

    add_exit(NOUTER+"white/w4","northeast");
    add_exit(NOUTER+"white/w6","south");
    add_exit(NOUTER+"white/ware1","north");
}

