inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define GG "/d/Kalad/common/wild/pass/npc/gob_guard"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Inside the cave");
   set_long("You are inside a musty-smelling cave whose floor is "+
      "littered with all manner of refuse. The smell is so bad here that "+
      "it nearly makes you wretch. Along the walls are many crudely painted "+
      "images. The cave appears to continue to the north, while in the "+
      "southwest it leads out into the open.\n");
   add_item(({"floor","refuse"}),"Discarded and chewed bones, fecal "+
      "waste, along with bits and scraps of cloth are strewn across the "+
      "cave floor.\n");
   add_item(({"walls","wall"}),"The otherwise unremarkable cave interior "+
      "is covered in crude paintings.\n");
   add_item(({"crude paintings","paintings","painting","painted images","images","image"}),
      "A myriad variety of images, all of the same thing cover the walls. "+
      "The image is that of a bloody hand clutching an eyeball.\n");
   add_exit(CPASS(goblin/g14),"north",0,1,2);
   add_exit(CPASS(goblin/g8),"southwest");
   set_alarm(1.0,0.0,"reset_room");
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
      ob1 -> team_join(ob2);
   }
}
