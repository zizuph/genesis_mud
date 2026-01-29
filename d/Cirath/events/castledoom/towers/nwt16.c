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
  set_short("NWT16");
  
  set_long("NTW16.\n");

  add_exit(TOWERS + "nwt13", "northwest", 0, 0, 0);
  add_exit(TOWERS + "nwt14", "north", 0, 0, 0);
  add_exit(TOWERS + "nwt15", "west", 0, 0, 0);
  reset_room();
}


