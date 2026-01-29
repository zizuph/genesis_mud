#include "/d/Ansalon/taman_busuk/sanction/local.h"
#include "/d/Ansalon/common/defs.h"

inherit SANCTION_OUT;

create_sanction_room()
{
    set_short("Outside the Sanction harbour");
    set_long("The ship is just outside the Sanction harbour, visible to " +
        "the east. The Newsea stretch out to the west.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
