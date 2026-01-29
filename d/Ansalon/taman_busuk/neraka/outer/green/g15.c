#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
 	set_short("A road in the Green Army camp");
    set_extra_long("You are walking on a dirt road in the Green Army camp. " +
        "All around you tents spread out. The market square lies just " +
		"east of here.");

    set_quarter(GREEN);
    add_item_dirtroad();
    add_item_camp();
	add_item_market("square");

    add_exit(NOUTER+"green/g5","east",0,0,0);
    add_exit(NOUTER+"green/g16","west",0,0,0);

}
