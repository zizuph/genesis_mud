#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
 	set_short("A road in the Red Army camp");
    set_extra_long("You are walking on a dirt road in the Red Army camp. " +
        "All around you tents spread out.");
    set_quarter(RED);
    add_item_dirtroad();
    add_item_camp();

    add_exit(NOUTER+"red/r26","east",0,0,0);
    add_exit(NOUTER+"red/r29","west",0,0,0);

}

int
msg()
{
    write("You pull aside the flap and enter the tent.\n");
    return 0;
}

