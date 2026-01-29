/*
* Created by: See /d/Cirath/events/castledoom/code.txt
* Date: Dec 2001 
*
* Comments: Tower room
*/

#include "defs.h"

inherit CASTLEDOOM + "base_outside";

void
create_outside_room()
{
  set_short("set16");
  
  set_long("set16.\n");

  add_exit(TOWERS + "set12", "down", 0, 0, 0);
  add_exit(TOWERS + "set13", "northwest", 0, 0, 0);
  add_exit(TOWERS + "set14", "north", 0, 0, 0);
  add_exit(TOWERS + "set15", "west", 0, 0, 0);
  reset_room();
}


