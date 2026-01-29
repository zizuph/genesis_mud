inherit "/d/Gondor/common/room";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/ithilien/emyn-arnen/arnen_defs.h"

#define MIN_AWARENESS		40

object  door;

void
create_room()
{
    set_short("A corridor leading to the servant quarters");
    set_long(BSN("This corridor once continued west, leading to the servant "
      + "quarters of the House of the Stewards. But west of here, the "
      + "ceiling collapsed and the upper floor tumbled down into the "
      + "corridor so that the passage is blocked."));

    add_exit(ITH_DIR + "emyn-arnen/palace/hall1", "east", 0, 1);

    PALACE_FLOOR
    PALACE_STONES

    add_item(({"passage", "corridor", }), BSN(
        "The corridor once continued west to the servant quarters, but "
      + "the ceiling collapsed and now the corridor is filled with the "
      + "ruins of walls and the roof of the upper floor."));

    add_item(({"roof", "ceiling"}), BSN(
        "The ceiling here looks still rather stable, but further west "
      + "it has collapsed."));

    add_item(({"wall", "walls", }), VBFC_ME("exa_walls"));

    add_prop(ROOM_I_INSIDE, 1);

    FIX_EUID

    door = clone_object(ITH_DIR + "emyn-arnen/obj/sqcout_door");
    door->move(TO);
}

string
exa_walls()
{
    string  desc = "The walls are made of large grey stone blocks that were "
    + "expertly hewn, polished and fitted together without the use of mortar.";

    if (TP->query_skill(SS_AWARENESS) > MIN_AWARENESS)
        desc += " In the south wall you find a cleverly hidden secret door. "
          + "It merges so well with the surrounding wall that it is very "
          + "difficult to see it.";

    TP->add_prop("_exa_s_wall", 1);
    return BSN(desc);
}

void
reset_room()
{
    door->reset_door();
}
