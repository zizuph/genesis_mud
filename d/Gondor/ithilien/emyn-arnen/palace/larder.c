inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/ithilien/emyn-arnen/arnen_defs.h"

void
create_room()
{
    set_short("A storage room");
    set_long(BSN("This is the larder where the food that was to be prepared "
      + "in the kitchen was stored. As in the kitchen, there is nothing left "
      + "but the bare walls."));

    PALACE_WALLS
    CELLAR_FLOOR

    add_item(({"roof", "ceiling", "vault", }), BSN(
        "The ceiling is a large vault shaped like a roman arch running north "
      + "south."));
    add_item(({"stones", "stone", "blocks", }), BSN(
        "The stone blocks that were used for the walls and the roof "
      + "were all cut from the same rock of light grey colour. Master masons "
      + "have fitted them together so expertly that nowhere the use of "
      + "mortar was required."));

    add_exit(ITH_DIR + "emyn-arnen/palace/kitchen",    "south", 0, 0);

}
