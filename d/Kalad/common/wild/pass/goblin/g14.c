inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
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
      "the walls are many crude paintings. To the south, a slight breeze "+
      "can be felt.\n");
   add_item(({"floor"}),"The stony ground is covered in refuse.\n");
   add_item(({"refuse"}),"Discarded and chewed bones, scraps of wood, "+
      "and the occasional pile of dung litter the floor.\n");
   add_item(({"walls","wall"}),"The otherwise unremarkable interior of "+
      "the cave is decorated by the many paintings on its sides.\n");
   add_item(({"crude paintings","paintings","painting"}),"All depict "+
      "an image of a bloody hand clutching an eyeball.\n");
   add_exit(CPASS(goblin/g13),"west",0,1,2);
   add_exit(CPASS(goblin/g11),"south",0,1,2);
   set_alarm(10.0,60.0,"smell");
}
smell()
{
   tell_room(TO,"A horrible stench wafts from the west.\n");
   return 1;
}
