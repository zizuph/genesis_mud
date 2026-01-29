inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
public void
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Moist tunnel");
   set_long("The echo of water dripping from far off reaches your ears from "+
      "all angles, confusing you as to its true location. The passage you "+
      "are travelling along branches here. One passage heads off to the west "+
      "while the other one travels northeast into inky darkness. "+
      "Various stalagmites and stalactites abound in the passageway, "+
      "restricting your movement somewhat.\n");
   add_item(({"passage","passageway"}),"This moist environment has helped "+
      "create a number of stalagmites and stalactites, which hinder speedy "+
      "movement through this area. The ground beneath thuds with your every "+
      "step.\n");
   add_item(({"ground"}),"Despite looking quite sturdy, it seems to "+
      "possess an odd, almost hollow quality.\n");
   add_item(({"inky darkness","darkness"}),"A lightlessness that you "+
      "thought was only possible in your dreams.\n");
   add_item(({"stalagmites","stalactites","stalagmite","stalactite"}),
      "The natural rock formations litter this passageway, hindering "+
      "your movement.\n");
   add_prop(OBJ_S_SEARCH_FUN,"search_ground");
   add_exit(CPASS(desert/salt/l2),"west","@@hurt",1,2);
   add_exit(CPASS(desert/salt/l4),"northeast","@@hurt",1,2);
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
public string
search_ground(object me, string arg)
{
   if(arg != "ground")
      return "";
   if(TP->query_skill(SS_AWARENESS) < 45)
      return "";
   add_exit(CPASS(desert/salt/l10),"down",0);
   set_alarm(10.0,0.0,"remove_exit","down");
   return "You search carefully and discover a way down.\n";
}
