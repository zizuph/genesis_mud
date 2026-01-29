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
  set_short("swt1");
  
  set_long("swt1.\n");

  add_exit(TOWERS + "swt2", "east", 0, 0, 0);
  add_exit(TOWERS + "swt3", "south", 0, 0, 0);
  add_exit(TOWERS + "swt4", "southeast", 0, 0, 0);
  add_exit(HALL + "wh3", "north", 0, 0, 0);
  reset_room();
}


