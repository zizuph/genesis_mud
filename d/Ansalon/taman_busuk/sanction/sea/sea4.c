#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/common/defs.h"

inherit SANCTION_OUT;

create_sanction_room()
{
    set_short("In the Ergothian Sea");
    set_long("The ship is sailing in the Ergothian Sea, between North and " +
        "South Ergoth.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
