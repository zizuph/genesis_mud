/*
* Created by: See /d/Cirath/events/castledoom/code.txt
* Date: Dec 2001 
*
* Comments: Special rooms
*/

#include "defs.h"

inherit CASTLEDOOM + "base_inside";

void
create_inside_room()
{
  set_short("sr2");
  
  set_long("sr2.\n");

  add_exit(HALL + "nh2", "north", 0, 0, 0);
  reset_room();
}


