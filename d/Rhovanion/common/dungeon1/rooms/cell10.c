inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Spooky, eh?\n");
   set_long("This is a small ten foot cell filled " +
      "with dust.  A pair of rusted, chain shackles " +
      "hang from the east wall and a there is a door " +
      "set into the west wall.  It is quite chilly here.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("shackles","This is a pair of rusted, iron " +
      "shackles.\n");
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   clone_object("/d/Rhovanion/common/dungeon1/misc/door12a.c")->move(TO);
}
