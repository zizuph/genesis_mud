inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
#define KG "/d/Kalad/common/wild/pass/uc/npc/kob_guard"
object ob1;
object ob2;
object ob3;
object ob4;
object ob5;
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A small chamber");
   set_long("You are within a small chamber.\n"+
      "Stone as black as the ashes of a campfire lie in every conceivable direction, "+
      "encompassing you in its cold, unyielding embrace. An unimaginable "+
      "amount of rock hangs overhead, seeming to absorb the very life from "+
      "your body, leaving it tired and vulnerable. Here there is a passage "+
      "that leads north. Scattered about the chamber are numerous piles of "+
      "bones, along with feces.\n"+
      "A putrid odor is in the air.\n");
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
   add_exit(CPASS(uc/u35),"north",0,2,1);
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
      tell_room(TO,"From behind the piles of bones appears several kobolds.\n");
      tell_room(TO,"One kobold drops a corpse of a gnome.\n");
   }
   if(!ob5)
      {
      ob5 = clone_object(CPASS(uc/obj/gno_corpse));
      ob5 -> move(TO);
   }
}
