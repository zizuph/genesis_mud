/* This is where the monument to the founder of Undraeth stands */
/* by Antharanos */
inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#define WIZ "/d/Kalad/common/wild/pass/drow/npc/monument_wizard"
object ob1;
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("At the monument site in Undraeth");
   set_long("You find yourself in a wide and relatively open area here "+
      "in the city of Undraeth. Visible all around you, although at "+
      "a more increased distance, are the many stalagmites of the city. "+
      "Leading away from here to the northeast and southwest is a long, thin "+
      "street.\n");
   add_item(({"wide area","open area","area","circular clearing","clearing"}),
      "A large space here in the heart of the city of Undraeth, where no "+
      "stalagmites stand, only the monument.\n");
   add_item(({"stalagmites","stalagmite"}),"Surrounding this huge "+
      "circular clearing in the city's heart, are the many stalagmite "+
      "dwellings of the resident population. Through powerful magics, the "+
      "stone has been transmutated into the equivalent of buildings in "+
      "surface cities.\n");
   add_item(({"large avenue","avenue"}),"A flat, smooth-stoned road "+
      "that bears not the slightest of debris. Not a single stone can be "+
      "found on its surface.\n");
   add_exit(CPASS(drow/d40),"northeast");
   add_exit(CPASS(drow/d31),"southwest","@@block");
   set_noshow_obvious(1);
   set_alarm(1.0,0.0,"reset_room");
   clone_object(CPASS(drow/obj/monument))->move(TO);
}
block()
{
   write("Darkness falls over you like the blanket of death...\n");
   write("Horrible, wicked things claw and scratch at you...\n");
   TP->command("scream");
   write("You stumble backwards and regain your senses!\n");
   return 1;
}
reset_room()
{
   if(!ob1)
      {
      ob1 = clone_object(WIZ);
      ob1 -> arm_me();
      ob1 -> move_living("M",TO);
      tell_room(TO,"A figure appears from amidst a cloud of black smoke.\n");
   }
}
