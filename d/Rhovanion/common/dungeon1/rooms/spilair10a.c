inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("place\n");
   set_long("This small cavern is covered with webs.  Webs span the " +
      "ceiling, webs cover the walls and floor, and webs cover the bones " +
      "that litter the floor in small piles throughout the room.  There " +
      "is a slight stench of decay here despite the dryness of the air. " +
      "You feel it would be best not to be caught here by the spiders should they " +
      "return\n");
   add_item(({"wall","walls","ceiling","floor"}), "They're too covered " +
      "webs for you to see them clearly.\n");
   add_item(({"web","webs"}), "The webs cover this room, and, despite " +
      "the fact they're threatening to encompass you and the entire room, " +
      "seem to possess an unnerving and startling beauty.\n");
   add_item("bones","These are the bones of the countless victims " +
      "who apparently `encountered' these spiders.\n");
   add_item("piles","These are piles of bones of various types " +
      "scattered throughout the cavern\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair10","east");
}
