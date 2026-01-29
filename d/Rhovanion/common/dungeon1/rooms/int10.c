inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
create_room() {
   set_short("sorry, brief jist don't work here\n");
   set_long("Here, the passageway splits off in three directions. " +
      "All three tunnels leading away from this intersection of sorts " +
      "are all too dark to see down.\n");
   add_item(({ "block", "blocks" }), "These are large, dark blocks of " +
      "stone approximately one by two feet in dimension.  They all " +
      "appear to be nearly identical so you figure they must have been " +
      "worked on by a master stoneworker.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun30","west");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun31","south");
   add_exit("/d/Rhovanion/common/dungeon1/rooms/tun32","northeast");
   clone_object("/d/Rhovanion/common/dungeon1/living/bats.c")
   ->move(TO);
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
}
