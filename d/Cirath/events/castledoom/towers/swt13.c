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
  set_short("swt13");
  
  set_long("swt13.\n");

  add_exit(TOWERS + "swt14", "east", 0, 0, 0);
  add_exit(TOWERS + "swt15", "south", 0, 0, 0);
  add_exit(TOWERS + "swt16", "southeastt", 0, 0, 0);
  reset_room();
}


