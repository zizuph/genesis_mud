/* /d/Ansalon/goodlund/nethosak/docks/room/seeker14.c
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
      "deck.  Directly to the port " +
      "the mizzen mast stretches up overhead, its sails folded up.  " +
      "Beside the mizzen mast is the wheel of the ship, currently " +
      "unmanned. " +
      "A set of steps head down to the main deck to the fore.\n");

    add_item(({"deck","aft deck"}),
      "Extremely clean and free of any litter, the aft deck is too " +
      "clean for only a rugged group of sailors taking care of it.  " +
      "However, the lack of obstructions gives the sailors free " +
      "roam of the ship without the worry of tripping about.\n");
    add_item(({"mast","mizzen mast"}),
      "Sitting to the port, the mizzen mast rises up into " +
      "the air.  Its sails are folded up and tied down, ready to " +
      "go the instant the need arises.\n");
    add_item("wheel",
      "Currently, the wheel of the ship is unmanned.  Almost " +
      "a good 5 feet in diameter, it takes a very large " +
      "individual to man the wheel.\n");
    add_item(({"ropes","rope","coils"}),
      "Neatly coiled ropes are scattered about the deck, ready to " +
      "be used to tie off sails.\n");
    add_item("sails",
      "Stacks of neatly folded sails are scattered about the deck.\n");
    add_item("steps",
      "Made for minotaurs, these sturdy steps leave quite a " +
      "challenge for the smaller races.\n");
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
    add_item("buildings",
      "These massive buildings of stone are spread throughout the " +
      "city.  However, two of them stand out as the most grandiose " +
      "and vast.  One, is a large stone arena styled in that of an " +
      "large amphitheater.  The other is a large domed structure " +
      "covered in statues and carvings.\n");
    add_item("city",
      "The city stretches out to the north and east, the end of it " +
      "hidden by the mass of structures that clutter this city.  " +
      "All the buildings appear to be of the greatest workmanship and " +
      "labor that could be afforded.  However, a smoggish brown " +
      "undertones everything, giving the city a look of neglect\n");
    add_item("ballista",
      "Loaded with a large wooden harpoon, the ballista stands " +
      "ready to be fired.  The blood sea holds many malicious creatures " +
      "other than pirates, that are best kept dissuaded from munching " +
      "on the ships.\n");
    add_item("main deck",
      "A good twenty feet below the aft deck, the only way to " +
      "to get there is via two sets of steps.  One set is here " +
      "and the other can be seen on the port side of the ship.\n");
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

    add_exit(DROOM + "seeker11","fore","@@steps");
    add_exit(DROOM + "seeker15","port",0);
    add_exit(DROOM + "seeker17","aft",0);
}

int steps()
{
   write("You climb down the huge steps.\n");
   return 0;
}