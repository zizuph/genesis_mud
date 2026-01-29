inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Within the bazaar, Undraeth");
   set_long("The bazaar of Undraeth.\n"+
      "This is the northern end of the bazaar, the very heart of Undraeth "+
      "where merchants from the length and breadth of the Dark Dominion "+
      "may trade in relative peace. Numerous multi-colored tents, some "+
      "decorated in faerie fire, others in a more mundane fashion, lie "+
      "all around you. The rest of the bazaar lies off to the southwest, "+
      "south and southeast.\n");
   add_item(({"bazaar"}),
      "It is where you are right now, look around.\n");
   add_item(({"undraeth","city"}),
      "It surrounds this relatively unforeboding area like a ring of "+
      "darkness waiting to crash upon a small sphere of light.\n");
   add_item(({"multi-colored tents","tents","tent"}),
      "Dozens of them lie scattered all over the bazaar.\n");
   add_exit(CPASS(drow/bazaar/b3),"southeast");
   add_exit(CPASS(drow/bazaar/b5),"south");
   add_exit(CPASS(drow/bazaar/b1),"southwest");
   set_noshow_obvious(1);
   set_alarm(3.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/rand_drow));
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"After a while, you notice a figure watching you nearby.\n");
   }
}
