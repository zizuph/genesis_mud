#include "/d/Ansalon/common/defs.h"
#include "../local.h"

/* Ashlar */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("market square in Blue Quarter");
    set_extra_long("You are in the south part of the market square. The square " +
        "continues north of here. Shops line the square, and other " +
        "merchants wander around, hawking their wares. A sign above a " +
        "doorway to the south proclaims 'Goods traded'. To the southwest " +
        "is a warehouse.");
    set_quarter(BLUE);

    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");
    add_item("doorway","The doorway leads to a building to the south.\n");
    add_item("sign","It says: 'Goods traded'\n");

    add_exit(NOUTER+"blue/b12","north");
    add_exit(NOUTER+"blue/shop","south");
    add_exit(NOUTER+"blue/ware1","southwest");
    add_exit(NOUTER+"blue/b8","northwest");
}

int
goods()
{
	write("It seems the store is closed. Try later.\n");
    return 1;
}

int
warehouse()
{
	write("The door to the warehouse is locked right now.\n");
    return 1;
}

