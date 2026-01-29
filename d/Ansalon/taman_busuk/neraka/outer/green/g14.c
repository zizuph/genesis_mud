#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
 	set_short("A road in the Green Army camp");
    set_extra_long("You are walking on a dirt road in the Green Army camp. " +
        "There is a tent to the northwest, while the camp spreads out in the other " +
        "directions.");

    set_quarter(GREEN);
    add_item_dirtroad();
    add_item_camp();

    add_exit(NOUTER+"green/g13","east",0,0,0);
    add_exit(NOUTER+"green/t5","northwest","@@msg@@",0,0);

}

int
msg()
{
    write("You pull aside the flap and enter the tent.\n");
    return 0;
}
