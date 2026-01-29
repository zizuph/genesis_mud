

inherit "/std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/mountains"

create_room(){
   
   set_short("Tunnel");
   set_long(
      "Crudely carved from the mountains rock, this dark tunnel slopes\n"
      +"slightly downward to the east, rising to the west.\n");
   
   add_exit(PATH + "/t2", "east", 0);
   
   add_exit(PATH + "/cavern", "west", 0);
   
   add_prop(ROOM_I_LIGHT, 0);
   add_prop(ROOM_I_INSIDE, 1);
   
}


