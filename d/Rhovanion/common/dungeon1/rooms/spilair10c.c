inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
void
create_room() {
   set_short("thingga\n");
   set_long("Webs cover all of this room making it near impossible to move " +
      "without getting fastly stuck within them.  Rubble and debris " +
      "litter this room like sand does the ocean.  There seems to be " +
      "some sort of tunneling going on here as there is what appears " +
      "to be the beginnings of a tunnel in the east section of the " +
      "cavern, but not enough yet to enter it.\n");
   add_item(({"wall","walls","ceiling","floor"}), "They're too covered " +
      "webs for you to see them clearly except the east wall where the " +
      "beginning of the tunnel is.\n");
   add_item(({"web","webs"}), "The webs cover this room, and, despite " +
      "the fact they're threatening to encompass you and the entire room, " +
      "seem to possess an unnerving and startling beauty.\n");
   add_item(({"rubble","debris"}),"Rocks, dirt, and all " +
      "manner of tunneling debris are strewn haphazardly across the " +
      "floor getting stuck in webs from the walls to the ceiling in " +
      "the process.  You notice nothing unusual about them.\n");
   add_item("tunnel","This is the makeshift beginning of a tunnel. " +
      "It opens, or is at least starting to open, into the east wall.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_exit("/d/Rhovanion/common/dungeon1/rooms/spilair10","west");
}
