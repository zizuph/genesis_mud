#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;
inherit RANTEAM;

void
create_neraka_room()
{
	set_short("A road in the Green Quarter");
    set_extra_long("You stand upon a small dirt road leading southeast " +
		"towards the Red Quarter. Going northwest will take you back " +
		"to the heart of the Green Quarter. " +
		"There are wooden sidewalks along the roads here, since the " +
		"roads are often used for wagons and horses.");
    set_quarter(GREEN);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

	add_exit(NOUTER+"green/g4","northwest",0,0,0);
	add_exit(NOUTER+"green/g2","southeast",0,0,0);

	set_team_size(2 + random(2));
	set_random_table(NT_OUTER);

	reset_room();
}
