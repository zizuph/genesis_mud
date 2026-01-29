inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
#define KG "/d/Kalad/common/wild/pass/uc/npc/kob_guard"
object ob1;
object ob2;
object ob3;
object ob4;
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("The end of the passage, a small chamber");
   set_long("You are at the end of the passage, within a small chamber.\n"+
      "Stone as black as the skin of the deep dragon surrounds you from all sides, "+
      "encompassing you in its cold, unyielding embrace. An unimaginable "+
      "amount of rock hangs overhead, seeming to absorb the very life from "+
      "your being, leaving you withered and fatigued. Here, the passage "+
      "you are journeying along stops abruptly. It continues only to the east, "+
      "where it disappears into oblivion. The entire chamber is littered "+
      "with feces, scattered amongst piles of bones.\n"+
      "A terrible stench is in the air.\n");
   add_item(({"small chamber","chamber"}),
      "A small recess set deep beneath the lands of light.\n");
   add_item(({"passage"}),
      "A tunnel located far beneath the realm of light, the realm of the sun.\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_item(({"feces"}),
      "Kobold dung, it is the cause of the horrible smell here.\n");
   add_item(({"piles","pile","bones","bone"}),
      "The horrible remnants of, judging by the size and shape of them, "+
      "gnomes.\n");
   add_exit(CPASS(uc/u32),"east",0,2,1);
   set_alarm(1.0,0.0,"reset_room");
}
void
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(KG);
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(KG);
      ob2 -> arm_me();
      ob2 -> move_living("M",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(KG);
      ob3 -> arm_me();
      ob3 -> move_living("M",TO);
   }
   if(!ob4)
      {
      ob4 = clone_object(KG);
      ob4 -> arm_me();
      ob4 -> move_living("M",TO);
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
      ob1 -> team_join(ob4);
      tell_room(TO,"Several kobolds appear from behind the piles of bones.\n");
   }
}
