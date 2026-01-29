/*
* Created by: Luther
* Date: 19 August 2001
*
* File: /d/Cirath/ridge/valley/v18.c
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
  set_long("You are standing in the belly of the valley. It runs about 100 feet "
  	+"wide before its sides start to climb up. To the northeast you see "
  	+"some ruins and to the southwest is the end of the valley. "
  	+"Looking up the valley edges you see movement.\n");

  add_item("ruins", "Taking a better look at the ruins you can make out a "
  	+"old building in an advanced state of decay.\n");

  add_item(({"movement", "edge"}), "Looking to the side of the valley "
  	+"you can make out something shimmering around, almost like a ghost...\n");

  add_item("end", "Looking southwards you see the end of the valley.\n");

  add_exit(RIDGE_VALLEY+"v14.c","north",0,8,0);
  add_exit(RIDGE_VALLEY+"v15.c","northeast",0,8,0);
  add_exit(RIDGE_VALLEY+"v19.c","east",0,8,0);
  add_exit(RIDGE_VALLEY+"v20.c","southwest",0,8,0);
  add_exit(RIDGE_VALLEY+"v17.c","west",0,8,0);
  reset_room();
}


