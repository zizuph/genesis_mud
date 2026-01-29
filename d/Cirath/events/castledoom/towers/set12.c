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
  set_short("set12");
  
  set_long("set12.\n");

  add_exit(TOWERS + "set8", "down", 0, 0, 0);
  add_exit(TOWERS + "set9", "northwest", 0, 0, 0);
  add_exit(TOWERS + "set10", "north", 0, 0, 0);
  add_exit(TOWERS + "set11", "west", 0, 0, 0);
  add_exit(TOWERS + "set16", "up", 0, 0, 0);
  reset_room();
}


