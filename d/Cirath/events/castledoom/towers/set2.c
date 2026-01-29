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
  set_short("set2");
  
  set_long("set2.\n");

  add_exit(TOWERS + "set1", "west", 0, 0, 0);
  add_exit(TOWERS + "set3", "southwest", 0, 0, 0);
  add_exit(TOWERS + "set4", "south", 0, 0, 0);
  add_exit(HALL + "eh3", "north", 0, 0, 0);
  reset_room();
}


