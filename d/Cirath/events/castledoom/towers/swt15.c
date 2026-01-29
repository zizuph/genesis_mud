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
  set_short("swt15");
  
  set_long("swt15.\n");

  add_exit(TOWERS + "swt11", "down", 0, 0, 0);
  add_exit(TOWERS + "swt13", "north", 0, 0, 0);
  add_exit(TOWERS + "swt14", "northeast", 0, 0, 0);
  add_exit(TOWERS + "swt16", "east", 0, 0, 0);
  reset_room();
}


