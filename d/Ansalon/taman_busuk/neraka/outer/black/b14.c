#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 24 May 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Small dirt road in Black Quarter");
    set_extra_long("This is a small dirt road leading northeast and " +
        "southwest towards a junction. " +
        "There are wooden sidewalks along the " +
        "roads here, since the roads are often used for wagons and horses.");
    set_quarter(BLACK);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item("junction","It is a three-way junction, with roads leading " +
        "north, northeast and south.\n");

    add_exit(NOUTER+"black/b15","northeast");
    add_exit(NOUTER+"black/b3","southwest");
}

