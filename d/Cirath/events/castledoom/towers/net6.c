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
  set_short("net6");
  
  set_long("net6.\n");

  add_exit(TOWERS + "net2", "down", 0, 0, 0);
  add_exit(TOWERS + "net5", "west", 0, 0, 0);
  add_exit(TOWERS + "net7", "southwest", 0, 0, 0);
  add_exit(TOWERS + "net8", "south", 0, 0, 0);
  add_exit(TOWERS + "net10", "up", 0, 0, 0);
  reset_room();
}


