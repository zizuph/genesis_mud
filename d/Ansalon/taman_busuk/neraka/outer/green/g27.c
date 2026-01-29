#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("A road at the border of the Green Quarter");
    set_extra_long("You stand upon a small dirt road at the border " +
		"to the White Quarter to the north. West of here lies " +
		"the guard tower, while the road leads back into the Green Quarter " +
		"to the southeast. " +
		"Wooden sidewalks line the roads here, since wagons and " +
    	"horses usually travel on the dirt roads.");
	add_item(({"tower", "guard tower"}), "The stone tower marks the border " +
		"of the Green Quarter.\n");
	set_quarter(GREEN);

    add_item_dirtroad();
    add_item_sidewalks();
    add_item_buildings();

	add_exit(NOUTER+"white/w14","north",0,0,0);
	add_exit(NOUTER+"green/tow2","west",0,0,0);
	add_exit(NOUTER+"green/g26","southeast",0,0,0);
}
