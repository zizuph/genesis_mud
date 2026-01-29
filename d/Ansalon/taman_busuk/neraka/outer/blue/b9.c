#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Dirt road in Blue Quarter");
    set_extra_long("You are walking on a dirt road in the Blue Quarter. " +
        "The road leads south towards the market square, and north towards " +
        "the Black Quarter. There are wooden sidewalks along the roads " +
        "here, since the roads are often used for wagons and horses. " +
        "A small alley leads southeast between two buildings, and a " +
        "doorway leads northeast.");
    set_quarter(BLUE);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");
    add_item(({"alley", "small alley"}),"The alley seems to lead to " +
        "the market square.\n");
    add_item("doorway","The doorway leads into a building to the " +
        "northeast.\n");
    add_item("northeast building","You notice strange smells coming from " +
        "the building to the northeast.\n");

    add_exit(NOUTER+"blue/b10","north");
    add_exit(NOUTER+"blue/pm","northeast","@@pm_msg");
    add_exit(NOUTER+"blue/b12","southeast","@@msg");
    add_exit(NOUTER+"blue/b8","south");
}

int
msg()
{
	write("You walk down the alley and emerge in the market square.\n");
    return 0;
}

int
pm_msg()
{
	//write("You open the door and enter the building.\n");
    write("The shop seems to be closed. Perhaps you should try again " +
        "another time.\n");
    return 1;
}

