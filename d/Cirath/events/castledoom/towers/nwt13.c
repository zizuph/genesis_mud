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
  set_short("NWT13");
  
  set_long("NTW13.\n");

  add_exit(TOWERS + "nwt9", "down", 0, 0, 0);
  add_exit(TOWERS + "nwt14", "east", 0, 0, 0);
  add_exit(TOWERS + "nwt15", "south", 0, 0, 0);
  add_exit(TOWERS + "nwt16", "southeastt", 0, 0, 0);
  reset_room();
}


