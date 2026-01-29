#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_OUT;

void
create_neraka_room()
{
 	set_short("A road in the Green Army camp");
    set_extra_long("You are walking on a dirt road in the Green Army camp. " +
        "All around you tents spread out.");

    set_quarter(GREEN);
    add_item_dirtroad();
    add_item_camp();

    add_exit(NOUTER+"green/g11","west",0,0,0);
    add_exit(NOUTER+"green/g9","northeast",0,0,0);

}
