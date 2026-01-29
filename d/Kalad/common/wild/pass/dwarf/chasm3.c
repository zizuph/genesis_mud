inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
/* by korat */
create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Inside a cave");
   set_long("The cave is not very large and contains just some "+
      "animal refuse. The walls looks fairly normal, except "+
      "the inner part. It is too smooth to be natural.\n");
   add_item("refuse","Just normal animal refuse. Nothing "+
      "special about it.\n");
   add_item(({"wall","walls"}),
      "The walls are all natural except that inner wall.\n");
   add_item("inner wall","You walk closer to the inner wall, "+
      "but suddenly you hit some invisible barrier!\n");
   add_item(({"barrier","inner barrier"}),
      "You cannot see anything, but when you reach out a hand "+
      "towards where it must be, your fingers touch something "+
      "just a meter from the inner wall. A invisible barrier "+
      "that you cannot penetrate.\n");
   add_exit(CPASS(dwarf/chasm2),"out");
   add_exit(CPASS(dwarf/chasm4),"in","@@test@@");
}

test()
{
   if(TP->test_bit("Kalad",2,3))
      {
      write("You notice the invisible barrier yield to your touch.\n");
      return 0;
   }
   write("You walk inwards, but slam into an invisible barrier!\n");
   return 1;
}

init()
{
   ::init();
   add_action("slice","slice");
   add_action("slice","cut");
   add_action("slice","break");
   add_action("slice","axe");
}
slice(string str)
{
   notify_fail("What?\n");
   if (!str) return 0;
   if(str!="barrier") return 0;
   notify_fail("Do what? How?\n");
   if(MASTER_OB(TP->query_weapon(W_BOTH)) != "/d/Kalad/common/wild/pass/dwarf/wep/mag_axe")
      return 0;
   write("You lift your axe high into the air and slash it down "+
      "against the invisible barrier. You feel the axe bite deeply into it!\n");
   say(QCTNAME(TP)+" lifts his axe high and slices it down through "+
      "empty air. Then "+TP->query_pronoun()+" walks towards the "+
      "inner wall.\n");
   if(TP->query_bit("Kalad",2,3) == 0)
      {
      write("You understand that from now this magical "+
         "wall will never again hinder your entrance. You "+
         "feel more experienced.\n");
      TP->add_exp(1000);
      TP->set_bit(2,3);
   }
   return 1;
}
