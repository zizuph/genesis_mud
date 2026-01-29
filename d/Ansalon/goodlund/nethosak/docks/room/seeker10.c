/* /d/Ansalon/goodlund/nethosak/docks/room/seeker10.c
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
      "to the south.  To the " +
      "starboard the main mast rises up, its sails folded up and " +
      "tied down.  A large hatchway leads down to the rooms " +
      "below deck.\n");

    add_item(({"deck","main deck"}),
      "Extremely clean and free of any litter, the main deck is too " +
      "clean for only a rugged group of sailors taking care of it.  " +
      "However, the lack of obstructions gives the sailors free " +
      "roam of the ship without the worry of tripping about.\n");
    add_item(({"mast","main mast"}),
      "Sitting to the starboard, the main sail rises up into " +
      "the air.  Its sails are folded up and tied down, ready to " +
      "go the instant the need arises.\n");
    add_item(({"ropes","rope","coils"}),
      "Neatly coiled ropes are scattered about the deck, ready to " +
      "be used to tie off sails.\n");
    add_item("sails",
      "Stacks of neatly folded sails are scattered about the deck.\n");
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
    add_item(({"hatch","hatchway","door","trapdoor"}),
      "Large and bulky, this door leads down to the rooms inside " +
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

    add_exit(DROOM + "seeker07.c","fore",0);
    add_exit(DROOM + "seeker09.c","starboard",0);
    add_exit(DROOM + "seeker13.c","aft",0);
} 