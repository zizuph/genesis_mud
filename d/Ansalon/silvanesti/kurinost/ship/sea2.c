#include "/d/Ansalon/silvanesti/kurinost/local.h"
#include "/d/Ansalon/common/defs.h"

inherit KURINOST_OUT;

create_kurinost_room()
{
    set_short("In the Bay of Balifor");
    set_long("The ship sails along the Bay of Balifor.  The mouth of "+
        "the Bay empties out into the Southern Courrain Ocean to the "+
        "southeast.\n");
    add_prop(ROOM_I_TYPE, ROOM_IN_WATER);
}
