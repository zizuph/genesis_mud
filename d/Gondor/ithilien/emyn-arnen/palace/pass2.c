inherit "/d/Gondor/common/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/ithilien/emyn-arnen/arnen_defs.h"

object  door;

void
create_room()
{
    set_short("A narrow passage");
    set_long(BSN("The narrow passage is running north from here. "
      + "It does not continue further to the south but opens onto "
      + "a large hall to the east."));

    add_exit(ITH_DIR + "emyn-arnen/palace/pass1",  "north", 0, 1);
    add_exit(ITH_DIR + "emyn-arnen/palace/sthall", "east", 0, 1);

    PALACE_FLOOR
    PALACE_STONES
    PALACE_WALLS

    add_item(({"passage", "corridor", }), BSN(
        "This narrow passage is leading north. It was probably meant to be "
      + "used by servants so they did not have to pass through the halls "
      + "distracting the Stewards and their visitors."));

    add_item(({"roof", "ceiling"}), BSN(
        "The ceiling is rather low in this narrow passage. It consists "
      + "of large stone flat stone blocks reaching from one wall to the "
      + "other."));

    FIX_EUID

}

