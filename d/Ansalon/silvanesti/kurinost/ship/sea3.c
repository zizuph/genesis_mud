#include "/d/Ansalon/silvanesti/kurinost/local.h"
#include "/d/Ansalon/common/defs.h"

inherit KURINOST_OUT;

create_kurinost_room()
{
    set_short("Near the docks of Kurinost");
    set_long("The ship is near the Kurinost docks.  To the south lies the "+
        "elven city of Kurinost, to the north and east is the Bay "+
        "of Balifor.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
