inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
object ob2;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   set_short("Inside a small tent");
   set_long("The interior of this tent is more utilitarian than plain, "+
      "most likely the home of a warrior. A single sleeping mat, one lamp and "+
      "a rug cover the ground. A small iron pot is also in the center of the "+
      "tent, while on the floor's edge is a mass of thorny spikes.\n");
   add_item(({"tent"}),"Its what you are inside of! Duh!\n");
   add_item(({"sleeping mat","mat"}),"It has been rolled up carefully and neatly "+
      "in the corner, leaving more room to walk about.\n");
   add_item(({"corner"}),"A dark part of the tent where the sleeping mat has "+
      "been placed.\n");
   add_item(({"lamp"}),"A rusted old bronze lamp. It no longer seems to "+
      "work.\n");
   add_item(({"rug"}),"A large rug woven from camel fibers. An image of a "+
      "dark sun has been placed onto it.\n");
   add_item(({"small iron pot","small pot","iron pot"}),"An old, worn-out "+
      "pot used for warmth and cooking.\n");
   add_item(({"mass of thorny spikes","mass","thorny spikes","spikes","spike"}),
      "A barrier created to prevent desert creatures from stealing into the "+
      "tent's interior.\n");
   add_exit(CPASS(desert/camp/c32),"east",0,-1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object("/d/Kalad/common/wild/pass/npc/lily_knight");
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A Knight of Thanar enters the tent!\n");
   }
   if(!ob2)
      {
      ob2 = clone_object("/d/Kalad/common/wild/pass/npc/bed_ewar");
      ob2 -> my_stuff();
      ob2 -> move_living("M",TO);
      tell_room(TO,"A Bedellin warrior follows soon after.\n");
      ob1 -> team_join(ob2);
   }
}
