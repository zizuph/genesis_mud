/* /d/Ansalon/goodlund/nethosak/docks/room/seeker15.c
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
      "keeping the stench of the city to itself.  The docks below " +
      "are full of activity, where cargo is being loaded off and on " +
      "other docked ships.  Massive buildings made of stone rise " +
      "up throughout the sprawling city that stretches to the east and " +
      "north.  At the very aft of the ship a ballista is mounted on the " +
      "deck.  Bursting from the deck the mizzen mast rises up, its " +
      "sails folded up and tied down.  Next to the mizzen mast is the " +
      "wheel of the ship, currently unmanned.\n");

    add_item(({"deck","aft deck"}),
      "Extremely clean and free of any litter, the aft deck is too " +
      "clean for only a rugged group of sailors taking care of it.  " +
      "However, the lack of obstructions gives the sailors free " +
      "roam of the ship without the worry of tripping about.\n");
    add_item(({"mast","mizzen mast"}),
      "Rising high above, the mizzen mast creaks and groans as it sways " +
      "in the strong winds.  Its sails are folded up and tied down, " +
      "ready to go the instant the need arises.\n");
    add_item("wheel",
      "The wheel of the ship is currently unmanned.  It has been " +
      "locked in place with a large wooden pole stuck through the " +
      "wheel and fastened down on one end with a large padlock.  " +
      "Almost a good 5 feet in diameter, it takes a very large " +
      "individual to man the wheel.\n");
    add_item(({"ropes","rope","coils"}),
      "Neatly coiled ropes are scattered about the deck, ready to " +
      "be used to tie off sails.\n");
    add_item("sails",
      "Stacks of neatly folded sails are scattered about the deck.\n");
    add_item("steps",
      "Made for minotaurs, these sturdy steps leave quite a " +
      "challenge for the smaller races.\n");
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

    add_exit(DROOM + "seeker14","starboard",0);
    add_exit(DROOM + "seeker16","port",0);
    add_exit(DROOM + "seeker18","aft",0);
}
