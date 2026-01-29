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
  set_short("NWT12");
  
  set_long("NTW12.\n");

  add_exit(TOWERS + "nwt9", "northwest", 0, 0, 0);
  add_exit(TOWERS + "nwt10", "north", 0, 0, 0);
  add_exit(TOWERS + "nwt11", "west", 0, 0, 0);
  add_exit(WALK + "sw1", "southeast", 0, 0, 0);
  reset_room();
}


