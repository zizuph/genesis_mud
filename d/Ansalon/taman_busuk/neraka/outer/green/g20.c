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
		"Northeast of here lies a warehouse. " +
		"There are wooden sidewalks along the roads here, since the " +
		"roads are often used for wagons and horses.");
    set_quarter(GREEN);

	add_item("warehouse", "It is a large wooden building used as a " +
		"storage facility.\n");
    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

	add_exit(NOUTER+"green/g21","north",0,0,0);
	add_exit(NOUTER+"green/g19","south",0,0,0);
	add_exit(NOUTER+"green/ware3","northeast","@@msg@@",0,0);
}

int
msg()
{
	write("You leave the road and step into the large warehouse.\n");
	return 0;
}
