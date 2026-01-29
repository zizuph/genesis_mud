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
  set_short("set1");
  
  set_long("set1.\n");

  add_exit(TOWERS + "set2", "east", 0, 0, 0);
  add_exit(TOWERS + "set3", "south", 0, 0, 0);
  add_exit(TOWERS + "set4", "southeast", 0, 0, 0);
  add_exit(COURT + "cy9", "northwest", 0, 0, 0); 
  reset_room();
}


