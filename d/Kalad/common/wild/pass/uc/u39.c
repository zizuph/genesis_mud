inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
#define KG "/d/Kalad/common/wild/pass/uc/npc/kob_guard"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("A crossroads of passages");
   set_long("A crossroads of passages.\n"+
      "Stone as black as a grieving widow's veil is visible from all sides, "+
      "its dark embrace promising the only certainty in life, death. Above "+
      "lies an unfathomable amount of rock, an immense volume of which "+
      "seperates you from the sun-lit realms up above. The rock's burdening "+
      "presence seems to absorb your energy, leaving you weakened and weary. "+
      "Three passages are open to you here, one journeying to the northwest, "+
      "another to the northeast and a third one to the southwest.\n");
   add_item(({"crossroads","crossroad","passages","passage"}),
      "A relatively cramped tunnel lying far beneath the surface of Kalad.\n");
   add_item(({"stone","rock"}),
      "An unusually dark substance that seems to suck the very life from "+
      "your bones.\n");
   add_item(({"darkness"}),
      "An absence of light so profound it is quite disconcerting.\n");
   add_item(({"walls","wall","floor","ground","ceiling"}),
      "It is composed of rock and stone.\n");
   add_exit(CPASS(uc/u32),"northwest",0,2,1);
   add_exit(CPASS(uc/u33),"northeast",0,2,1);
   add_exit(CPASS(uc/u45),"southwest",0,2,1);
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
      ob1 -> team_join(ob2);
      tell_room(TO,"With a rush of foul air, two kobolds arrive.\n");
   }
}
