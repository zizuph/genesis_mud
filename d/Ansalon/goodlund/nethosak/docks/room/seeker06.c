/* /d/Ansalon/goodlund/nethosak/docks/room/seeker06.c
   Glain
   11/7/98
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit NETHOSAK_OUT;

object door;

void reset_nethosak_room()
{
   return;
}

void create_nethosak_room()
{
    set_short("Main deck of Storm Seeker");
    set_long(
      "Coils of rope and folded sails clutter the main deck of this " + 
      "small sailing ship.  Strong gusts of wind blow across the " +
      "deck keeping the stench of the city to itself.  To the aft " +
      "the main mast rises up, its sails folded up and tied down.  " +
      "Above a large wooden door in the fore wall is the fore deck.\n");

    add_item(({"deck","main deck"}),
      "Extremely clean and free of any litter, the main deck is too " +
      "clean for only a rugged group of sailors taking care of it.  " +
      "However, the lack of obstructions gives the sailors free " +
      "roam of the ship without the worry of tripping about.\n");
    add_item(({"mast","main mast"}),
      "Sitting to the aft, the main sail rises up into " +
      "the air.  Its sails are folded up and tied down, ready to " +
      "go the instant the need arises.\n");
    add_item(({"ropes","rope","coils"}),
      "Neatly coiled ropes are scattered about the deck, ready to " +
      "be used to tie off sails.\n");
    add_item("sails",
      "Stacks of neatly folded sails are scattered about the deck.\n");
    add_item("foredeck",
      "A good fifteen feet above the main deck, the only way to " +
      "to get there is via two sets of steps, one on each side of the " +
      "main deck, which lead up to the foredeck.  From there the " +
      "entire bay can be viewed.\n");
    add_item(({"wall","fore wall"}),
      "Running across the width of the ship this wall seperates " +
      "the main deck from the fore deck fifteen feet above.  A " +
      "large wooden door leads to some rooms under the fore deck.\n");
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

    add_exit(DROOM + "seeker05.c","starboard",0);
    add_exit(DROOM + "seeker07.c","port",0);
    add_exit(DROOM + "seeker09.c","aft",0);

    door = clone_object(DOBJ + "door1a.c");
    door->move(TO);
 
    reset_nethosak_room();
}
 