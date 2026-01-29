inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   int i;
   set_short("Boyeeee!\n");
   set_long("This is a small ten foot cell devoid of " +
      "all features save its door and the large, stone " +
      "blocks that comprise its walls.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   for (i = 0; i < 2 + random(3); i++)
   clone_object("/d/Rhovanion/mute/dungeon1/skeleton1.c")->move(TO);
   clone_object("/d/Rhovanion/mute/dungeon1/door10a.c")->move(TO);
}
