/* /d/Ansalon/goodlund/nethosak/docks/room/mast01.c
   Glain
*/

#include "/d/Ansalon/goodlund/nethosak/local.h"
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include <ss_types.h>
#include <macros.h>

inherit NETHOSAK_OUT;

void create_nethosak_room()
{
    set_short("High up on the main mast");
    set_long(
       "The main mast slowly swings back and forth in the " +
       "strong winds.  Out to the port and starboard the crossbeam " +
       "streches, with the main sail tied and bundled onto it.  " +
       "A little farther up the mast is the lookout nest.  Nets and " +
       "ropes are strung about the mast.\n");  

    add_item(({"mast","main mast"}),
      "Rising high above, the main mast creaks and groans as it sways " +
      "in the strong winds.  Its sails are folded up and tied down, " +
      "ready to go the instant the need arises.  At the top of the " +
      "mast is the lookout,  accessible only by climbing a " +
      "multitude of ropes and nets that cling to the mast.  Here, " +
      "on the deck, a number of nets and ropes have been tied " +
      "around the mast.\n");
    add_item(({"lookout","nest"}),
      "Sitting on top of the main mast is the lookout nest.  Not " +
      "much can be made out at this point of view, other then it " +
      "has been sturdily made to withstand the harsh winds of the " +
      "Blood Sea.  Apparently, the only way there is by climbing " +
      "further up the main mast with the aid of the multitude of " +
      "ropes and nets that cling to it.\n");
    add_item("nets",
      "Clinging to the main mast, these old nets look far from " +
      "the sturdy climbing aid that they are used for.\n");
    add_item("ropes",
      "A number of ropes are tied around the main mast.  They " +
      "greatly aid the crew in traversing the main mast.\n");
    add_item("crossbeam",
      "The main sail drops from here to be tied down at its lower " +
      "end.  At the moment the sail is bundled up and tied down.\n");

    add_cmd_item(({"down","down mast","down main mast"}),
       "climb","@@climb_down");
    add_cmd_item(({"up","up mast","up main mast"}),
       "climb","@@climb_up");
}

string climb_down()
{    
   write("You climb down the main mast, using the ropes and nets to " +
      "to help you down.\n");
   say(QCTNAME(TP) + "climbs down the mast.\n");
   tell_room(DROOM + "stormseeker9",QCNAME(TP) + " enters, climbing " +
      "down the main mast.\n");
   TP->move_living("down the mast",DROOM + "stormseeker9",1,0);
   return "";
}

string climb_up()
{
   if(TP->query_skill(SS_CLIMB) < 20)
   {
      write("You climb up the mast, reach for a rope... but " +
         "instead grab air. You fall to the deck below.\n");
      say(QCTNAME(TP) + " climbs up the mast and tries to reach " +
         "for one of the ropes to the lookout, but misses.  " +
         QCTNAME(TP) + "plummets past you and smacks into the deck " +
         "below.\n");
      tell_room(DROOM + "stormseeker9",QCTNAME(TP) + " screaming, " +
         "comes crashing down onto the deck, from high up on the " +
         "main mast.\n");
      TP->move_living("down to the deck",DROOM + "stormseeker9",1,0);
      TP->heal_hp(-random(200));
      return "";
   }
    
   write("You climb up the mast, grab a nearby rope, and pull " +
      "yourself into the lookout nest.\n");
   say(QCTNAME(TP) + "climbs up the mast, and manages to reach the " +
      "lookout.\n");
   tell_room(DROOM + "nest01",QCNAME(TP) + " pulls himself into " +
      "the lookout.\n");
   TP->move_living("into the lookout",DROOM + "nest01",1,0);
   return "";
}  