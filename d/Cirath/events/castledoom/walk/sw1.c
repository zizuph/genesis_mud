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
  set_short("sw1");
  
  set_long("sw1.\n");

  add_exit(TOWERS + "nwt12", "northwest", 0, 0, 0);
  add_exit(WALK + "sw3", "southeast", 0, 0, 0);
  reset_room();
}


