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
  set_short("net3");
  
  set_long("net3.\n");

  add_exit(TOWERS + "net1", "north", 0, 0, 0);
  add_exit(TOWERS + "net2", "northeast", 0, 0, 0);
  add_exit(TOWERS + "net4", "east", 0, 0, 0);
  add_exit(COURT + "cy3", "southwest", 0, 0, 0);
  reset_room();
}


