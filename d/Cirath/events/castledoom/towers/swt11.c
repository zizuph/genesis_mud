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
  set_short("swt11");
  
  set_long("swt11.\n");

  add_exit(TOWERS + "swt7", "down", 0, 0, 0);
  add_exit(TOWERS + "swt9", "north", 0, 0, 0);
  add_exit(TOWERS + "swt10", "northeast", 0, 0, 0);
  add_exit(TOWERS + "swt12", "east", 0, 0, 0);
  add_exit(TOWERS + "swt15", "up", 0, 0, 0);
  reset_room();
}


