/* /d/Ansalon/goodlund/nethosak/docks/room/seeker03.c
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
      "sailing ship.  Strong gusts of wind blow across the deck keeping the " +
      "stench of the city to itself.  Stretching up overhead is " +
      "the fore mast with its sails folded up.\n");

    add_item(({"deck","fore deck","bow"}),
      "Extremely clean and free of any litter, the fore deck is too " +
      "clean for only a rugged group of sailors taking care of it.  " +
      "However, the lack of obstructions gives the sailors free " +
      "roam of the ship with the worry of tripping about.\n");
    add_item(({"mast","fore mast"}),
      "Sitting to the port, the fore mast rises up into " +
      "the air.  Its sails are folded up and tied down, ready to " +
      "go the instant the need arises.\n");
    add_item(({"ropes","rope","coils"}),
      "Neatly coiled ropes are scattered about the deck, ready to " +
      "be used to tie off sails.\n");
    add_item("sails",
      "Stacks of neatly folded sails are scattered about the deck.\n");
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

    add_exit(DROOM + "seeker01","fore",0);
    add_exit(DROOM + "seeker02","starboard",0);
    add_exit(DROOM + "seeker04","port",0);
}
