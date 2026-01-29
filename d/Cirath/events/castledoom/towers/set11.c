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
  set_short("set11");
  
  set_long("set11.\n");

  add_exit(TOWERS + "set9", "north", 0, 0, 0);
  add_exit(TOWERS + "set10", "northeast", 0, 0, 0);
  add_exit(TOWERS + "set12", "east", 0, 0, 0);
  add_exit(HALL + "sh3", "west", 0, 0, 0);
  reset_room();
}


