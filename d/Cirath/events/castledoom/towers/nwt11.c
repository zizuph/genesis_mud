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
  set_short("NWT11");
  
  set_long("NTW11.\n");

  add_exit(TOWERS + "nwt9", "north", 0, 0, 0);
  add_exit(TOWERS + "nwt10", "northeast", 0, 0, 0);
  add_exit(TOWERS + "nwt12", "east", 0, 0, 0);
  add_exit(HALL + "wh4", "south", 0, 0, 0);
  reset_room();
}


