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
  set_short("swt5");
  
  set_long("swt5.\n");

  add_exit(TOWERS + "swt6", "east", 0, 0, 0);
  add_exit(TOWERS + "swt7", "south", 0, 0, 0);
  add_exit(TOWERS + "swt8", "southeast", 0, 0, 0);
  reset_room();
}


