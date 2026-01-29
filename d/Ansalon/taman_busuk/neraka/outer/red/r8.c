#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("A road at the border of the Red Quarter");
    set_extra_long("You stand upon a small dirt road at the border " +
		"to the Green Quarter to the northwest. North of here lies " +
		"the guard tower, but you can not find any way to enter it " +
		"from here however. Roads lead back into the Red Quarter to " +
		"the south and southwest of here.");
	set_quarter(RED);
	add_item(({"tower", "guard tower"}), "The stone tower marks the border " +
		"to the Red Quarter.\n");
	add_item_dirtroad();
	add_item_sidewalks();
	add_item_buildings();

    add_exit(NOUTER+"green/g1","northwest",0,0,0);
    add_exit(NOUTER+"red/r1","south",0,0,0);
    add_exit(NOUTER+"red/r9","southeast",0,0,0);
}
