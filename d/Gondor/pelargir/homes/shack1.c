inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("in a run-down shack");
    set_long(BSN("You are in an old run-down shack. The smell of fish "
      + "and reek of dead things would bring you to your knees if the "
      + "dust in here did not nearly make you sneeze. The floor, "
      + "walls, and ceiling all look like they could use a few more "
      + "nails - or anything that could make them a little sturdier."));
    add_prop(ROOM_I_INSIDE,1);
    add_item(({"floor","dust"}),BSN("From the dust on this floor you believe "+
      "it needs to be swept. There is a pile of dead things "+
      "in one corner."));
    add_item("boards", BSN("You should better not touch them "+
      " as something could definitely break."));
    add_item(({"walls","ceiling"}),BSN("The walls and the "+
      "ceiling look to be ready to fall. A few nails here and there "+
      "might be required to help the shack to remain standing."));
    add_item(({"dead things","pile"}),BSN("It seems someone "+
      "has gathered a small heap of dead mice into the corner."));

    add_exit(PELAR_DIR + "streets/earnil02", "north", 0, 0);
}
