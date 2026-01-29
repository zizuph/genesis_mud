inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Large oval chamber");
   set_long("You are within the center of a large oval chamber, the "+
      "echoing sounds of dripping water rebounding across the open "+
      "expanse, confusing you as to its exact source. Numerous bones and "+
      "filth litter this chamber, intermixed with the many stalagmites and "+
      "stalactites common to such moist, underground areas. An ink dark passage "+
      "exits the area to the northwest.\n");
   add_item(({"large oval chamber","large chamber","oval chamber","chamber"}),
      "A large, natural cavity within the surrounding rock structure, that "+
      "seems to have been formed via the process of water erosion. This "+
      "would appear to account for the large formations of stalagmites "+
      "and stalactites.\n");
   add_item(({"large formations","formations","large formation","formation","stalagmites","stalagmite","stalacites","stalactite"}),
      "Large structures hanging from the ceiling and rising from the ground, "+
      "formed from calcite deposits made by water erosion.\n");
   add_item(({"bones","bone"}),"The chewed and gnawed bones of human "+
      "and demihuman beings! They litter the entire chamber!\n");
   add_item(({"filth"}),"The still wet fecal remains of some large creature. "+
      "Its smell is overpowering.\n");
   add_item(({"ceiling"}),"It is covered with bristling stalactites.\n");
   add_item(({"ground"}),"It is covered with bristling stalagmites, "+
      "along with many bones and other filth.\n");
   add_item(({"ink dark passage","dark passage","passage"}),"It looks like "+
      "the only way out of this chamber.\n");
   add_item(({"darkness"}),"A stygion blackness reminiscent of the deepest "+
      "pit of hell.\n");
   add_exit(CPASS(desert/salt/l8),"northwest","@@hurt",1,2);
   set_alarm(1.0,0.0,"reset_room");
}
hurt()
{
   if(TP->query_base_stat(SS_DEX) < 50)
      {
      write("You stepped on a stalagmite! Ouch!\n");
      say(QCTNAME(TP) + " stepped on a stalagmite!\n");
      TP->heal_hp(-100);
      return 0;
   }
   write("You manage not to step on any stalagmites.\n");
   return 0;
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/liz_king");
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A bestial lizard man alerts you to his presence by "+
         "hissing loudly.\n");
   }
}
