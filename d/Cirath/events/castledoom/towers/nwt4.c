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
  set_short("NWT4");
  
  set_long("NTW4.\n");

  add_exit(TOWERS + "nwt1", "northwest", 0, 0, 0);
  add_exit(TOWERS + "nwt2", "north", 0, 0, 0);
  add_exit(TOWERS + "nwt3", "west", 0, 0, 0);
  add_exit(COURT + "cy1", "southeast", 0, 0, 0);
  reset_room();
}


