#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("A road in the Red Quarter, just south of the market square");
    set_extra_long("You are travelling along a well-used road in the Red Quarter. " +
		"Just north of here lies the market square, while the road continues " +
		"towards the Red Army camp to the southwest. Wooden sidewalks line the roads " +
		"here, since wagons and horses usually travel on the dirt roads.");
    set_quarter(RED);
    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");

    add_exit(NOUTER+"red/r16","north",0,0,0);
    add_exit(NOUTER+"red/r25","southwest",0,0,0);
    add_exit(NOUTER+"red/backyard","southeast",0,1,1);
}
