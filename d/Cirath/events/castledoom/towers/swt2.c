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
  set_short("swt2");
  
  set_long("swt2.\n");

  add_exit(TOWERS + "swt1", "west", 0, 0, 0);
  add_exit(TOWERS + "swt3", "southwest", 0, 0, 0);
  add_exit(TOWERS + "swt4", "south", 0, 0, 0);
  add_exit(COURT + "cy7", "northeast", 0, 0, 0);
  reset_room();
}


