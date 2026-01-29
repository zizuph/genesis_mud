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
  set_short("NWT15");
  
  set_long("NTW15.\n");

  add_exit(TOWERS + "nwt13", "north", 0, 0, 0);
  add_exit(TOWERS + "nwt14", "northeast", 0, 0, 0);
  add_exit(TOWERS + "nwt16", "east", 0, 0, 0);
  reset_room();
}


