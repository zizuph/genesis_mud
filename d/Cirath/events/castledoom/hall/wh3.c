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
  set_short("wh3");
  
  set_long("wh3.\n");

  add_exit(HALL + "wh2", "north", 0, 0, 0);
  add_exit(TOWERS + "swt1", "south", 0, 0, 0);
  reset_room();
}


