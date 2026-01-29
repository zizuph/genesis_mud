#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Market square in the Red Quarter");
    set_extra_long("You are at the southern end of the market square. " +
		"Apart from the merchants who wander the marketplace, various shops " +
		"and establishments line the square. Southeast of here lies a " +
		"pawnshop, while a road leads away from the square to the south. The " +
		"entrance to the jewelry shop southwest of here has been nailed shut.");
	set_quarter(RED);
	add_item_market("square");
	add_item_sidewalks();
	add_item_buildings();

	add_item(({"jewelry shop", "entrance"}), "A note has been pinned next to " +
		"entrance.\n");
	add_item("note", "The note reads: 'Closed for repairs'\n");
	add_item("pawnshop", "The nice large letters above the entrance reads: \"Lute's Loot\".\n");
	add_item("road", "The road leads south of here, towards the area of the " +
		"Red Dragonarmy camp.\n");
    add_item("camp", "The camp is south of here.\n");

    add_exit(NOUTER+"red/r12","north",0,0,0);
    add_exit(NOUTER+"red/r13","northeast",0,0,0);
    add_exit(NOUTER+"red/store1","southeast",0,0,0);
    add_exit(NOUTER+"red/r18","south",0,0,0);
    add_exit(NOUTER+"red/r11","northwest",0,0,0);
}

