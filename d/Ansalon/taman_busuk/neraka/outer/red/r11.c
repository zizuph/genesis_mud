#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Market square in the Red Quarter");
    set_extra_long("You are at the western end of the market square. " +
		"Apart from the merchants who wander the marketplace, various shops " +
		"and establishments line the square. West of here you spot an " +
		"exotic-looking shop, while to the southwest lies a smithy. A road " +
		"leads away from the square to the south.");
	set_quarter(RED);
    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");
	add_item("smithy", "That would be the place to go, should you need the " +
		"services of such an establishment.\n");
	add_item(({"shop", "exotic-looking shop"}), "This establishment deals " +
		"in various exotic animals.\n");
	add_item("road", "The road leads south of here, away from the square.\n");
	add_item(({"door", "entrance"}), "You see nothing unusual about it.\n");

    add_exit(NOUTER+"red/r7","northeast",0,0,0);
    add_exit(NOUTER+"red/r12","east",0,0,0);
    add_exit(NOUTER+"red/r16","southeast",0,0,0);
    add_exit(NOUTER+"red/r15","south",0,0,0);
    add_exit(NOUTER+"red/smith","southwest",0,0,0);
    add_exit(NOUTER+"red/animals","west");
}


