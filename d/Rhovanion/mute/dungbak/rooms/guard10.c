inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("brief mode\n");
   set_long("You are now in a small room about ten " +
      "feet square in size serving as an intersection of " +
      "sorts.  There are two small passageways, one leading " +
      "west and one south, here, and a door is set into the " +
      "east wall.  The heavy scent of wyrmman rests on the " +
      "warm, warm air here.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   clone_object("/d/Rhovanion/mute/dungeon1/door7a.c")->move(TO);
   add_exit("/d/Rhovanion/mute/dungeon1/guard12","west");
   add_exit("/d/Rhovanion/mute/dungeon1/guard11","south");
}
