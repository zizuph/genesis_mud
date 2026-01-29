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
  set_short("NWT14");
  
  set_long("NTW14.\n");

  add_exit(TOWERS + "nwt13", "west", 0, 0, 0);
  add_exit(TOWERS + "nwt15", "southwest", 0, 0, 0);
  add_exit(TOWERS + "nwt16", "south", 0, 0, 0);
  reset_room();
}


