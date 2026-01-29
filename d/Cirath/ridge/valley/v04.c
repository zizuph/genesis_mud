/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v04.c
* Comments: Valley outside of Tyr
*/

#pragma strict_types
#pragma save_binary
#include "defs.h"
inherit BASE_VALLEY;

void
create_valley()
{
  set_short("Sand Valley");
  set_long("You are standing at the beginning of the valley. It stretches for "
  	+"miles to the southwest. It looks like a lonely place to take a trip. "
  	+"You can't help but think of how much water you would need to make a "
  	+"journey into there.\n");

  add_exit(RIDGE_VALLEY+"v02a.c","north",0,8,0);
  add_exit(RIDGE_VALLEY+"v07.c","south",0,8,0);
  add_exit(RIDGE_VALLEY+"v03.c","west",0,8,0);
  reset_room();
}


