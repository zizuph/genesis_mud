inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Jail cell");
   set_long("This small rocky room reminds one of a cesspit in the "+
      "heat of summer. The walls are bare save for the sturdy-looking "+
      "chains that hang from around head height, while the floor is "+
      "covered with many stagnant pools of some dark liquid. A ladder in "+
      "the center of the room leads up through a hole in the ceiling.\n");
   add_item(({"small rocky room","small room","rocky room","room"}),
      "A disgustingly filthy place, a place ripe for disease to flourish.\n");
   add_item(({"walls","wall"}),"The sides of this room are nothing but "+
      "bare stone.\n");
   add_item(({"sturdy-looking chains","chains","chain"}),"Strong links "+
      "made of forged iron. They look as if they are used to imprison captives.\n");
   add_item(({"floor"}),"The bare rock floor is covered with pools of "+
      "some stagnant liquid. The smell is horrendous.\n");
   add_item(({"stagnant pools","pools","pool","dark liquid","liquid","stagnant liquid"}),
      "Consisting of some dark, brownish and murky liquid, it slowly swirls "+
      "around in a clock-wise direction.\n");
   add_item(({"ladder"}),"Made of wood, the aged and somewhat decaying ladder "+
      "looks barely strong enough to support your weight.\n");
   add_item(({"ceiling"}),"The bare rock surface is devoid of any markings.\n");
   add_exit(CPASS(goblin/g15),"up",0,1,2);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/prisoner");
      ob1 -> move(TO);
      tell_room(TO,"The kabal guard rattles his chains.\n");
   }
}
