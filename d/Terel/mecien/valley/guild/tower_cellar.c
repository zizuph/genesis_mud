/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>

#define PATH "/d/Terel/mecien/valley/guild/"

object door;

reset_room(arg){
door->close_door();
}
create_room(){

set_short("Tower Cellar");
set_long("Dark and shrouded in a mantle of mist, this circular\n"
  +"hall is the cellar of the tower. Water drips from the\n"
  +"the low ceiling, condensing from the mists. The walls are\n"
   +"made from rounded grey stones.\n");

door=clone_object(PATH + "crypt/cdoor1");
door->move(this_object());
door->set_key(909090);

add_prop(ROOM_I_LIGHT, 0);

add_item(({"stairs", "staircase"}), 
  "The steps are dark slate, but strong. Up the staircase it\n"
  +"gets lighter.\n");

add_item("walls", "They are made from small round grey stones.\n");

add_exit(PATH + "tower1", "up", 0);

reset_room();
}


