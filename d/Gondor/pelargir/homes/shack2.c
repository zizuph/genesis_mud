inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in a run-down shack");
    set_long(BSN("You are in an old run-down shack. "+
        "Though it does not look like anyone takes care of it, "+
        "there are a few signs of recent use, like the bits of "+
        "half eaten food scattered about the unmade sleeping pallet. "+
        "The pallet is the only furniture in the one room "+
        "shanty and without a lock on the door you can see why."));
    add_prop(ROOM_I_INSIDE,1);
    add_item("floor",BSN("From the dust on this floor you believe"+
        " even the spiders would leave tracks."));
    add_item("boards",BSN("You should better not touch them"+
        " as something could definitely break."));
    add_item("pallet",BSN("This is a crumpled, straw stuffed "+
        "sleeping pallet. Closer inspection reveals that someone "+
        "has soiled the sheets."));
    add_exit(PELAR_DIR + "streets/peddlers01", "southwest", 0);
}
