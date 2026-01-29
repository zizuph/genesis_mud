inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
#include <macros.h>
void
create_room() {
   set_short("home\n");
   set_long("You have made it, it would seem, to the final lair " +
      "of the large spiders who reside here.  It is a small `natural " +
      "cavern' of sorts with webs covering the entirety of the room. " +
      "One web in particular attracts your attention spanning all of " +
      "the south wall, part of the ceiling, and even a bit of the floor. " +
      "     Irregular from other lairs you've seen, this cavern is incredibly " +
      "clean and orderly;  aside from the webs that is.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item("webs","The webs here are unusually large, well " +
      "built, and beautiful.  They cover everything.\n");
   clone_object("/d/Rhovanion/common/dungeon1/gear/web.c")
   ->move(TO);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair10","north");
}
