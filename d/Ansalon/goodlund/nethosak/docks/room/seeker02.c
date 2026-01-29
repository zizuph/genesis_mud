/* /d/Ansalon/goodlund/nethosak/docks/room/seeker02.c
   Glain
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit NETHOSAK_OUT;

void create_nethosak_room()
{
    set_short("Fore deck of Storm Seeker");
    set_long(
      "Coils of rope and folded sails clutter the fore deck of this small " +
      "sailing ship.  Ships can be seen sweeping across the bay " +
      "from this vantage point.  Their sails are billowing in the " +
      "same strong gusts that are blowing across the deck keeping the " +
      "stench of the city to itself.  From the " +
      "railing, the docks can be seen below, where cargo is being " +
      "loaded off and on other docked ships.  Directly to the port " +
      "the fore mast stretches up overhead, its sails folded up.  " +
      "To the aft, a set of steps head down to the main deck.\n");

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
      "Rising high above, the main mast creaks and groans as it sways " +
      "in the strong winds.  Its sails are folded up and tied down, " +
      "ready to go the instant the need arises.\n");
    add_item(({"ropes","rope","coils"}),
      "Neatly coiled ropes are scattered about the deck, ready to " +
      "be used to tie off sails.\n");
    add_item("sails",
      "Stacks of neatly folded sails are scattered about the deck.\n");
    add_item("steps",
      "These sturdy steps were made for minotaurs, leaving some " +
      "of the smaller races a little climbing exercise.\n");
    add_item("main deck",
      "Looking upon the main deck from this vantage point, the " +
      "cleaned deck seems out of place for a crew of ruthless " +
      "minotaurs.\n");
    add_item("railing",
      "Looking over the starboard side railing the docks can be " +
      "seen below.  Like any other time of the day, the docks are " +
      "bustling with minotaurs loading and unloading cargo from " +
      "the various docked ships.\n");
    add_item(({"dock","docks"}),
      "Like any other time of the day, the docks are bustling " +
      "with minotaurs loading and unloading cargo from the " +
      "various docked ships.\n");
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
    add_item("cargo",
      "All kinds and sizes of cargo are being loaded on and off the " +
      "the other ships docked in port.  It is strikingly odd that " +
      "the docks woul be so busy, as minotaurs are not noted for " +
      "their trade techniques, only rarely trading with Flotsam to " +
      "get supplies that they can not produce themselves.\n");

    add_exit(DROOM + "seeker01","fore","@@bow");
    add_exit(DROOM + "seeker03","port",);
    add_exit(DROOM + "seeker05","aft","@@steps");
}

int bow()
{
   write("You follow the starboard railing to the bow of the ship.\n");
   return 0;
}

int steps()
{
   write("You climb down the huge steps.\n");
   return 0;
}