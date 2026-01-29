#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("A road at the border of the Red Quarter");
    set_extra_long("You are travelling along a well-used road " +
		"at the border to the Blue Quarter to the north. Northwest " +
		"of here lies the guard tower, while the road leads southwest " +
		"back into the center of the Red quarter. " +
		"Wooden sidewalks line the roads here, since wagons and " +
    	"horses usually travel on the dirt roads.");
	set_quarter(RED);
	
	add_item(({"tower", "guard tower"}), "The stone tower marks the border " +
		"of the Red Quarter.\n");
    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

    add_exit(NOUTER+"blue/b1","north",0,0,0);
    add_exit(NOUTER+"red/tow1","northwest",0,0,0);
	add_exit(NOUTER+"red/r22","southwest",0,0,0);
}
