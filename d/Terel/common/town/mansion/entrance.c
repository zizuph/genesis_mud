inherit "/std/room";
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

object butler, door;

object xmas;

reset_room() {
   if (!butler) {
      butler = clone_object(MANSION + "mon/butler");
      butler -> move(this_object());
      if (door -> query_open())
      butler -> command("close door");
   }
   if (!xmas) {
	xmas = clone_object(MANSION + "obj/xmas");
	xmas -> move(this_object());
   }
}

create_room() {
   
  set_short("Entry Foyer");
  set_long(break_string(
   "This is the entry foyer of the great mansion. It now lays " +
   "coated in a thick layer of dust. The wood, once fine and smooth " +
   "now splintering and decaying. Even the beautiful oak floor " +
   "boards show cracks and decay. Cobwebs hang from the ceiling " +
   "and from the bronze chandeliers.\n", 70));
   
   /* This is what is needed for the west door. */
   door = clone_object(TOWNDIR + "mansion/ruin_door2");
   door->set_key(89890);
   door->move(this_object());
   
   add_item(({"chandelier", "bronze chandelier", "chandeliers"}),
  "They are shaped like a writhing mass of serpents and have\n"
  + "sockets in which to hold candles. The chandeliers are\n"
  + "old and coated with cobwebs.\n");
  add_item("cobwebs", "You thought you saw a large spider in one of"
  + "the webs...\nbut it was just a shadow.\n");
  add_item(({"floor", "floor boards", "boards"}), "Although "
  + "somewhat damaged they are in a good shape.\n");
  add_item(({"dust", "thick dust"}), "@@sneeze_from_dust");
   add_exit(TOWNDIR + "mansion/wing_w3", "east", 0);
   reset_room();
}

sneeze_from_dust()
{
  say(QCTNAME(this_player()) + " suddenly sneezes due to all the dust.\n");
  tell_room(TOWNDIR + "mansion/wing_w3", "You hear a loud sneeze!\n");
  return("Achoo!  The dust makes you sneeze!\n");
}
