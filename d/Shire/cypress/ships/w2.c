#include "/sys/stdproperties.h"
#include "/d/Shire/cypress/sys/defs.h"
#pragma save_binary

inherit "/std/room";

create_room() {

  set_short("In the middle ofa great ocean");
  set_long("You are surrounded by water in all directions.\n");

  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
  
  add_exit(SHIP_DIR + "w1", "west", 0,1,1);
  add_exit(SHIP_DIR + "w3", "east", 0,1,1);

}
