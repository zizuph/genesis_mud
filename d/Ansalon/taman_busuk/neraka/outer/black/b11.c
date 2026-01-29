#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 21 May 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
    set_neraka_hide(15);
	set_short("Dirt road in Black Quarter");
    set_extra_long("You are walking on a dirt road in the Black Quarter. " +
        "The road leads northwest and southeast. " +
        "A guard tower stands off to the north, keeping a solitary vigil. " +
        "There are wooden sidewalks along the roads " +
        "here, since the roads are often used for wagons and horses.");
    set_quarter(BLACK);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item(({"tower","guard tower"}),
        "The guard tower stands at the entrance to the Black Quarter. " +
        "There is no entrance from this direction.\n");

    add_exit(NOUTER+"black/b10","southeast");
    add_exit(NOUTER+"black/b12","northwest");
}
