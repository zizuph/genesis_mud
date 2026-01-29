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
  set_short("set8");
  
  set_long("set8.\n");

  add_exit(TOWERS + "set4", "down", 0, 0, 0);
  add_exit(TOWERS + "set5", "northwest", 0, 0, 0);
  add_exit(TOWERS + "set6", "north", 0, 0, 0);
  add_exit(TOWERS + "set7", "west", 0, 0, 0);
  add_exit(TOWERS + "set12", "up", 0, 0, 0);
  reset_room();
}


