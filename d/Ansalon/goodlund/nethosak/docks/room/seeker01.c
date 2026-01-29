/* /d/Ansalon/goodlund/nethosak/docks/room/seeker01.c
   Glain
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit NETHOSAK_OUT;

void
create_nethosak_room()
{
    set_short("Bow of Storm Seeker");
    set_long(
      "Coils of rope and folded sails clutter the bow of this " +
      "small sailing ship.  Ships can be seen sweeping across the " +
      "bay from this vantage point.  Their sails are billowing " +
      "in the same strong gusts that are blowing across the deck " +
      "keeping the stench of the city to itself.  Carved into the " +
      "bow of the ship is the large head of a minotaur, peering ahead.  " +
      "Currently lowered, the top of the anchor line wraps around " +
      "the capstan at the bow of the ship.  " +
      "A wooden spar extends from the bow to the foremast carrying " +
      "a small sail.  Directly to the aft the fore mast stretches " +
      "up overhead, it's sails folded up.\n");

    add_item("capstan",
      "A mechanical advantage that allows the crew to raise the " +
      "anchor.  A long pole through the capstan allows two crew " +
      "members to turn the capstan by walking around it, while " +
      "the line wraps around the bottom.\n");
    add_item(({"anchor","anchor line","line"}),
      "The thick rope is wrapped around the captsan.  From there it " +
      "travels through a hawsehole, over the the catshead, and " +
      "disappears into the deep waters.\n");
    add_item("hawsehole",
      "A hole in the bow of the ship that the anchor line passes " +
      "through.\n");
    add_item("catshead",
      "A small wooden beam that extends out from the ship with " +
      "the anchor line passing over it.  This allows the anchor " +
      "line to be raised and lowered without striking the side " +
      "of the ship.\n");
    add_item("spar",
      "Extending from the bow, the spar braces the foremast and " +
      "carries a spritsail.\n");
    add_item("ships",
      "All manner of minotaur ships sail through the Horned Bay.  " +
      "Some leaving for trade, but most in search of ill-gotten " +
      "treasures.\n");
    add_item("bay",
      "The bay is a natural protection for the port of " +
      "the city.  Not only does it hide the port from others but " +
      "running aground on a reef is a serious hazard for those " +
      "not knowing the layout of the bay.\n");
    add_item(({"deck","fore deck","bow"}),
      "Extremely clean and free of any litter, the fore deck is too " +
      "clean for only a rugged group of sailors taking care of it.  " +
      "However, the lack of obstructions gives the sailors free " +
      "roam of the ship without the worry of tripping about.\n");
    add_item(({"mast","fore mast"}),
      "Sitting to the aft, the fore mast rises up into " +
      "the air.  Its sails are folded up and tied down, ready to " +
      "go the instant the need arises.\n");
    add_item(({"ropes","rope","coils"}),
      "Neatly coiled ropes are scattered about the deck, ready to " +
      "be used to tie off sails.\n");
    add_item("sails",
      "Stacks of neatly folded sails are scattered about the deck.\n");
    add_item(({"carving","head"}),
      "This is actually the ramming device carved into the likes " +
      "of the head of a minotaur.  The minotaur has great horns " +
      "that slowly curve up until they point straight up.  " +
      "He appears to be seeking something out.\n");
    add_item("city",
      "The rigging of the ship blocks your view of the city.\n");
    add_item("ship",
      "Skillfully crafted, this ship appears to be built for speed " +
      "more then warfare.  A rare thing among the minotaurs.\n");
    add_item("gusts",
      "Sharp gusts blow inland from the bay, help stemming the " +
      "stench of the city.\n");
    add_item("stench",
      "As with all minotaur cities, the stench is horrendous for " +
      "any non-minotaur visiting the city.  The few who have visited " +
      "a minotaur city have said the smell reminds them of a large cow " +
      "barn with no ventilation.\n");

    add_exit(DROOM + "seeker03","aft",0);
    add_exit(DROOM + "seeker02","starboard","@@starboard");
    add_exit(DROOM + "seeker04","port","@@port");
}

int starboard()
{
   write("You follow the starboard railing, moving to the aft.\n");
   return 0;
}

int port()
{
   write("You follow the port railing, moving to the aft.\n");
   return 0;
}