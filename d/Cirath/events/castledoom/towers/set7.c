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
  set_short("set7");
  
  set_long("set7.\n");

  add_exit(TOWERS + "set5", "north", 0, 0, 0);
  add_exit(TOWERS + "set6", "northeast", 0, 0, 0);
  add_exit(TOWERS + "set8", "east", 0, 0, 0);
  reset_room();
}


