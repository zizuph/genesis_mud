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
  set_short("swt7");
  
  set_long("swt7.\n");

  add_exit(TOWERS + "swt3", "down", 0, 0, 0);
  add_exit(TOWERS + "swt5", "north", 0, 0, 0);
  add_exit(TOWERS + "swt6", "northeast", 0, 0, 0);
  add_exit(TOWERS + "swt8", "east", 0, 0, 0);
  add_exit(TOWERS + "swt11", "up", 0, 0, 0);
  reset_room();
}


