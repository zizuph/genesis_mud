#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("A road in the Red Quarter");
    set_extra_long("You are travelling along a well-used road, " +
		"leading towards the Blue Quarter to the north. " +
		"Wooden sidewalks line the roads here, since wagons and " +
    	"horses usually travel on the dirt roads.");
    set_quarter(RED);
    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

    add_exit(NOUTER+"red/r21","north",0,0,0);
    add_exit(NOUTER+"red/r19","southwest",0,0,0);
}
