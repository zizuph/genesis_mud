// Bazaar Street17 (/d/Avenir/common/bazaar/extr/str17.c)
// creator(s):   Triana 1994
// last update:  Tepisch Aug 94, Iliyan April 95
// purpose:
//
// note:
// bug(s):
// to-do:

inherit "/d/Avenir/common/bazaar/extr/std_ctr2.c";

#include "/d/Avenir/common/bazaar/bazaar.h"

init()
{
   ::init();
   ADD("do_crunch","north");
   ADD("do_crunch", "east");
}

object guard1, guard2;

reset_room()
{
  if (!guard1)
   {
      guard1 = clone_object(BAZAAR + "NPCS/grd.c");
      guard1->arm_me();
      guard1->move_living("M", this_object());
    }
  if (!guard2)
   {
      guard2 = clone_object(BAZAAR + "NPCS/grd.c");
      guard2->arm_me();
      guard2->move_living("M", this_object());
    }
}

void
create_room()
{
   AE(EXTR + "str11", "north", 0);
   AE(EXTR + "str18", "east", 0);
   AE(INTR + "guild", "west", 0);

   AI("garden", "A part of the roof that extends outward "+
     "parallel to the ground.\n");
   AI(({"complex","building complex"}), "A series of inter"+
     "connected buildings from which loud grunts and metal "+
     "clanging against metal can be heard.\n");
   add_item(({"sign", "discreet sign"}), "NO STEEDS ALLOWED!\n"+
     "They are trampling the garden!\n");
   add_cmd_item(({"sign", "discreet sign"}), ({"read"}),
     "NO STEEDS ALLOWED!\n"+
     "They are trampling the garden!\n");
   AI(({"garden","south"}),"The garden to the south of the gate is "
     +"thick with vegetation and other plants. The sweet scent of "
     +"herbs and flowers is in the air.\n");

   clone_object(OBJ + "door/g_gate1a")->move(TO);

   SHORT("East of Survival Training Center");
   make_the_room(" The gravel walk leading to the "+
      "building complex in the west looks like it has been "+
      "churned up by the passage of many feet. South you "+
      "can see what appears to be a garden.\n");

   reset_room();
}

do_crunch()
{
   write("Gravel crunches under your feet.\n");
}

