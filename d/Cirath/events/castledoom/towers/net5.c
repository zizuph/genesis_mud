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
  set_short("net5");
  
  set_long("net5.\n");

  add_exit(TOWERS + "net6", "east", 0, 0, 0);
  add_exit(TOWERS + "net7", "south", 0, 0, 0);
  add_exit(TOWERS + "net8", "southeastt", 0, 0, 0);
  reset_room();
}


