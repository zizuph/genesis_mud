/*
 *  Path leading up the mountain
 */

inherit "/std/room";

#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "defs.h"

int rock_open, good_cnt;

create_room() {
   rock_open = 0;
   set_short("Path");
   set_long("@@my_long");

   add_item(({"rocks","rock walls"}),"@@rock_walls");


   //   add_exit(HINROOM_DIR + "path3","north");
   add_exit(HINROOM_DIR + "path4","north","@@closed_road",0);
   add_exit(HINROOM_DIR + "path5","south");
   add_exit(MOUNT_DIR + "path/p1","west");

   add_prop(ROOM_I_INSIDE, 0);  /* This room is outside */

   reset_room();
}

closed_road()
{
  write("Magically you are hindered in going north by Nob Nar's wish.\n");
  return 0;
  // by my wish : Boromir
}

reset_room()
{
   if (!present("rock") && !random(4))
      clone_object(OBJ_DIR + "smallrock")->move(this_object());
}

my_long() {
   return break_string(
      "You are walking on a path between rising walls of rock. "
    + "The way south leads down and away from this mountainous "
   + "area. North leads up the mountain, and west a new path "+
   "winds up the mountain.\n",70);
}


rock_walls() {
   return break_string(
      "The rock walls are gradually growing too steep to climb without the "
    + "necessary climbing gear.",70);
}
