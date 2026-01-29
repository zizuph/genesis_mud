#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("Market square in the Red Quarter");
    set_extra_long("You are at the eastern end of the market square. " +
		"Apart from the merchants who wander the marketplace, various shops " +
		"and establishments line the square. Just east of here lies a small " +
		"pub, while a road leads away from the square to the northeast.");
	set_quarter(RED);
    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");

	add_item(({"pub", "small pub"}), "The sign about the entrance reads: 'The Little " +
		"Red Rooster'. You dare not speculate on the nature of this name.\n");
	add_item("road", "The road leads northeast, towards the Blue Quarter.\n");
    add_exit(NOUTER+"red/r19","northeast",0,0,0);
    add_exit(NOUTER+"red/pub1","east","@@msg@@",0,0);
    add_exit(NOUTER+"red/r16","southwest",0,0,0);
    add_exit(NOUTER+"red/r12","west",0,0,0);
    add_exit(NOUTER+"red/r7","northwest",0,0,0);
}

int
msg()
{
    write("You boldly enter the Little Red Rooster.\n");
    return 0;
}

