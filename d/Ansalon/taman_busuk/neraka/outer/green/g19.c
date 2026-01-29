#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("A road in the Green Quarter");
    set_extra_long("You stand upon a small dirt road leading northeast " +
		"towards the White Quarter, while " +
		"going south will take you to the heart of the Green Quarter. " +
		"A warehouse can be found on each side of the road here. " +
		"There are wooden sidewalks along the roads here, since the " +
		"roads are often used for wagons and horses.");
    set_quarter(GREEN);

	add_item("warehouse", "It is a large wooden building used as a " +
		"storage facility.\n");
    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

	add_exit(NOUTER+"green/g20","north",0,0,0);
	add_exit(NOUTER+"green/g5","south",0,0,0);
	add_exit(NOUTER+"green/ware2","northeast","@@msg@@",0,0);
	add_exit(NOUTER+"green/ware1","northwest","@@msg@@",0,0);
}

int
msg()
{
	write("You leave the road and step into the large warehouse.\n");
	return 0;
}
