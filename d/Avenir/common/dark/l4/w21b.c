/*

*/

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"

void
create_room()
{
  set_short("stairwell between level two and level four");
  set_long("You now stand in a stairwell between different levels of "
    +"the utterdark. Above is the second level, and below is the fourth "
	+"level, from whence the stench of ogres rises.\n");

  AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway", "steps", "stairs"}),
     "Very uninteresting stone.\n"); 
  AI(({"steps", "stairs"}), "They lead upward and downward, into more darkness.\n");

  add_exit(L4 + "w21", "down",0);
  add_exit(L2 + "w1", "up",0); 
  add_prop(ROOM_I_LIGHT,0);
  IN;
  reset_room();
}
