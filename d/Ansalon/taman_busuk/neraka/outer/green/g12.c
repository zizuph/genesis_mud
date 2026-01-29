#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
 	set_short("A road in the Green Army camp");
    set_extra_long("You are walking on a dirt road in the Green Army camp. " +
        "There are tents both to the southeast and southwest here, while the camp " +
		"spreads out in the other directions.");

    set_quarter(GREEN);
    add_item_dirtroad();
    add_item_camp();

    add_exit(NOUTER+"green/g11","east",0,0,0);
    add_exit(NOUTER+"green/g13","north",0,0,0);
	add_exit(NOUTER+"green/t4","southwest","@@msg@@",0,0);
	add_exit(NOUTER+"green/t3","southeast","@@msg@@",0,0);
}

int
msg()
{
    write("You pull aside the flap and enter the tent.\n");
    return 0;
}
