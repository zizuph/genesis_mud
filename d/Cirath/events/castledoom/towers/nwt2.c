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
  set_short("NWT2");
  
  set_long("NTW2.\n");

  add_exit(TOWERS + "nwt1", "west", 0, 0, 0);
  add_exit(TOWERS + "nwt3", "southwest", 0, 0, 0);
  add_exit(TOWERS + "nwt4", "south", 0, 0, 0);
  add_exit(HALL + "nh1", "east", 0, 0, 0);
  reset_room();
}


