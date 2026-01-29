/* Xak Tsorath coded by Percy */

#include "/d/Krynn/common/random_meet.h"
#include "xlocal.h"
#include "/sys/ss_types.h"
#include <macros.h>

inherit MARSHBASE

object monster;

void
reset_room()
{
   if (random(5))
      return;
   if (monster)
      return;
   monster = RANDOM_MEET("/d/Krynn/common/rndtables/tblcursedlands");
   if (monster->query_prop(OBJ_I_COLORABLE))
      monster->set_color("black");
   monster->move(TO);
}

void
create_marsh() 
{
   set_short("The cursed lands");
   set_long("You are in the cursed lands, a truely dismal place in"
      + " every sense of the word. All around you is a seemingly"
      + " endless marsh swamp. Danger seems to ooze from its nauseous"
      + " surface. Further into the swamp to the south you can see"
      + " what looks like a large campsite set up for many creatures."
      + " You can't make out much from here and there seems to be no"
      + " way to cross the swamp from here to get there.\n");
   
   add_exit(TDIR + "marsh1.c", "north", "@@cross", 5);
   add_exit(TDIR + "marsh4.c", "west", "@@cross", 5);
   OUTSIDE;
   LIGHT;
   add_item(({"campsite", "camp"}), "@@camp");
   add_item(({"marsh", "swamp", "marsh swamp"}), "This swamp appears to be " +
              "endless, and very forboding.\n");
   reset_room();
}

string
camp()
{
   write("You can't make out much from here and the swamp is impassable"
      + " in that direction.\n");
   return "";
}
