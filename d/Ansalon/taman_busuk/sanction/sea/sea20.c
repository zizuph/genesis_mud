#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/common/defs.h"

inherit SANCTION_OUT;

create_sanction_room()
{
    set_short("In Newsea");
    set_long("The ship is in the Newsea, just outside Newports.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
