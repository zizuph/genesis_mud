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
  set_short("swt9");
  
  set_long("swt9.\n");

  add_exit(TOWERS + "swt10", "east", 0, 0, 0);
  add_exit(TOWERS + "swt11", "south", 0, 0, 0);
  add_exit(TOWERS + "swt12", "southeast", 0, 0, 0);
  add_exit(HALL + "wh6", "north", 0, 0, 0);
  reset_room();
}


