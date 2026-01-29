/*
* Created by: See /d/Cirath/events/castledoom/code.txt
* Date: Dec 2001 
*
* Comments: Tower room
*/

#include "defs.h"

inherit CASTLEDOOM + "base_inside";

void
create_inside_room()
{
  set_short("swt3");
  
  set_long("swt3.\n");

  add_exit(TOWERS + "swt1", "north", 0, 0, 0);
  add_exit(TOWERS + "swt2", "northeast", 0, 0, 0);
  add_exit(TOWERS + "swt4", "east", 0, 0, 0);
  add_exit(TOWERS + "swt7", "up", 0, 0, 0);
  //add_exit(DUNGEON + "", "down", 0, 0, 0);
  reset_room();
}


