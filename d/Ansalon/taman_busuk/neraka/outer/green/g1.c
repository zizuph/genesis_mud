#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("A road at the border of the Green Quarter");
    set_extra_long("You stand upon a small dirt road at the border " +
		"to the Red Quarter to the southeast. Northeast of here lies " +
		"the guard tower, while the road leads back into the Green Quarter " +
		"northwest of here. " +
		"Wooden sidewalks line the roads here, since wagons and " +
    	"horses usually travel on the dirt roads.");
	add_item(({"tower", "guard tower"}), "The stone tower marks the border " +
		"of the Green Quarter.\n");
	set_quarter(GREEN);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

	add_exit(NOUTER+"green/g2","northwest",0,0,0);
	add_exit(NOUTER+"green/tow1","northeast",0,0,0);
	add_exit(NOUTER+"red/r8","southeast",0,0,0);
}
