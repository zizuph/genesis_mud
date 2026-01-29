/*
 * 2k9.c
 * Second Floor room, Telberin Castle, near the courtroom.
 * - Alaron November 1996
 */

#include <macros.h>
#include "default.h"

inherit CASTLE_ROOM;

void reset_room();

string
sir_or_madam()
{
    if (TP->query_gender()==G_MALE) return "sir";
    else return "madam";
}

void
create_room()
{
   ::create_room();
   set_short("Hallway outside the Telberin Courtroom");
   set_long("   You are standing before a large set of mahogany double-doors. They "+
	"reach several feet above your head, dominating the entire end of this corridor. The "+
	"doors seem to ooze authority. Their shape and intricate carving simply radiates "+
	"the feeling of power and wisdom which rests beyond this gateway. The walls are "+
	"made of a softly glowing, emerald stone. The soft, green glow drapes the stone "+
	"floor and everyone in the hallway. The traffic of people milling about here "+
	"is heavy, thinning out to the east as the hallway heads away from the "+
	"courtroom. Loud, animated voices penetrate the thick, wooden doors which "+
	"separate the courtroom from the rest of the castle.\n\n");
	
   add_item( ({"doors", "mahogany doors", "double doors", "double-doors",
	       "mahogany double-doors", "door", "mahogany", "wood", "wooden doors",
               "carving", "gateway"}),
	    "The mahogany double-doors are incredible. They tower high above your "+
	    "head, dominating this end of the large hallway. You can hear loud, "+
	    "animated voices on the other side of the doors. Obviously the legend of "+
	    "elves always being calm and collected has its exception in the elven "+
            "judicial system.\n");

   add_item( ({"court", "courtroom"}),
	    "The courtroom can't be seen from here, but you can certainly here the "+
            "members of court loudly and fervently debating the issues beyond the "+
            "massive wooden barrier.\n");
 
   
   add_exit(CASTLE_DIR + "th1","west","@@west_block@@");
   add_exit(CASTLE_DIR + "2k8","east", 0);
   
   set_alarm(1.0, 0.0, reset_room);
}


west_block()
{
   object guard;
   
   guard = present("guard");
   
   if(guard && guard->query_name()!= "corpse")
   {
      if (TP->query_race_name() != "elf")
      {
	   tell_room(TO,
                     "The guard pushes "+QTNAME(TP)+" backwards.\n",TP);
           TP->catch_msg("The guard pushes you backwards.\n");
           tell_room(TO,process_string(
                     "The guard says: This is an elven courtroom, @@sir_or_madam@@. "+
                     "None but elves may enter.\n"));
	   return 1;
      }
      if (TP->query_alignment() < -160)
      {
           tell_room(TO,
                     "The guard pushes "+QTNAME(TP)+ " back  threateningly.\n", TP);
           TP->catch_msg("The guard pushes you back threateningly.\n");
           tell_room(TO, process_string(
                     "The guard says: You have the look of a criminal about you, @@sir_or_madam@@. You "+
                     "will not be allowed into court this day, unless you plan on "+
                     "breaking the law soon.\n"));
           return 1;
     }
   }

   write("You pull on the heavy wooden door and step into the courtroom. The weight of the "+
	 "heavy door causes it to slam shut behind you ... \n\n");
   say(QCTNAME(TP)+" pulls on the heavy wooden door and steps through into the courtroom. The "+
       "weight of the heavy door causes it to slam shut behind "+TP->query_objective()+".\n");
         
   return 0;
}

void
reset_room()
{
   object guard;
   
   guard = present("guard");
   if(guard && guard->query_name()!="ghost")
      return;
   else
      guard = clone_object("/d/Emerald/telberin/castle/npc/c_guard"); 
   guard->arm_me();
   guard->move_living("into a room", this_object());
}
