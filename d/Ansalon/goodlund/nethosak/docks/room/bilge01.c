/* /d/Ansalon/goodlund/nethosak/docks/room/bilge01.c
   Glain
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit NETHOSAK_IN;

void create_nethosak_room()
{
    set_short("Bilge room of Storm Seeker");
    set_long(
      "Here, in the back of the ship's hold, small pools of water have " +
      "collected giving the room a musty smell.  A bilge pump sits " +
      "on either side of the room, with lots of room between so " +
      "they may be manned more easily.  The floor slightly slants to " +
      "the aft where it collects by the pumps' drain.  Two large " +
      "pallets full of bricks, one on each side of the hold, have " +
      "been sit back in here.  A few small " +
      "crates are scattered about the hold to the fore.\n");

    add_item(({"pools","water"}),
      "Small dirty pools of water have collected here at the aft " +
      "end of the ship.\n");
    add_item(({"bilge pump","pump","pumps"}),
      "A bilge pump has been built into the ship on either side " +
      "of the hold.  A large wheel on each pump allows two of the " +
      "crew to man each pump.  Pipes start in the aft of the ship, " +
      "continue through the pumps, and finally end on the outside " +
      "of the hull.\n");
    add_item("drain",
      "This small drain connects with the pipes of the bilge pumps, " +
      "which in turn lead to the outside of the ship.\n");
    add_item("crates",
      "A few small wooden crates are scattered about the hold to " +
      "the fore.  You are unable to make any more details out.\n");
    add_item("hold",
      "The section of the ship you stand in now, appears to be the " +
      "bilge room.\n");
    add_item("floor",
      "Scrubbed clean, the wooden floor is in perfect condition.  It " +
      "has a slight slant to the aft, where water collects to be " +
      "pumped out.\n");
    add_item(({"pallets","bricks"}),
      "Old bricks have been stacked on top of the two pallets " +
      "back here.  Each pallet has been partially covered by a " +
      "tarp and tied down with ropes to prevent the bricks from " +
      "falling off.\n");

    add_exit(DROOM + "cargo01.c","fore",0);
} 