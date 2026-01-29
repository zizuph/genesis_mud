inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define GG "/d/Kalad/common/wild/pass/npc/gob_guard"
object ob1;
object ob2;
object ob3;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Inside the cave");
   set_long("You are inside the musty cave, where the floor is littered "+
      "with all manner of refuse. The terrible stench here nearly makes "+
      "you wretch. The stench seems to increase further to the west. Along "+
      "the walls are many crude paintings. To the east, the terrible "+
      "stench seems to lighten somewhat, perhaps promising an exit out "+
      "into the open air.\n");
   add_item(({"floor"}),"The stony ground is covered in refuse.\n");
   add_item(({"refuse"}),"Discarded and chewed bones, scraps of wood, "+
      "and the occasional pile of dung litter the floor.\n");
   add_item(({"walls","wall"}),"The otherwise unremarkable interior of "+
      "the cave is decorated by the many paintings on its sides.\n");
   add_item(({"crude paintings","paintings","painting"}),"All depict "+
      "an image of a bloody hand clutching an eyeball.\n");
   add_exit(CPASS(goblin/g12),"west",0,1,2);
   add_exit(CPASS(goblin/g14),"east",0,1,2);
   set_alarm(1.0,0.0,"reset_room");
   set_alarm(10.0,60.0,"smell");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(GG);
      ob1 -> move_living("xxx",TO);
   }
   if(!ob2)
      {
      ob2 = clone_object(GG);
      ob2 -> move_living("xxx",TO);
   }
   if(!ob3)
      {
      ob3 = clone_object(GG);
      ob3 -> move_living("xxx",TO);
      ob1 -> team_join(ob2);
      ob1 -> team_join(ob3);
   }
}
smell()
{
   tell_room(TO,"A terrible stench wafts from the west.\n");
   return 1;
}
