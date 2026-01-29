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
      "A countless number and amount of stone surrounds you from all sides, "+
      "seeming to promise any foolish enough to be here the cold of an "+
      "unmarked grave. Overhead lies thousands of tons of rock, forming an "+
      "impenetrable barrier between you and the lands of light far above. "+
      "Just to the north lies an immense chasm, like the maw of some giant "+
      "beast gaping wide to swallow everything within its path. A thin, "+
      "stone bridge crosses the chasm, leading north until it reaches "+
      "the far side, which is just barely visible from here. The passage "+
      "takes a bend here, heading off towards the southeast.\n");
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
   add_exit(CPASS(uc/u29),"north","@@check",2,1);
   add_exit(CPASS(uc/u41),"southeast",0,2,1);
}
check()
{
   if(TP->query_stat(SS_DEX) < random(CHECK_DEX))
      {
      write("You start to walk northwards...\n");
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
