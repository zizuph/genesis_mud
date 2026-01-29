#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 14 Jun 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("dirt road in White Quarter, near guard tower");
    set_extra_long("You are walking on a dirt road in the White Quarter. " +
        "Southwest of here is a guard tower, marking the border to the " +
        "Green Quarter. The road leads south, and north to the heart " +
        "of the White Quarter. There are wooden sidewalks " +
        "along the roads here, since the roads are often used for wagons " +
        "and horses.");
    add_item(({"tower","guard tower"}),"The stone tower marks the border " +
        "to the Green Quarter. There is no entrance from this direction.\n");
    set_quarter(WHITE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

    add_exit(NOUTER+"white/w13","north");
    add_exit(NOUTER+"green/g27","south");
}


