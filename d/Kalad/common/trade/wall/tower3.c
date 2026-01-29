inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Milashk, modified by Antharanos */

void
create_room()
{
   ::create_room();
   set_short("Guard Tower");
   set_long("This is the top of the tower. Around you are battlements, "
      +"as well as a view of the entire city of Kabal. There is "
      +"an iron ring planted into the stone wall on the east side "
      +"of the tower.\n");
   add_exit(TRADE(wall/tower2),"down");
   add_item(({"ring"}),"This is a heavy iron ring that has been bolted to "+
      "the side of the stone wall.\n");
   add_item(({"stone wall","wall"}),"A solid wall built of granite mined "+
      "from the Hespyre mountains.\n");
   hear_bell = 1;
   INSIDE;
   add_prop(ROOM_NO_TIME_DESC,1);
   set_alarm(1.0,0.0,"reset_room");
}

void
reset_room()
{
   if (!ob1)
   {
      ob1 = clone_object("/d/Kalad/common/trade/qguard.c");
      ob1 ->move_living("xxx", this_object());
   }
   /* This will make the NPC check whether he's got the locket or not. /Mercade */
   ob1->check_locket();
}
