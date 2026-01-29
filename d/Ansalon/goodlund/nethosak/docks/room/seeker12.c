/* /d/Ansalon/goodlund/nethosak/docks/room/seeker12.c
   Glain
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit NETHOSAK_OUT;

void create_nethosak_room()
{
    set_short("Main deck of Storm Seeker");
    set_long(
      "Coils of rope and folded sails clutter the main deck of this " + 
      "small sailing ship.  Strong gusts of wind blow across the " +
      "deck keeping the stench of the city to itself.  To the fore " +
      "the main mast rises up, its sails folded up and tied down.  " +
      "A large tarp has been draped over a cargo hatch on the deck.  " +
      "Above a set of wooden double doors in the aft wall is the " + 
      "aft deck.\n");

    add_item(({"tarp","tarpaulin"}),
      "This large waterproof tarpaulin covers the cargo hatch, to " +
      "prevent seawater from entering the ship's hold.\n");
    add_item(({"hatch","cargo hatch"}),
      "This covers the opening that is used to raise or lower " +
      "cargo from the hold.  It is battened down and covered with " +
      "a waterproof tarpaulin to prevent seawater from entering " +
      "the ship's hold.\n");
    add_item(({"deck","main deck"}),
      "Extremely clean and free of any litter, the main deck is too " +
      "clean for only a rugged group of sailors taking care of it.  " +
      "However, the lack of obstructions gives the sailors free " +
      "roam of the ship without the worry of tripping about.\n");
    add_item(({"mast","main mast"}),
      "Sitting to the fore, the main sail rises up into " +
      "the air.  Its sails are folded up and tied down, ready to " +
      "go the instant the need arises.\n");
    add_item(({"ropes","rope","coils"}),
      "Neatly coiled ropes are scattered about the deck, ready to " +
      "be used to tie off sails.\n");
    add_item("sails",
      "Stacks of neatly folded sails are scattered about the deck.\n");
    add_item("aft deck",
      "A good twenty feet above the main deck, the only way to " +
      "to get there is via two sets of steps, one on each side of the " +
      "main deck, which lead up to the aft deck.  From there most " +
      "of the city can be viewed.\n");
    add_item(({"doors","wooden doors","double doors","wooden double doors"}),
      "Large enought to fit a minotaur, these doors lead into " +
      "some rooms under the aft deck.\n");
    add_item(({"wall","aft wall"}),
      "Running across the width of the ship this wall seperates " +
      "the main deck from the aftdeck twenty feet above.  A " +
      "pair of wooden doors lead to some rooms under the aft deck.\n");
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

    add_exit(DROOM + "seeker11.c","starboard",0);
    add_exit(DROOM + "seeker13.c","port",0);
    add_exit(DROOM + "seeker09.c","fore",0);
} 