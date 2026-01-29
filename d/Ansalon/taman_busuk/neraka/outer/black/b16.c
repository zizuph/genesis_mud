#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 24 May 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Small dirt road in Black Quarter");
    set_extra_long("This is a small dirt road leading northeast towards " +
        "a large tent, and south to the market square.");
    set_quarter(BLACK);

    add_item_dirtroad();
    add_item_market("square");

    add_item(({"tent","large tent"}),
        "The large tent is off to the northeast, at the end of the dirt " +
        "road.\n");

    add_exit(NOUTER+"black/b17","northeast");
    add_exit(NOUTER+"black/b13","south");
}

