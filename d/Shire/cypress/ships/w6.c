#include "/sys/stdproperties.h"
#include "/d/Shire/cypress/sys/defs.h"
#pragma save_binary

inherit "/std/room";

create_room()
{

  set_short("In the water");
  set_long("You are surrounded by water in all directions " +
    "except to the east were you can see a beach.\n");

  add_prop(ROOM_I_TYPE,ROOM_IN_WATER);
  
  add_exit(ShIP_DIR + "w5", "west", 0,1,1);
  add_exit("/d/Shire/common/greyhaven/pier2a", "east", 0,1,1);

}
