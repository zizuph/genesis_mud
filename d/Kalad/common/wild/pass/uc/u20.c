inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
#define CHECK_DEX 30
#define DAMAGE 250
string long;
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("At the edge of a chasm");
   set_long("At the edge of a chasm.\n"+
      "A myriad amount of stone surrounds you from every conceivable angle, "+
      "seeming to promise any foolish enough to be here the cold of an "+
      "unmarked grave. Above you lies an incalculable amount of rock, forming an "+
      "insurmountable barrier between you and the sunlit realms of Kalad. "+
      "Just to the south lies an immense chasm, like the maw of some fell "+
      "beast gaping wide to swallow everything within its path. A thin, "+
      "stone bridge crosses the chasm, leading south until it reaches "+
      "the far side, which is just barely visible from here. The passage "+
      "you are in continues to the northwest.\n");
   add_item(({"edge"}),
      "A small shelf of rock upon which you stand, aside the chasm.\n");
   add_item(({"chasm","immense chasm"}),
      "A giant gash within the surface of this area. Darkness as deep as "+
      "death itself fills it. The cavern in which you are is quite large, "+
      "in contrast to the relatively narrow passages that make up this "+
      "subterranean area.\n");
   add_item(({"cavern"}),
      "A large open area, dominated by an immense chasm.\n");
   add_item(({"stone","rock"}),
      "It is unusually dark, seeming to absorb any light directed at you.\n");
   add_item(({"passage"}),
      "A tunnel located far beneath the sunlit lands of Kalad.\n");
   add_exit(CPASS(uc/u15),"northwest",0,2,1);
   add_exit(CPASS(uc/u29),"south",0,2,1);
}
check()
{
   if(TP->query_stat(SS_DEX) < random(CHECK_DEX))
      {
      write("You start to walk southwards...\n");
      write("You lose your balance and fall...\n");
      write("...down...\n");
      write("......down......\n");
      write(".........down until you slam into the ground with body-crushing force!\n");
      TP->move_living("falling into the chasm","/d/Kalad/common/wild/pass/uc/d1");
      TP->heal_hp(-DAMAGE);
      if(TP->query_hp() <= 0)
         TP->do_die(TO);
      return 1;
   }
   write("You deftly walk towards the center of the bridge.\n");
   return 0;
}
