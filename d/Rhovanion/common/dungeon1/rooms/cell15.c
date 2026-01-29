inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Bastingo!\n");
   set_long("This is a small room nearly fifteen feet long by about " +
      "ten wide.  A dark passageway leads south out of here and an odd " +
      "mist is rolling across the floor.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item("mist","These odd vapours seem to be coming from nowhere. " +
      "They are rolling about the floor making it hard to see.\n");
   add_item("floor","The floor is covered with an odd, rolling mist " +
      "making it hard to see.\n");
   clone_object("/d/Rhovanion/common/dungeon1/living/bats.c")->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/misc/door8.c")->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/misc/door9.c")->move(TO);
   clone_object("/d/Rhovanion/common/dungeon1/misc/door10.c")->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/cell16","south");
}
