inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Moist tunnel");
   set_long("The echo of water dripping from far off reaches your ears from "+
      "all angles, confusing you as to its true location. You've reached "+
      "a t-intersection between two passages, one passageway heading "+
      "east-west and another going to the south. Inky darkness fills this "+
      "place, reminding you of the depths of a bottomless pit. Many "+
      "stalagmites and stalactites abound in this place.\n");
   add_item(({"passage","passageway","place"}),"This moist environment has helped "+
      "create a number of stalagmites and stalactites, which hinder speedy "+
      "movement through this area.\n");
   add_item(({"inky darkness","darkness"}),"A lightlessness that you "+
      "thought was only possible in your dreams.\n");
   add_item(({"stalagmites","stalactites","stalagmite","stalactite"}),
      "The natural rock formations litter this passageway, hindering "+
      "your movement.\n");
   add_exit(CPASS(desert/salt/l10),"west","@@hurt",1,2);
   add_exit(CPASS(desert/salt/l8),"east","@@hurt",1,2);
   add_exit(CPASS(desert/salt/l12),"south","@@hurt",1,2);
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
