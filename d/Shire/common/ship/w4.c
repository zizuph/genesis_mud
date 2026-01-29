#include "/sys/stdproperties.h"
#include "defs.h"
#pragma save_binary

inherit "/std/room";

create_room() {

  set_short("In the water");
  set_long("You are surrounded by water in all directions.\n");

  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
  
  add_exit(STAND_DIR + "w3", "west", 0,1,1);
  add_exit(STAND_DIR + "w5", "east", 0,1,1);

}
