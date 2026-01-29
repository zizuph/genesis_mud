/* The crypt by percy */

#include "local.h"
#include "/d/Krynn/common/defs.h"
inherit INSIDE_BASE;
#include <macros.h>

object zo1, zo2;

create_solace_room()
{
   object door;
   
   set_short("Crypt room");
   set_long(break_string("You find yourself in the crypt entrance hall."
         + " The hall is well lit by some unseen magical force. The floor of"
         + " the hall is made of jet black marble and at the end of the hall"
         + " you can see an archway leading out into a well lit room. ", 70));
   
   add_exit(TDIR + "crypt2", "north", 0);
   
   add_item(({"marble door", "door", "doors", "double door",
            "double doors", "marble doors"}), "@@doors");
   add_item(({"floor", "marble floor", "black floor"}), "@@floor");
   add_item(({"arch", "archway"}), "@@arch");
   add_item(({"wall", "walls", "hall", "hallway", "ceiling", "roof"}),
      "@@wall");
   
   INSIDE
   LIGHT
   
   door = clone_object(OBJ + "d_hole1b");
   door->move(TO);
   door->set_key(K_HOLE1);
   
   reset_room();
}

reset_solace_room()
{
   if (!zo1)
      {
      zo1 = clone_object(MONSTER + "zowarrior");
      zo1->move_living("xxx", TO);
   }
   if (!zo2)
      {
      zo2 = clone_object(MONSTER + "zowarrior");
      zo2->move_living("xxx", TO);
   }
}

floor()
{
   write(BS("The floor is just total blackness, looking into it"
         + " is like looking at death.", 70));
   say(BS(QCTNAME(TP) + " studies the floor carefully.", 70));
   return "";
}

arch()
{
   write(BS("The archway looks like a normal arch, perfectly safe..", 70));
   say(BS(QCTNAME(TP) + " studies the archway carefully.", 70));
   return "";
}

wall()
{
   write(BS("The walls and the ceiling of the hallway are black though"
         + " they appear to only be made of normal stone, unlike the marble"
         + " floor.", 70));
   say(BS(QCTNAME(TP) + " studies the hallway carefully.", 70));
   return "";
}


doors()
{
   write(BS("These double doors are made of black obsidian marble, they look"
         + " very old and very very solid. Everything about them exudes an " +
         "ancient evil. You feel a shiver run up your spine.", 70));
   say(BS(QCTNAME(TP) + " studies the doors carefully.", 70));
   return "";
}
