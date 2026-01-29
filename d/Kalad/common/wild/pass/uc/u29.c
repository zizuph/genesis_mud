inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
#define CHECK_DEX 30
#define DAMAGE 250
string long;
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("At the center of a stone bridge");
   set_long("At the center of a stone bridge.\n"+
      "A strange and unusual sensation pervades your being, though you know "+
      "you are far beneath the surface, standing here within this cavern "+
      "gives you the odd feeling that you are in a featureless black "+
      "void, one that stretches on and on without end. Were it not for the "+
      "bridge beneath your feet, this sensation would be complete. The "+
      "bridge continues straight to the north and south, into the featureless "+
      "blackness.\n");
   add_item(({"center","stone bridge","bridge"}),
      "An uncomfortably narrow bridge of black stone that stretches into the "+
      "blackness to the north and south.\n");
   add_item(({"black stone","stone"}),
      "Rock of a hue that is unnaturally dark, for it seems to absorb even "+
      "the brightest of lights.\n");
   add_item(({"cavern"}),
      "All that is visible is a seemingly endless expanse of darkness.\n");
   add_item(({"darkness","blackness","featureless blackness","lightlessness"}),
      "An absence of light that seems most profound right beneath your "+
      "feet, past the bridge and in the lightlessness below.\n");
   add_item(({"chasm"}),
      "Like the rest of the cavern, only darkness is visible, though the sense "+
      "of space is greater for it.\n");
   add_exit(CPASS(uc/u20),"north","@@check1",2,1);
   add_exit(CPASS(uc/u37),"south","@@check2",2,1);
}
void
init()
{
   ::init();
   AA(jump,jump);
   AA(throw,throw);
}
int
jump(string str)
{
   write("You foolishly jump and instead of landing on the bridge, fall "+
      "down towards the chasm.\n");
   say(QCTNAME(TP) + " foolishly jumps and falls from the bridge and "+
      "down into the chasm.\n");
   TP->move_living("M","/d/Kalad/common/wild/pass/uc/fall_w",1);
   return 1;
}
int
throw(string str)
{
   object *arr;
   int i;
   if(!str)
      {
      NF("Throw what?\n");
      return 0;
   }
   arr = FIND_STR_IN_OBJECT(str, TP);
   if(!sizeof(arr))
      {
      NF("You don't have any '" + str + "'.\n");
      return 0;
   }
   for (i = 0; i < sizeof(arr); i++)
   arr[i]->move("/d/Kalad/common/wild/pass/uc/fall_w");
   write("You throw " + COMPOSITE_DEAD(arr) + " off the bridge.\n");
   say(QCTNAME(TP) + " throws " + QCOMPDEAD + " off the bridge.\n");
   return 1;
}
check1()
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
   write("You deftly walk towards the northern end of the bridge.\n");
   return 0;
}
check2()
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
   write("You deftly walk towards the southern end of the bridge.\n");
   return 0;
}
