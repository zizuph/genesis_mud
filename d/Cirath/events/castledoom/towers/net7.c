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
  set_short("net7");
  
  set_long("net7.\n");

  add_exit(TOWERS + "net5", "north", 0, 0, 0);
  add_exit(TOWERS + "net6", "northeast", 0, 0, 0);
  add_exit(TOWERS + "net8", "east", 0, 0, 0);
  reset_room();
}


