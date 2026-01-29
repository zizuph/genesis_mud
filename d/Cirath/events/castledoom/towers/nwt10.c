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
  set_short("NWT10");
  
  set_long("NTW10.\n");

  add_exit(TOWERS + "nwt9", "west", 0, 0, 0);
  add_exit(TOWERS + "nwt11", "southwest", 0, 0, 0);
  add_exit(TOWERS + "nwt12", "south", 0, 0, 0);
  add_exit(HALL + "nh4", "east", 0, 0, 0);
  reset_room();
}


