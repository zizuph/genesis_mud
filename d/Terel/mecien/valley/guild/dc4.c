inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/guild/"
create_room(){
   
   set_short("Dark Cavern");
   set_long(
      "A craggy dark cavern, roughly hewn, except for the south side, where " +
      "the stone is cut very clear. It changes color to aquamarine. " +
      "Upon the floor are set seven silver stars.\n");
   
   
   add_item("stars", "They are silvery and set into the floor.\n");
   add_item("floor", "It is decorated with seven stars.\n");
   add_prop(ROOM_I_LIGHT, 0);
   add_exit(PATH + "dc3", "north", 0);
  add_exit("/d/Terel/mecien/mountains/archcham", "south", 0);
   
   
}
