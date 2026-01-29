#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
 	set_short("A road in the Green Army camp");
    set_extra_long("You are walking on a dirt road in the Green Army camp. " +
        "There is a tent to the southeast, while the camp spreads out in the other " +
        "directions. The market square lies just north of here.");

    set_quarter(GREEN);
    add_item_dirtroad();
    add_item_camp();
	add_item_market("square");

    add_exit(NOUTER+"green/g5","north",0,0,0);
	add_exit(NOUTER+"green/g9","southwest",0,0,0);
    add_exit(NOUTER+"green/t1","southeast","@@msg@@",0,0);

}

int
msg()
{
    write("You pull aside the flap and enter the tent.\n");
    return 0;
}
