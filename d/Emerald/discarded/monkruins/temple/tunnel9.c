inherit "/std/room";

#include "/d/Emerald/defs.h"

void create_room()
{
   add_prop(ROOM_I_INSIDE, 1);
   set_short("Escape tunnel");
   set_long("   The tunnel continues east and there is an exit over "+
            "you. It's bright enough to see the ground.\n\n");

   add_item("ground","It's soft.\n");

   add_exit(TEMPLE_DIR + "tunnel8", "east", 0);
   add_exit(TEMPLE_DIR + "clearing", "up", 0);
}
