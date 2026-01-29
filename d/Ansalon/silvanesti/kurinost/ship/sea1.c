#include "/d/Ansalon/silvanesti/kurinost/local.h"
#include "/d/Ansalon/common/defs.h"

inherit KURINOST_OUT;

create_kurinost_room()
{
    set_short("Outside the Balifor harbour");
    set_long("The ship is just outside the Balifor harbour, the expanse "+
        "of the Bay of Balifor stretches out north and south.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
