inherit "/d/Kalad/common/wild/pass/uc/uc_std";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_room()
{
   ::create_room();
   set_short("At the bottom of the chasm");
   set_long("At the bottom of the chasm.\n"+
      "Bones, hundreds, if not thousands of bones lie scattered all over "+
      "the bottom of this chasm. Some of them are piled high in great mounds "+
      "that tower far above you, while others lie scattered about, as though "+
      "they were a child's toys. The surrounding rock is as it was "+
      "farther up, composed of some strange, dark material. Escape from "+
      "this place seems impossible, for the walls of the chasm are "+
      "practically vertical.\n"+
      "The bottom of the chasm continues to the west.\n");
   add_item(({"bottom","chasm"}),
      "A large gash within the ground, it is, unfortunately, where you are.\n");
   add_item(({"bones","bone"}),
      "The remnants of numerous creatures, some human...others not quite so.\n");
   add_item(({"great mounds","mounds","mound","great mound"}),
      "Rising nearly twenty feet in height, they easily tower over you, but "+
      "fall far short of the distance to the top of the chasm.\n");
   add_item(({"surrounding rock","rock"}),
      "It is composed of some unusually dark material that appears to absorb "+
      "the minutest of light that shines upon it.\n");
   add_item(({"walls","wall"}),
      "They lie at a ninety degree angle to the floor, and are as smooth "+
      "as ice, offering no handholds whatsoever.\n");
   add_item(({"floor","ground"}),
      "It is composed of strangely dark rock.\n");
   add_item(({"ceiling"}),
      "It is impossible to view, as you are too far down in the chasm.\n");
   add_exit(CPASS(uc/d4),"west","@@msg",2,1);
}
void
init()
{
   ::init();
   AA(climb,climb);
}
int
climb(string str)
{
   if(!str || str != "up")
      {
      NF("Climb where? Up?\n");
      return 0;
   }
   write("You try to climb up the sheer walls of the chasm, but fail.\n");
   say(QCTNAME(TP) + " tries to climb up the sheer walls of the chasm, but fails.\n");
   return 1;
}
msg()
{
   write("The crunch of bones creates eerie echoes as you move across the "+
      "floor.\n");
   return 0;
}
