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
  set_short("set10");
  
  set_long("set10.\n");

  add_exit(TOWERS + "set9", "west", 0, 0, 0);
  add_exit(TOWERS + "set11", "southwest", 0, 0, 0);
  add_exit(TOWERS + "set12", "south", 0, 0, 0);
  add_exit(HALL + "eh6", "north", 0, 0, 0);
  reset_room();
}


