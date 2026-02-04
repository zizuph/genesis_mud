/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

object mon;

#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){

set_short("Hallway");
set_long("Dismal in its antiquity, this small upper hall stands\n"
    + "silent, the old stone barren and voiceless. The air is\n"
    + "filled with incense, forming a thick cloud that drifts\n"
    + "about like some mysterious presence. A black iron lamp\n"
    + "hangs from the ceiling.\n"
);

  add_item(({"cloud", "incense"}),
   "A cloud of incense, it drifts about with a purifying essence.\n");
  add_item("lamp", "It it a large black, wroght iron lamp.\nIt hangs "
   + "from a chain to illuminate the hall.\n");
add_item("chain", "Of black iron, it holds a lamp.\n");
add_exit(PATH + "foyer", "down", 0);
add_exit(PATH + "u_hall2", "south", 0);
add_exit(PATH + "post", "west", 0);

seteuid(getuid());
mon = clone_object(PATH + "mystic3");
mon->move(this_object());

}
