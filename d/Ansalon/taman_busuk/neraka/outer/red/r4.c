#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("A road in the Red Quarter");
    set_extra_long("The dirt road you stand upon leads north into the " +
    	"inner city of Neraka, and south to the Red Dragon Army camp and " +
    	"square. Wooden sidewalks line the roads here, since wagons and " +
    	"horses usually travel on the dirt roads.");
    set_quarter(RED);
    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

    add_exit(NOUTER+"red/r3","north",0,0,0);
    add_exit(NOUTER+"red/r5","south",0,0,0);
}
