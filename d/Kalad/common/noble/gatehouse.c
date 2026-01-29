inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define KG "/d/Kalad/common/caravan/npc/kguard_cg"

/* by Antharanos */
object ob1;
object ob2;
object ob3;
object ob4;
create_room()
{
   ::create_room();
   set_short("Gatehouse room");
   set_long("This is the inside of the gatehouse, this room is of medium "+
      "size, not so small as to be cramped, but not large enough to be "+
      "called spacious. There is a table in the corner with some stools "+
      "around it.\n");
   INSIDE;
   hear_bell = 1;
   add_item ( ({"room"}),
      "This room is rather dimly lit, the only light source besides the "+
      "windows is a small brass lantern in the far corner.\n");
   add_item ( ({"lantern"}),
      "This small lantern barely provides enough light to illuminate this "+
      "guardroom.\n");
   add_item ( ({"table"}),
      "This must be where the guards play cards and eat their meals.\n");
   add_item ( ({"stools","stool"}),
      "These pieces of furniture are what the guards sit on.\n");
   add_item ( ({"windows","window"}),
      "looking out through the windows, Caravan Street can be seen.\n");
   add_exit("/d/Kalad/common/noble/farmer-end", "out",0,-1,-1);
   set_alarm(1.0,0.0,"reset_room");
}
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
      tell_room(TO,"A troop of four guardsmen of Kabal enters the gatehouse.\n");
   }
}
