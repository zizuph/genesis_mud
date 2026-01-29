#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Dirt road in Blue Quarter, near guard tower");
    set_extra_long("You are walking on a dirt road in the Blue Quarter. " +
        "Southwest of here is a guard tower, marking the border to the " +
        "Red Quarter. The road leads south, and northeast to the heart " +
        "of the Blue Quarter. There are wooden sidewalks " +
        "along the roads here, since the roads are often used for wagons " +
        "and horses.");
    set_quarter(BLUE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item(({"tower","guard tower"}),"The stone tower marks the border " +
        "to the Red Quarter. There is no entrance from this direction.\n");

    add_exit(NOUTER+"blue/b2","northeast");
    add_exit(NOUTER+"red/r23","south");
}

int
msg()
{
    write("A guard steps up and denies you access to the Red Quarter.\n");
    return 1;
}
