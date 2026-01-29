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
    set_long(BSN("The narrow passage is running south from the door "
      + "to the north. The walls, ceiling, and floor are almost "
      + "completely featureless."));

    add_exit(ITH_DIR + "emyn-arnen/palace/pass2", "south", 0, 1);

    PALACE_FLOOR
    PALACE_STONES
    PALACE_WALLS

    add_item(({"passage", "corridor", }), BSN(
        "This narrow passage is leading south. It was probably meant to be "
      + "used by servants so they did not have to pass through the halls "
      + "distracting the Stewards and their visitors."));

    add_item(({"roof", "ceiling"}), BSN(
        "The ceiling is rather low in this narrow passage. It consists "
      + "of large flat stone blocks reaching from one wall to the "
      + "other."));

    FIX_EUID

    door = clone_object(ITH_DIR + "emyn-arnen/obj/sqcin_door");
    door->move(TO);
}

void
reset_room()
{
    door->reset_door();
}
