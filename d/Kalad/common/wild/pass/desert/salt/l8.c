inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Moist tunnel");
   set_long("The echo of water dripping from far off reaches your ears from "+
      "all angles, confusing you as to its true location. The passage you "+
      "are travelling down turns sharply here, heading towards the west, "+
      "north and southeast, all into inky darkness. A number of "+
      "stalagmites and stalactites are within the passageway, making "+
      "travel somewhat hazardous to the clumsy.\n");
   add_item(({"passage","passageway"}),"This moist environment has helped "+
      "create a number of stalagmites and stalactites, which hinder speedy "+
      "movement through this area.\n");
   add_item(({"inky darkness","darkness"}),"A lightlessness that you "+
      "thought was only possible in your dreams.\n");
   add_item(({"stalagmites","stalactites","stalagmite","stalactite"}),
      "The natural rock formations litter this passageway, hindering "+
      "your movement.\n");
   add_exit(CPASS(desert/salt/l9),"west","@@hurt",1,2);
   add_exit(CPASS(desert/salt/l7),"north","@@hurt",1,2);
   add_exit(CPASS(desert/salt/l11),"southeast","@@hurt",1,2);
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
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/liz_lead");
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A loud hiss alerts you to the presence of a lizard man.\n");
   }
}
