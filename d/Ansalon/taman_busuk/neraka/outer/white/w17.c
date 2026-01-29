#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 14 Jun 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("market square in the White Quarter");
    set_extra_long("You are in the west end of a market square in the White " +
        "Quarter. Shops line the square, and other merchants wander around, " +
        "hawking their wares. A small dirt road leads west away from the market " +
        "square.");
    set_quarter(WHITE);

    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");
    add_item(({"dirt road","road","small dirt road"}),
        "The small dirt road leads west.\n");

    add_exit(NOUTER+"white/w6","east");
    add_exit(NOUTER+"white/w18","west");
}

