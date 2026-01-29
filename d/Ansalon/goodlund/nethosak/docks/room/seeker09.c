/* /d/Ansalon/goodlund/nethosak/docks/room/seeker09.c
   Glain
   11/7/98
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <macros.h>

inherit NETHOSAK_OUT;

void create_nethosak_room()
{
    set_short("Main deck of Storm Seeker");
    set_long(
      "Coils of rope and folded sails clutter the main deck of this " + 
      "small sailing ship.  Strong gusts of wind blow across the " +
      "deck keeping the stench of the city to itself.  Bursting " +
      "from the deck the main mast rises up, its sails folded up " +
      "and tied down.  High above, at the top of the main mast, you " +
      "can see the lookout, accessible only by climbing a multitude " +
      "of ropes and nets that cling to the mast.\n");

    add_item(({"deck","main deck"}),
      "Extremely clean and free of any litter, the main deck is too " +
      "clean for only a rugged group of sailors taking care of it.  " +
      "However, the lack of obstructions gives the sailors free " +
      "roam of the ship with the worry of tripping about.\n");
    add_item(({"mast","main mast"}),
      "Rising high above, the main mast creaks and groans as it sways " +
      "in the strong winds.  Its sails are folded up and tied down, " +
      "ready to go the instant the need arises.  At the top of the " +
      "mast is the lookout,  accessible only by climbing a " +
      "multitude of ropes and nets that cling to the mast.  Here, " +
      "on the deck, a number of nets and ropes have been tied " +
      "around the mast.  Coupled with the blood stains surrounding " +
      "the mast, you realize this is where flogging is practiced " +
      "on the less fortunate.\n");
    add_item(({"lookout","nest"}),
      "Sitting on top of the main mast is the lookout nest.  Not " +
      "much can be made out at this point of view, other then it " +
      "has been sturdily made to withstand the harsh winds of the " +
      "Blood Sea.  Apparently, the only way there is by climbing " +
      "the main mast with the aid of the multitude of ropes and " +
      "nets that cling to it.\n");
    add_item("nets",
      "Clinging to the main mast, these old nets look far from " +
      "the sturdy climbing aid that they are used for.\n");
    add_item("chains",
      "These sturdy iron chains are used to hold down the " +
      "struggling victim of a flogging.\n");
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

    add_cmd_item(({"mast","main mast","up mast","up main mast"}),
       "climb","@@climb_mast");

    add_exit(DROOM + "seeker06.c","fore",0);
    add_exit(DROOM + "seeker08.c","starboard",0);
    add_exit(DROOM + "seeker10.c","port",0);
    add_exit(DROOM + "seeker12.c","aft",0);
} 

string climb_mast()
{
   if(TP->query_skill(SS_CLIMB) < 10)
   {
      write("Your head spins and your stomach turns as you think of " +
         "trying to climb the mast in these strong winds.\n");
      return "";
   }
    
   write("You climb up the main mast, using the ropes and nets to " +
      "to help you up.\n");
   say(QCTNAME(TP) + "climbs up the main mast.\n");
   tell_room(DROOM + "mast01",QCNAME(TP) + " enters, climbing up " +
      "the mast.\n");
   TP->move_living("up the main mast",DROOM + "mast01",1,0);
   return "";
}