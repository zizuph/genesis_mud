inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("The main hall of House Noquar");
   set_long("This is the main hall of House Noquar.\n"+
      "Numerous adamantine pillars line the northern and southern walls of "+
      "this long, rectangular passageway. Enscribed onto them are a myriad "+
      "amount of faerie fire decorations, casting this hall into an eerie, "+
      "multi-colored glow. A burgundy-colored carpet runs the length of "+
      "the floor, from the west where it dissappears into a black archway to "+
      "the east where it dissappears into a similarly darkened archway. The "+
      "regular intervals of the pillars is broken only by a third archway, "+
      "that is located in the southern wall.\n");
   add_item(({"ceiling"}),
      "A great mass of rock, it is solidly supported by the many adamantine "+
      "pillars lining this hall.\n");
   add_item(({"main hall","hall"}),
      "A long passageway which you are presently inside of.\n");
   add_item(({"adamantine pillars","pillars","adamantine pillar","pillar"}),
      "Immensely durable supports that keep the tremendous weight of the "+
      "ceiling from crashing in upon the occupants of this compound.\n");
   add_item(({"northern wall","southern wall","wall","walls"}),
      "The black, smooth surface is cold and unyielding to the touch. "+
      "Numerous pillars are lined up before it.\n");
   add_item(({"long passageway","rectangular passageway","passageway"}),
      "A corridor that stretches to the west and east.\n");
   add_item(({"faerie fire decorations","decorations","faerie fire","fire","decoration"}),
      "Images created through the use of varying hues of magical fire that "+
      "depict weapon-wielding drow in close combat with svirfnebli, or deep "+
      "gnomes as they are more commonly called.\n");
   add_item(({"burgundy-colored carpet","carpet"}),
      "It stretches for several dozen feet from the west to the east, "+
      "appearing as if the blood of many gnomes had soaked into it.\n");
   add_item(({"black archway"}),
      "A portal of darkness in the west.\n");
   add_item(({"darkened archway",}),
      "A portal of darkness in the east.\n");
   add_item(({"third archway"}),
      "An archway, just like the ones in the west and east that is situated "+
      "in the southern wall.\n");
   add_item(({"archway"}),
      "Which one?\n");
   add_exit(CPASS(drow/house8/entrance),"west","@@msg",-1,-1);
   add_exit(CPASS(drow/house8/mm_chamber),"east","@@check",-1,-1);
   add_exit(CPASS(drow/house8/chapel),"south",0,-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/h8_hell_hound));
      ob1 -> move_living("M",TO);
      tell_room(TO,"A terrible hell hound arrives, trailing fire in its wake.\n");
   }
}
check()
{
   if(present(ob1,TO) &&
         TP->query_subloc_obj("_h8_insignia") == 0)
   {
      write("The terrible hell hound moves and blocks your path!\n");
      say(QCTNAME(TP) + " tries to go east but is stopped by the terrible hell hound!\n");
      return 1;
   }
   else
      msg();
}
msg()
{
   write("You enter the black archway...\n");
   say(QCTNAME(TP) + " enters the black archway...\n");
   return 0;
}
