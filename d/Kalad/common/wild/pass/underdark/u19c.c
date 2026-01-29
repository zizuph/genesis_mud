inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/ss_types.h"
#define HARD_TO_CLIMB 45
#define DAMAGE 150
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,0);
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Beast Pit");
   set_long("This darkened pit is filled with the skeletal remains of "+
      "many creatures, mostly humanoid from what you can ascertain. The walls of "+
      "the pit, while easy enough to climb down from, look extremely hard "+
      "to climb up, because of their steep angle and what appears to be "+
      "some slimy substance covering its surface.\n");
   add_item(({"skeletal remains","remains"}),"Discernible among the "+
      "various animal skeletons are the clear remnants of human beings. The bones "+
      "of many of the skeletons look like they have been chewed upon.\n");
   add_item(({"walls","wall"}),"It looks like a difficult climb back up.\n");
   add_item(({"slimy substance","substance"}),"A greenish slime that is "+
      "plastered over most of the side walls. It so thoroughly covers the "+
      "wall's surface that you can't tell if the slime was put on the wall "+
      "or if it is actually coming from the wall.\n");
    add_exit(CPASS(underdark/u19),"up", "@@climb",2);
   set_noshow_obvious(1);
   set_alarm(1.0, 0.0, "reset_room");
}
reset_room()
{
   if (!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/pitspider");
      ob1 -> move_living("xxx", TO);
   }
}
climb()
{
   if(TP->query_skill(SS_CLIMB) < random(HARD_TO_CLIMB))
      {
      write("You slip while trying to climb up the slippery walls and fall "+
         "down.\n");
      write("You slam into a pile of bones!\n");
      TP->heal_hp(-DAMAGE);
      say(QCTNAME(TP) + " fell down while trying to climb out of the pit.\n");
      say(QCTNAME(TP) + " slammed into a pile of bones!\n");
      return 1;
      if (TP->query_hp() < 1)
         TP->do_die(TO);
   }
   write("You manage to get out of the pit!\n");
   say(QCTNAME(TP) + " manages to climb out of the pit.\n");
   return 0;
}
