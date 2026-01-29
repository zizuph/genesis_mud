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
  set_short("set9");
  
  set_long("set9.\n");

  add_exit(TOWERS + "set10", "east", 0, 0, 0);
  add_exit(TOWERS + "set12", "southeast", 0, 0, 0);
  add_exit(TOWERS + "set11", "south", 0, 0, 0);
  add_exit(WALK + "sw5", "northwest", 0, 0, 0);
  reset_room();
}


