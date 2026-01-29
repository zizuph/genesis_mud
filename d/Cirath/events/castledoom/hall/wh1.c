/*
* Created by: See /d/Cirath/events/castledoom/code.txt
* Date: Dec 2001 
*
* Comments: Hall room
*/

#include "defs.h"

inherit CASTLEDOOM + "base_inside";

void
create_inside_room()
{
  set_short("wh1");
  
  set_long("wh1.\n");

  add_exit(TOWERS + "nwt3", "north", 0, 0, 0);
  add_exit(HALL + "wh2", "south", 0, 0, 0);
  reset_room();
}


