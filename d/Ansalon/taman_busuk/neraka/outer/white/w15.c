#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 14 Jun 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("market square in the White Quarter");
    set_extra_long("You are in the east end of a market square in the White " +
        "Quarter. Shops line the square, and other merchants wander around, " +
        "hawking their wares.");
    set_quarter(WHITE);

    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");
    
    add_exit(NOUTER+"white/w6","west");
}

