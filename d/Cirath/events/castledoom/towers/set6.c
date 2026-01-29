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
  set_short("set6");
  
  set_long("set6.\n");

  add_exit(TOWERS + "set5", "west", 0, 0, 0);
  add_exit(TOWERS + "set7", "southwest", 0, 0, 0);
  add_exit(TOWERS + "set8", "south", 0, 0, 0);
  reset_room();
}


