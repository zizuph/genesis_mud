#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar, 19 May 97 */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Dirt road in Black Quarter, near guard tower");
    set_extra_long("You are walking on a dirt road in the Black Quarter. " +
        "East of here is a guard tower, marking the border to the " +
        "Blue Quarter. The road leads southeast, and north to the heart " +
        "of the Black Quarter. There are wooden sidewalks " +
        "along the roads here, since the roads are often used for wagons " +
        "and horses.");
    set_quarter(BLACK);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    
    add_item(({"tower","guard tower"}),"The stone tower marks the border " +
        "to the Blue Quarter. There is no entrance from this direction.\n");

    add_exit(NOUTER+"black/b2","north");
    add_exit(NOUTER+"blue/b11","southeast");
}

