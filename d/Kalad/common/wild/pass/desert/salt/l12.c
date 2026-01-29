inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define LIZLEAD "/d/Kalad/common/wild/pass/npc/liz_lead"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Moist tunnel");
   set_long("The echo of water dripping from far off reaches your ears from "+
      "all angles, confusing you as to its true location. The passage you "+
      "are journeying along runs straight to the north and south, where "+
      "it leads into inky black darkness. A number of stalagmites and "+
      "stalactites litter the passageway.\n");
   add_item(({"passage","passageway"}),"This moist environment has helped "+
      "create a number of stalagmites and stalactites, which hinder speedy "+
      "movement through this area.\n");
   add_item(({"inky black darkness","inky darkness","black darkness","darkness"}),
      "A lightlessness that you thought was only possible in your dreams.\n");
   add_item(({"stalagmites","stalactites","stalagmite","stalactite"}),
      "The natural rock formations litter this passageway, hindering "+
      "your movement.\n");
   add_exit(CPASS(desert/salt/l9),"north","@@hurt",1,2);
   add_exit(CPASS(desert/salt/l13),"south","@@hurt",1,2);
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
      ob1 = clone_object(LIZLEAD);
      ob1 -> my_stuff();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(LIZLEAD);
      ob2 -> my_stuff();
      ob2 -> move_living("M",TO);
      tell_room(TO,"A serie of hisses alerts you to the presence of two lizard men.\n");
      ob1 -> team_join(ob2);
   }
}
