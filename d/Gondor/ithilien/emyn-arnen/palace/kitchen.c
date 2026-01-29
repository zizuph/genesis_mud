inherit "/d/Gondor/common/room";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/ithilien/emyn-arnen/arnen_defs.h"

object  gate;

void
create_room()
{
    set_short("The kitchen in the House of the Stewards");
    set_long(BSN("This is the room where the meals were prepared in the "
      + "House of the Stewards. A large fireplace is built into the south "
      + "wall. All other utensils and fixtures have been stolen or "
      + "destroyed."));

    add_item(({"south wall", "fireplace", "chimney", "hearth", "grill", }), BSN(
        "The fireplace was built into the south wall of the kitchen. It "
      + "is large enough to roast oxen in one piece in it. But the spit "
      + "is missing like all the other fixtures that once were in use here."));

    add_item(({"fixtures", "utensils", "tools", }), BSN(
        "Except for the fireplace there is nothing left except the bare walls. "
      + "In a few places you can see that something was removed or destroyed. "
      + "White spots in many places along the walls indicate where once, "
      + "cupboards, shelves, and tools were hanging. In the corners next "
      + "to the fireplace one can still see what remains of two small stoves "
      + "made from bricks."));

    add_item(({"brick", "bricks", "brick walls"}), BSN(
        "The two small stoves were made from bricks. The small walls that are "
      + "all what remains are charred on the inside."));

    add_item(({"stove", "stoves", "small stoves"}), BSN(
        "They have been destroyed, all that still remains are brick walls a little "
      + "more than a foot high which are charred on the inside."));

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

    add_exit(ITH_DIR + "emyn-arnen/palace/larder",    "north", 0, 0);
    add_exit(ITH_DIR + "emyn-arnen/rrd1",             "northeast", 0, 0);
    add_exit(ITH_DIR + "emyn-arnen/palace/ghall",     "west",  0, 0);
    add_exit(ITH_DIR + "emyn-arnen/palace/well_room", "down",  0, 1);

    gate = clone_object(ITH_DIR + "emyn-arnen/obj/kitchen_gate_in");
    gate->move(TO);

    (ITH_DIR + "emyn-arnen/palace/ghall")->load_me();
}

void
reset_room()
{
    gate->reset_door();
}
