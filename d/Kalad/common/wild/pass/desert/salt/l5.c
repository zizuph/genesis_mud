inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Moist chamber");
   set_long("The echo of water dripping from far off reaches your ears from "+
      "all angles, confusing you as to its true location. The passage "+
      "from the south ends here in a small oval chamber. Like a gaping "+
      "bloody wound, a gaping black hole lies in the center of the floor. "+
      "Several stalagmites and stalactites are littered around the chamber, "+
      "particularly around the hole, giving the impression of a giant "+
      "tooth-filled maw.\n");
   add_item(({"passage"}),"A dark, foreboding tunnel that leads out of "+
      "this chamber.\n");
   add_item(({"here","small oval chamber","small chamber","oval chamber","chamber"}),
      "A natural cavity within the rock strata, it appears to have been "+
      "formed via water erosion.\n");
   add_item(({"gaping black hole","gaping hole","black hole","hole"}),
      "A yawning pit that leads down beyond your sight.\n");
   add_item(({"floor"}),"It is littered with stalagmites and has a "+
      "gaping hole in its center.\n");
   add_item(({"stalagmites","stalactites","stalagmite","stalactite"}),
      "Formed through the process of water erosion, the rock structures "+
      "hinder your movement around this chamber, forcing you to watch "+
      "your step, lest you impale your foot upon a rogue stalagmite.\n");
   add_item(({"darkness"}),"A lightlessness you thought was only "+
      "possible in the realm of dreams.\n");
   add_exit(CPASS(desert/salt/l4),"south","@@hurt",1,2);
   add_exit(CPASS(desert/salt/l6),"down","@@pain",2,2);
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
pain()
{
   if(TP->query_skill(SS_CLIMB) < 50)
      {
      write("You try to climb down safely...\n");
      write("But instead you fall all the way down!!!\n");
      say(QCTNAME(TP) + " tried to climb down safely but instead falls all "+
         "the way down the hole!!\n");
      TP->heal_hp(-500);
      return 0;
   }
   write("You manage to climb down safely.\n");
   say(QCTNAME(TP) + " manages to climb down safely.\n");
   return 0;
}
