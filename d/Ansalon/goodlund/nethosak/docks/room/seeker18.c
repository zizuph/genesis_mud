/* /d/Ansalon/goodlund/nethosak/docks/room/seeker18.c
   Glain
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

inherit NETHOSAK_OUT;

void create_nethosak_room()
{
    set_short("Aft deck of Storm Seeker");
    set_long(
      "Coils of rope and folded sails clutter the aft deck of this small " +
      "sailing ship.  Strong gusts of wind blow across the deck " +
      "keeping the stench of the city to itself.  The docks directly below " +
      "are full of activity, where cargo is being loaded off and on " +
      "other docked ships.  Massive buildings made of stone rise " +
      "up throughout the sprawling city that stretches to the east and " +
      "north.  A large ballista has been mounted here, in the very  " +
      "aft of the ship.  Directly to the fore the mizzen mast stretches up " +
      "overhead, its sails folded up.   Behind the mizzen mast you " +
      "make out the wheel of the ship, curently unmanned.\n");

    add_item(({"deck","aft deck"}),
      "Extremely clean and free of any litter, the aft deck is too " +
      "clean for only a rugged group of sailors taking care of it.  " +
      "However, the lack of obstructions gives the sailors free " +
      "roam of the ship with the worry of tripping about.\n");
    add_item(({"mast","mizzen mast"}),
      "Sitting to the fore, the mizzen mast rises up into " +
      "the air.  Its sails are folded up and tied down, ready to " +
      "go the instant the need arises.\n");
   add_item(({"ropes","rope","coils"}),
      "Neatly coiled ropes are scattered about the deck, ready to " +
      "be used to tie off sails.\n");
    add_item("sails",
      "Stacks of neatly folded sails are scattered about the deck.\n");
    add_item("railing",
      "Looking over the aft railing the docks can be " +
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
    add_item("buildings",
      "These massive buildings of stone are spread throughout the " +
      "city.  However, two of them stand out as the most grandiose " +
      "and vast.  One, is a large stone arena styled in that of an " +
      "ancient ampitheater.  The other is a large domed structure " +
      "covered in statues and carvings.\n");
    add_item("city",
      "The city stretches out to the north and east, the end of it " +
      "hidden by the mass of structures that clutter this city.  " +
      "All the buildings appear to be of the greatest workmanship and " +
      "labor that could be afforded.  However, a smoggish brown " +
      "undertones everything, giving the city a look of neglect.\n");
    add_item("ballista",
      "Loaded with a large wooden harpoon, the ballista stands " +
      "ready to be fired.  The blood sea holds many malicious creatures " +
      "other than pirates, that are best kept dissuaded from munching " +
      "on the ships.\n");
    add_item("main deck",
      "A good twenty feet below the aft deck, the only way to " +
      "to get there is via two sets of steps, one on each side of the " +
      "ship, which lead down to the main deck.\n"); 
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

    add_exit(DROOM + "seeker15","fore",0);
    add_exit(DROOM + "seeker17","starboard",0);
    add_exit(DROOM + "seeker19","port",0);
}
