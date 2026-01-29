#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/common/defs.h"

inherit SANCTION_OUT;

create_sanction_room()
{
    set_short("East of Southern Ergoth");
    set_long("The ship is sailing in the Ergothian sea, east of " +
        "Southern Ergoth.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
