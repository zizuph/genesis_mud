inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
create_room() {
   set_short("t\n");
   set_long("This passageway is dark and cold, constructed still " +
      "of large stone blocks.  Your footsteps sound hollow and cold " +
      "upon the smooth stone of the floor.  There is a door on the " +
      "west wall.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({ "block", "blocks" }), "These are large, dark blocks of " +
      "stone approximately one by two feet in dimension.  They all " +
      "appear to be nearly identical so you figure they must have been " +
      "worked on by a master stoneworker.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   clone_object("/d/Rhovanion/mute/dungeon1/door1_a.c")->move(TO);
   add_exit("/d/Rhovanion/mute/dungeon1/int10.c","east");
}
