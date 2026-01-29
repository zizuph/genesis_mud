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
  set_short("net11");
  
  set_long("net11.\n");

  add_exit(TOWERS + "net9", "north", 0, 0, 0);
  add_exit(TOWERS + "net10", "northeast", 0, 0, 0);
  add_exit(TOWERS + "net12", "east", 0, 0, 0);
  add_exit(WALK + "sw2", "southwest", 0, 0, 0);
  reset_room();
}


