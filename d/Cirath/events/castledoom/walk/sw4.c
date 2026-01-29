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
  set_short("sw4");
  
  set_long("sw4.\n");

  add_exit(TOWERS + "swt10", "southwest", 0, 0, 0);
  add_exit(WALK + "sw3", "northeast", 0, 0, 0);
  reset_room();
}


