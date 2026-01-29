/*
* Created by: See /d/Cirath/events/castledoom/code.txt
* Date: Dec 2001 
*
* Comments: Hall room
*/

#include "defs.h"

inherit CASTLEDOOM + "base_outside";

void
create_outside_room()
{
  set_short("wh6");
  
  set_long("wh6.\n");

  add_exit(HALL + "wh5", "north", 0, 0, 0);
  add_exit(TOWERS + "swt9", "south", 0, 0, 0);
  reset_room();
}


