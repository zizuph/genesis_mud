/* n2.c is east
n12.c is north
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"

create_room()
{

set_short("Dark tunnel");
set_long("This dark northbound tunnel branches here to the east.  The walls and ceiling are of"+" rough stone, and, looking ahead, you can see only darkness.\n");

AI(({"ceiling", "walls", "wall", "floor", "tunnel"}),
   "Very uninteresting stone.\n");    

add_exit("/d/Avenir/common/dark/l4/n2","east",0);
add_exit("/d/Avenir/common/dark/l4/n12","north",0);
add_exit("/d/Avenir/common/dark/l4/center","south","@@do_puddle");

BLACK
IN

	add_npc(MON + "bat", 2);
}

do_puddle()
{
   if (random(3))
   {	
      write("You lose your footing and fall into a puddle.\n");
      this_player()->reduce_hit_point(15);
   }
   return 0;
}
