/* /d/Ansalon/goodlund/nethosak/docks/room/barracks01.c
   Glain
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit NETHOSAK_OUT;

void create_nethosak_room()
{
    set_short("Crew barracks on the Storm Seeker");
    set_long(
      "Four sets of large bunks stick out from the walls, two sets " +
      "on each wall.  The stench from the bunks is almost too much " +
      "to bear.   Under each set of bunks are two locked metal foot " +
      "lockers.  The floor is slightly slanted to the aft so that " +
      "water can collect in the bilge room.  Further to the fore " +
      "there are a two more bunks all by themselves.  Two hatchways " +
      "to the aft allow access to the deck above.\n");

    add_item("bunks",
      "Two sets of double bunks line each side of the wall.  There " +
      "is no padding or covers on the bunks, just a wooden slab " +
      "sticking out of the wall.  Under each set of bunks are two " +
      "metal foot lockers, each locked securely.\n"); 
    add_item("floor",
      "Scrubbed clean, the wooden floor is in perfect condition.  It " +
      "has a slight slant to the left, so that water from above may " +
      "collect in the bilge room, to later be pumped out of the " +
      "ship.\n");
    add_item(({"bilge","bilge room"}),
      "All the way in the back of the ship the bilge pumps sit.  " +
      "Water that manages to find its way below deck collects in " +
      "the bilge room to be pumped back out.\n");
    add_item("deck",
      "Being below deck and all makes it hard to check out the " +
      "deck above.\n");
    add_item("stench",
      "The stench coming from the bunks brings back memories of " +
      "growing up on the farm.\n");
    add_item(({"hatch","hatchway","door","trapdoor","hatches"}),
      "Large and bulky, the hatches lead back up to the main deck.\n"); 

    add_exit(DROOM + "barracks02.c","fore",0);
    add_exit(DROOM + "bdeck01.c","aft",0);
} 