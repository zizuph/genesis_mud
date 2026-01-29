inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
object ob1;
/* by Antharanos */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Inside the mage's tent");
   set_long("Somehow, there appears to be far more space within the tent "+
      "than seems possible. The square tent is approximately twelve feet "+
      "by twelve feet in length and width, and well over eight feet in "+
      "height. Apparently makeshift wooden shelves are stacked on three of "+
      "the walls, with the fourth being where the 'exit' to the tent is. "+
      "A large rug of unusual design has been lain on the ground, while "+
      "several varieties of pottery lie scattered aside the shelves and "+
      "walls. Faerie fire decorates the interior of the tent, providing a dim, eerie "+
      "illumination that spreads throughout the tent.\n");
   add_item(({"tent","interior","square tent"}),
      "It is cluttered with shelves burgeoning from many stacks of paper, "+
      "vials and other less common items.\n");
   add_item(({"makeshift wooden shelves","makeshift shelves","wooden shelves","shelves","shelf"}),
      "Hundreds of stacks of paper, vials for potions, jars filled with "+
      "herbs and dozens of other strange items have been crammed onto them, "+
      "making it appear as if the shelves may explode from the sheer volume "+
      "of material loaded on them.\n");
   add_item(({"walls","wall"}),
      "The sides of the tent appear to have been made from some sort "+
      "of black leather.\n");
   add_item(({"large rug","rug"}),
      "A large rug that looks as if a crazed painter randomly threw gobs "+
      "of paint onto the rug, then proceeded to spread the various colors "+
      "around.\n");
   add_item(({"ground"}),
      "It is covered by the large rug.\n");
   add_item(({"faerie fire","fire"}),
      "The magical light glows with the luminescence of hundreds of tiny faerie "+
      "lights, hence the name.\n");
   add_exit(CPASS(drow/bazaar/b5),"exit",0,-1,-1);
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(CPASS(drow/npc/bazaar_mage));
      ob1 -> arm_me();
      ob1 -> move_living("X",TO);
   }
}
