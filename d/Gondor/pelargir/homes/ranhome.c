inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in a ransacked house");
    set_long(BSN("This house, though it looked fine on the outside, "
      + "is in shambles. The table has been overturned and all the "
      + "plates and glasses have been smashed on the floor. Someone "
      + "has even smashed the hutch and cabinets. The door to the "
      + "street is the only way out."));
    add_item("table", "It is a typical four legged table upside down.\n");
    add_item("drawers",BSN("The drawers are empty and broken."));
    add_item("door",BSN("The door stands open. It seems that "+
      "due to some damage to the "+
      "hinges, it will probably never shut again."));
    add_item("hutch", BSN("The drawers have all been pulled out, "
      + "though strangely enough you don't see anything of value "
      + "lying about that might have been in them."));
    add_item("cabinets", BSN("Not a very sturdy cabinet, at least "
      + "it didn't take well to the way someone smashed it."));
    add_item(({"dishes","glasses","plates"}), BSN("It is fairly "
      + "hard to discern the difference between each dish, as they "
      + "are all nothing but shards of glass now. Watch your step!"));

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PELAR_DIR + "streets/admiral07", "south", 0);
}

