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
  set_short("swt10");
  
  set_long("swt10.\n");

  add_exit(TOWERS + "swt9", "west", 0, 0, 0);
  add_exit(TOWERS + "swt11", "southwest", 0, 0, 0);
  add_exit(TOWERS + "swt12", "south", 0, 0, 0);
  add_exit(WALK + "sw4", "northeast", 0, 0, 0);
  reset_room();
}


