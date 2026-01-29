inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("A large, oval chamber");
   set_long("A large, oval chamber.\n"+
      "This entire chamber is composed not of rock and stone, but pure "+
      "crystal. The myriad surfaces of the crystal seem to catch, reflect "+
      "and intensify the light given off by the radiant red orb that lies "+
      "floating at the exact center of the chamber. The only break within "+
      "the crystalline chamber is a dark passage that leads north, back "+
      "towards the chasm. Besides the orb, the only other items within the "+
      "chamber are several huge heaps of bones.\n");
   add_item(({"large chamber","oval chamber","crystalline chamber","chamber"}),
      "This huge area is composed entirely out of flawless crystal.\n");
   add_item(({"flawless crystal","pure crystal","crystal"}),
      "Multi-faceted glittering objects whose beauty rivals that of the "+
      "most precious of gems.\n");
   add_item(({"radiant red orb","radiant orb","red orb","orb"}),
      "A red crystalline orb whose eerie radiance seems to compel you to "+
      "touch it, so great is its attractiveness.\n");
   add_item(({"dark passage","passage"}),
      "A gaping, black hole leading to the north.\n");
   add_item(({"huge heaps of bones","huge heaps","huge heap","heap","heaps","bones","bone"}),
      "Great mounds of bones that rise well over thirty feet in height, the "+
      "bones themselves appear to come from several different races, including "+
      "humans, elves, dwarves and a few others that are unrecognizable.\n");
   add_exit(CPASS(uc/d3),"north","@@msg",2,1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(uc/npc/gem_dragon));
      ob1 -> move_living("M",TO);
      tell_room(TO,"From behind a huge heap of bones emerges the most magnificent "+
         "creature you've ever laid eyes on.\n");
   }
}
void
init()
{
   ::init();
   AA(touch,touch);
}
int
touch(string str)
{
   if(!str || str != "orb")
      {
      NF("Touch what? The orb?\n");
      return 0;
   }
   write("You touch the radiant red orb.\n");
   say(QCTNAME(TP) + " touches the radiant red orb.\n");
   set_alarm(1.0,0.0,"do_move");
   return 1;
}
void
do_move()
{
   TP->move_living("into a black, choking mist","/d/Kalad/common/wild/pass/uc/d7");
   return;
}
msg()
{
   write("The eerie echo of bones crunching resounds as you move.\n");
   return 0;
}
