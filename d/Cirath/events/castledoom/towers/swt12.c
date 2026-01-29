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
  set_short("swt12");
  
  set_long("swt12.\n");

  add_exit(TOWERS + "swt9", "northwest", 0, 0, 0);
  add_exit(TOWERS + "swt10", "north", 0, 0, 0);
  add_exit(TOWERS + "swt11", "west", 0, 0, 0);
  add_exit(HALL + "sh1", "east", 0, 0, 0);
  reset_room();
}


