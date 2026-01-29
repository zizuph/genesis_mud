#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 11 Jun 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Dirt road in White Quarter");
    set_extra_long("You are walking on a dirt road in the White Quarter. " +
        "The road leads northeast and southwest. " +
        "A guard tower stands off to the east, keeping a solitary vigil. " +
        "There are wooden sidewalks along the roads " +
        "here, since the roads are often used for wagons and horses.");
    set_quarter(WHITE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item(({"tower","guard tower"}),
        "The guard tower stands at the entrance to the White Quarter. " +
        "There is no entrance from this direction.\n");

    add_exit(NOUTER+"white/w3","southwest");
    add_exit(NOUTER+"white/w1","northeast");
}

