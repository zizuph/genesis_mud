/*
   This is a hut for an eremite. Mortricia 920717
 */
inherit "/std/room.c";
#define HOME_DIR "/d/Terel/common/forest/"
#include <stdproperties.h>
#include <macros.h>

reset_room()
{
   object eremite;
   if (present("eremite"))
      return;
/*
   eremite=clone_object(HOME_DIR + "eremite");
 */
   eremite=clone_object("/d/Terel/mortricia/people/eremite");
   eremite -> move(this_object());
}

create_room()
{
   set_short("A ramshackle hut");
   set_long(break_string("You are inside a very old hut. It must be " +
     "decades since anyone bothered to repair it, and you notice that " +
     "the walls might tumble down on you any minute.\n",70));

   add_item(({"wall", "walls"}), "There is a window in one of the walls.\n");
   add_item(({"window"}), "You wonder why a hut like this has a window.\n");

   add_prop(ROOM_I_INSIDE, 1);

   add_exit(HOME_DIR + "forest25", "west", 0);

   reset_room();
}
