#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Dirt road in Blue Quarter");
    set_extra_long("You are walking on a dirt road in the Blue Quarter. " +
        "The road leads southwest towards the Red Quarter, and northeast " +
        "towards the heart of the Blue Quarter. There are wooden sidewalks " +
        "along the roads here, since the roads are often used for wagons " +
        "and horses.");
    set_quarter(BLUE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

    add_exit(NOUTER+"blue/b3","northeast");
    add_exit(NOUTER+"blue/b1","southwest");
}

