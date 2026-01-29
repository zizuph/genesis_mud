/* /d/Ansalon/goodlund/nethosak/docks/room/seeker08.c
   Glain
   11/7/98
*/

#include "/d/Ansalon/goodlund/nethosak/docks/room/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit NETHOSAK_OUT;

void create_nethosak_room()
{
    set_short("Main deck of Storm Seeker");
    set_long(
      "Coils of rope and folded sails clutter the main deck of this " + 
      "small sailing ship.  Strong gusts of wind blow across the " +
      "deck keeping the stench of the city to itself.  From the " +
      "railing, the docks can be seen below, where cargo is being " +
      "loaded off and on other docked ships.  To the " +
      "port the main mast rises up, its sails folded up and " +
      "tied down.  A large hatchway leads down to the rooms " +
      "below deck.\n");

    add_item(({"deck","main deck"}),
      "Extremely clean and free of any litter, the main deck is too " +
      "clean for only a rugged group of sailors taking care of it.  " +
      "However, the lack of obstructions gives the sailors free " +
      "roam of the ship without the worry of tripping about.\n");
    add_item(({"mast","main mast"}),
      "Sitting to the port, the main sail rises up into " +
      "the air.  Its sails are folded up and tied down, ready to " +
      "go the instant the need arises.\n");
    add_item(({"ropes","rope","coils"}),
      "Neatly coiled ropes are scattered about the deck, ready to " +
      "be used to tie off sails.\n");
    add_item("sails",
      "Stacks of neatly folded sails are scattered about the deck.\n");
    add_item("railing",
      "Looking over the starboard side railing the docks can be " +
      "seen below.  Like any other time of the day, the docks are " +
      "bustling with minotaurs loading and unloading cargo from " +
      "the various docked ships.\n");
    add_item(({"dock","docks"}),
      "Like any other time of the day, the docks are bustling " +
      "with minotaurs loading and unloading cargo from the " +
      "various docked ships\n");
    add_item("ships",
      "Multitudes of ships are docked at the port of the city.  " +
      "Ranging in size from a small sailing ship, such as the one " +
      "you are standing on, to warships with crews of over three " +
      "hundred, all are manned by the famed minotaur sailors of " +
      "Mithas.  Making any of the ships formidable opponents in " +
      "the high seas.\n");
    add_item(({"hatch","hatchway","door","trapdoor"}),
      "Large and bulky, this hatch leads down to the rooms inside " +
      "the hull of the ship.  From the smell emenating from below " +
      "this could only be the living quarters of minotaurs.\n");
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

    add_exit(DROOM + "seeker05.c","fore",0);
    add_exit(DROOM + "seeker09.c","port",0);
    add_exit(DROOM + "seeker11.c","aft",0);
} 