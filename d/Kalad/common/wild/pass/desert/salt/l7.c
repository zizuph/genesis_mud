inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("End of passageway");
   set_long("The sound of dripping water reaches your ears, sounding "+
      "an eerie cadence within this darkened passage. The passageway ends "+
      "here at a stone door, which blocks the way to the northwest. The "+
      "passage continues to the south, heading into inky darkness. "+
      "Numerous stalagmites and stalactites litter the area, making travel "+
      "somewhat dangerous.\n");
   add_item(({"darkened passage","passage","passageway","area"}),"This "+
      "underground tunnel seems to have been created through the natural "+
      "process of water erosion. As a result, numerous stalagmites and "+
      "stalactites abound in the passage.\n");
   add_item(({"inky darkness","darkness"}),"A blackness darker even than the "+
      "darkest of moonless nights.\n");
   add_item(({"stalagmites","stalactites","stalagmite","stalactite"}),
      "They are all over the passage, forcing you to watch your step, "+
      "lest you step on a stalagmite and injure yourself.\n");
   add_exit(CPASS(desert/salt/l8),"south","@@hurt",1,2);
   clone_object("/d/Kalad/common/wild/pass/obj/ldoor2")->move(TO);
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
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/liz_man");
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A lone lizard man emerges from the darkness.\n");
   }
}
