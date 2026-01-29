inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("Mute made this.\n");
   set_long("The passageway tees here in what you figure must " +
      "be the cleanest tunnel you've been in since you got down " +
      "here.  The large, stone blocks in the wall are perhaps " +
      "a shade lighter than the dark, unreflective black as they " +
      "have been or it could be they're just less grimey. " +
      "A pair of sconches adorn the east wall just north and " +
      "south of the east passageway each bearing a single, lit " +
      "torch.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_item(({"block","blocks"}),"These are large, dark blocks of stone " +
      "approximately one by two feet in dimension.  They all appear to " +
      "be nearly identical so you figure they must have been worked on " +
      "by a master stoneworker.\n");
   add_item(({"sconch","sconches"}), "This is a pair of dark, " +
      "filthy copper sconches set just to the north and south of " +
      "the east passageway.  Both are set with a torch.\n");
   add_item(({"torch","torches"}), "These are simple, " +
      "wooden torches with some especially combustive substance " +
      "topping them.  They are burning rather brightly.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/guard6","north");
   add_exit("/d/Rhovanion/mute/dungeon1/guard1","east");
   add_exit("/d/Rhovanion/mute/dungeon1/guard3","south");
}
