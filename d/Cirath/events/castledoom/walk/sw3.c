/*
* Created by: See /d/Cirath/events/castledoom/code.txt
* Date: Dec 2001 
*
* Comments: Walk room
*/

#include "defs.h"

inherit CASTLEDOOM + "base_outside";

void
create_outside_room()
{
  set_short("sw3");
  
  set_long("sw3.\n");

  add_exit(WALK + "sw1", "northwest", 0, 0, 0);
  add_exit(WALK + "sw2", "northeast", 0, 0, 0);
  add_exit(WALK + "sw4", "southwest", 0, 0, 0);
  add_exit(WALK + "sw5", "southeast", 0, 0, 0);
  reset_room();
}


