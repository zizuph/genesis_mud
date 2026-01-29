#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("A road in the Green Quarter");
    set_extra_long("You stand upon a small dirt road leading north " +
		"towards the White Quarter. " +
		"There are wooden sidewalks along the roads here, since the " +
		"roads are often used for wagons and horses.");
    set_quarter(GREEN);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

	add_exit(NOUTER+"green/g24","north",0,0,0);
	add_exit(NOUTER+"green/g7","south",0,0,0);
}
