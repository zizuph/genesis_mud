/* /d/Ansalon/goodlund/nethosak/docks/room/bdeck01.c
   Glain
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit NETHOSAK_OUT;

void create_nethosak_room()
{
    set_short("Below deck on the Storm Seeker");
    set_long(
      "Clean and spacious, this small room below deck leads to " +
      "other sections of the ship below, serving as a juntion point.  " +
      "The smooth wooden floor is slightly slanted to the aft so " +
      "that water may collect in the bilge room.  From the fore the " +
      "stench of the crews' barracks pours out.  Sets of steps on " +
      "both sides lead up through a hatchway to the main deck above.\n");

    add_item("floor",
      "Scrubbed clean, the wooden floor is in perfect condition.  It " +
      "has a slight slant to the left, so that water from above may " +
      "collect in the bilge room, to later be pumped out of the " +
      "ship.\n");
    add_item(({"bilge","bilge room"}),
      "All the way in the back of the ship the bilge pumps sit.  " +
      "Water that manages to find its way below deck collects in " +
      "the bilge room to be pumped back out.\n");
    add_item("barracks",
      "Up ahead to the fore of the ship, the minotaur crew has its " +
      "barracks.  The only things that can really be made out in the " +
      "the dim lighting are the double bunks that are attached to " +
      "the walls, and the overwhelming stench.\n");  
    add_item("main deck",
      "Being below deck and all makes it hard to check out the main " +
      "deck.\n");
    add_item("stench",
      "The stench coming from the barracks brings back memories of " +
      "growing up on the farm.\n");
    add_item(({"hatch","hatchway","door","trapdoor","hatches"}),
      "Large and bulky, the hatches lead back up to the main deck.\n"); 
    add_item("steps",
      "Made for minotaurs, these sturdy steps leave quite a " +
      "challenge for the smaller races.\n");

    add_exit(DROOM + "barracks01.c","fore",0);
    add_exit(DROOM + "seeker08.c","starboard",0);
    add_exit(DROOM + "seeker10.c","port",0);
    add_exit(DROOM + "cargo01.c","aft",0);
} 