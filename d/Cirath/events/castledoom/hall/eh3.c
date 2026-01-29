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
  set_short("eh3");
  
  set_long("eh3.\n");

  add_exit(HALL + "eh2", "north", 0, 0, 0);
  add_exit(TOWERS + "set2", "south", 0, 0, 0);
  reset_room();
}


