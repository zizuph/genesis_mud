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
  set_short("set4");
  
  set_long("set4.\n");

  add_exit(TOWERS + "set1", "northwest", 0, 0, 0);
  add_exit(TOWERS + "set2", "north", 0, 0, 0);
  add_exit(TOWERS + "set3", "west", 0, 0, 0);
  add_exit(TOWERS + "set8", "up", 0, 0, 0);
  reset_room();
}


