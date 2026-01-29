/* File         : /d/Khalakhor/se_speir/rannoch/room/b_14.c
 * Creator      : Darragh@Genesis
 * Date         : 00-09-22      
 * Purpose      : Map room file of the Loch Rannoch area.
 * Related Files: 
 * Comments     :
 * Modifications: Almost completely rewritten 01-03-22
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "room.h"

inherit ROAD_BASEFILE;

#define HERE "/d/Khalakhor/se_speir/rannoch/road/b_14.c"

string climb_wall();
int knock_gate();
int entry();

string
climb_wall()
{
   if (TP->query_base_skill(SS_CLIMB) <= 30)
   {
      return "You do not even know where to start climbing, "
           + "as you are lacking the training needed. However, "
           + "the wall look awfully high, and you doubt you "
           + "could climb it, ever.\n";

      say(QCTNAME(this_player())+ " stares at the wall for a "
                                + "short while.\n");
   }

   else
   {
      return "You can not even seem to find a reliable foothold "
           + "or grip, climbing up this wall seems hopeless. Even "
           + "if you made it to the top, the sharpened tops of the "
           + "poles could inflict some serious harm.\n";

      say(QCTNAME(this_player())+ " studies the wall closely, as "
                                + "if trying to find a way to climb it.\n");
   }
}

int
knock_gate()
{

   write("You knock on the gate.\n");

   say("You watch as " + QTNAME(this_player()) + " knocks on the gate.\n");

   set_alarm(4.5,0.0,&entry());

   return 1;
}

int
entry()
{

   tell_room(TO, "Someone shouts from the other side of the gate:\n\n"
       + "- Sorry, we don't welcome strangers! Off with ye!\n");



   return 1;
}
   
public void
create_khalakhor_room()
{

   create_loch_room();

   add_item(({"wall","wooden wall","village wall"}),
              "The wall is about ten feet high, made of thick, "
            + "sturdy wooden poles shoved deep into the ground. "
            + "The tops of the poles have been sharpened, in order "
            + "to discourage any trespassers. This is where the gate "
            + "through the wall is, and it is closed at the moment. "
            + "The wall runs north and south into the woods. On top "
            + "of the wall, on the left side of the gate, there is "
            + "a crimson and green banner hanging from a pole.\n");
   add_item(({"poles","thick poles","sturdy poles","wooden poles"}),
              "The poles of the wall, look like tree trunks, shoved "
            + "into the ground. They do not look very special, at least "
            + "not from this side. The top of each pole has been sharpened, "
            + "to prevent anyone from climbing over it.\n");
   add_item(({"gate","wooden gate","village gate","sturdy gate",
              "strong gate","high gate"}),
              "The gate is made of massive oak, reinforced with "
            + "iron. It has been painted black. You do not see "
            + "any latch or handle from this side, and it is "
            + "probably barred from the inside.\n");
   add_item(({"pole","flagpole"}),
              "It is just a wooden pole, fastened to the top of "
            + "the wall, just left of the gate. A banner hangs from it.\n");
   add_item(({"banner","flag"}),
              "The banner is crimson and green, and displays a crest "
            + "depicting a lion resting upon two crossed axes within "
            + "a belted circle.\n"); 

   add_cmd_item(({"wall","the wall","over wall","over the wall",
                  "wooden wall","the wooden wall","over wooden wall",
                  "over the wooden wall","village wall",
                  "the village wall","over village wall",
                  "over the village wall"}),
                  "climb",
                   climb_wall);
   add_cmd_item(({"gate","village gate","sturdy gate"}),
                ({"climb","scale"}),
                  "The gate is even higher than the wall, and is "
                + "more sheer. You can not climb over it.\n");
   add_cmd_item(({"gate","the gate","on the gate"}),
                  "knock",
                  knock_gate); 
   add_cmd_item("gate",
                "open",
                "The gate is locked and does not even move the slightest.\n");

   add_exit(ROOM + "b_13.c","west",0,1,1);
   add_exit(ROOM + "a_13.c","northwest",0,1,1);
   add_exit(ROOM + "a_14.c","north",0,1,1);
   add_exit(ROOM + "c_14.c","south",0,1,0);
   add_exit(ROAD + "c_13.c","southwest",0,1,0);

   set_short("In front a gate");
   set_long(query_long() + "The road ends here in front of a high "
                         + "wooden wall stretching from the north "
                         + "and to the water southwards. Right before "
                         + "you to the east is a strong gate set in "
                         + "the wall, and there is a banner hanging "
                         + "from a pole on top of the wall.\n");

   create_room_tells();

}

void
create_room_tells()
{

   add_tell(({"The trees sway and groan when a sudden wind comes in "
            + "from the east, sweeps along the road, and fades away.\n",
              "You hear something moving in the woods behind you.\n",
              "A leaf falls gently to the ground.\n",
              "A gentle breeze rustles the foliage above, sending a "
            + "few leaves to the ground.\n",
              "The banner flaps in the wind.\n",
              "You can vaguely hear the sound of voices speaking on "
            + "the other side of the gate.\n",
              "You hear some shouting coming from inside the wall.\n",
              "You hear the sound of deep laughter from the other side "
            + "of the wall.\n",}));

   set_tell_time(450);
}