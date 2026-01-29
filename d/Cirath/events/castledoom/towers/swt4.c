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
  set_short("swt4");
  
  set_long("swt4.\n");

  add_exit(TOWERS + "swt1", "northwest", 0, 0, 0);
  add_exit(TOWERS + "swt2", "north", 0, 0, 0);
  add_exit(TOWERS + "swt3", "west", 0, 0, 0);
  reset_room();
}


