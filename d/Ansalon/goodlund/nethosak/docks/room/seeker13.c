/* /d/Ansalon/goodlund/nethosak/docks/room/seeker13.c
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
      "deck keeping the stench of the city to itself.  From the " +
      "railing, the coastline of Mithas can be seen stretching " +
      "to the south.  To the fore " +
      "and starboard the main mast rises up, its sails folded up and " +
      "tied down.  Steps head up to the aft deck, from which parts " +
      "of the city can be seen.  A plank has been lowered from the " +
      "ship to the docks below.\n");

    add_item(({"deck","main deck"}),
      "Extremely clean and free of any litter, the main deck is too " +
      "clean for only a rugged group of sailors taking care of it.  " +
      "However, the lack of obstructions gives the sailors free " +
      "roam of the ship without the worry of tripping about.\n");
    add_item(({"mast","main mast"}),
      "Sitting to the fore and starboard, the main sail rises up into " +
      "the air.  Its sails are folded up and tied down, ready to " +
      "go the instant the need arises.\n");
    add_item(({"ropes","rope","coils"}),
      "Neatly coiled ropes are scattered about the deck, ready to " +
      "be used to tie off sails.\n");
    add_item("sails",
      "Stacks of neatly folded sails are scattered about the deck.\n");
    add_item("steps",
      "Made for minotaurs, these sturdy steps leave quite a " +
      "challenge for the smaller races.\n");
    add_item("railing",
      "Looking over the port side railing the coastline of " +
      "Mithas can be seen stretching south and then hooking back in " +
      "and heading northwest creating a small peninsula that hides " +
      "the port of Nethosak from the enemies of the minotaur race.\n");
    add_item("coastline",
      "Extremely rocky and dangerous to unwary ships, the coastline " +
      "stretches south and then hooks back to the northeast " +
      "which creates a small peninsula, hiding Nethosak from its " +
      "enemies.  Splotches of forest are mixed in with the mostly " +
      "rocky terrain of the coast of Mithas.\n");
    add_item("aft deck",
      "A good twenty feet above the main deck, the only way to " +
      "to get there is via two sets of steps.  One set is here " +
      "and the other can be seen on the starboard side of the ship.  " + 
      "From the aft deck some of the city can be viewed.\n");
    add_item("plank",
      "A large wooden plank leads to the docks allowing the crew " +
      "to disembark.  Old and slowly rotting away, it is questionable " +
      "how much weight this plank could bear.\n");
    add_item("docks",
      "Being the farthest ship south, docked, there is not much to see " +
      "from this vantage point other then the end of the docks.  " +
      "It sounds like all the action is happening further north where " +
      "the large merchant and war ships are docked.\n");   
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

    add_exit(DROOM + "seeker10.c","fore",0);
    add_exit(DROOM + "seeker12.c","starboard",0);
    add_exit(DROOM + "seeker16.c","aft","@@steps");
} 

int steps()
{
   write("You climb up the huge steps.\n");
   return 0;
}