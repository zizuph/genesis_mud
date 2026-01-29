#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("A road in the Green Quarter");
    set_extra_long("You stand upon a small dirt road leading east " +
		"towards the inner city. Going west will take you back " +
		"to the market square of the Green Quarter. " +
		"There are wooden sidewalks along the roads here, since the " +
		"roads are often used for wagons and horses.");
    set_quarter(GREEN);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
	add_item_market("square");

	add_exit(NOUTER+"green/g5","west",0,0,0);
	add_exit(NOUTER+"green/g7","east",0,0,0);
}
