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
  set_short("set14");
  
  set_long("set14.\n");

  add_exit(TOWERS + "set13", "west", 0, 0, 0);
  add_exit(TOWERS + "set15", "southwest", 0, 0, 0);
  add_exit(TOWERS + "set16", "south", 0, 0, 0);
  reset_room();
}


