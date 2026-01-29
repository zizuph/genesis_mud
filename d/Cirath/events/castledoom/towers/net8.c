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
  set_short("net8");
  
  set_long("net8.\n");

  add_exit(TOWERS + "net5", "northwest", 0, 0, 0);
  add_exit(TOWERS + "net6", "north", 0, 0, 0);
  add_exit(TOWERS + "net7", "west", 0, 0, 0);
  reset_room();
}


