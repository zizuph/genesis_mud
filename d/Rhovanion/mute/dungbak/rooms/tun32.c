inherit "/std/room.c";
#include "/d/Rhovanion/defs.h"
create_room() {
   set_short("t\n");
   set_long("The passageway turns slightly here, but the large stone " +
      "blocks that comprise the wall manage to handle the kink quite well. " +
      "Truly this place was built by a master craftsman.  There is " +
      "an odd odour in the air the likes of which you've never " +
      "smelled before.\n");
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_LIGHT, 0);
   add_item(({ "block", "blocks" }), "These are large, dark blocks of " +
      "stone approximately one by two feet in dimension.  They all " +
      "appear to be nearly identical so you figure they must have been " +
      "worked on by a master stoneworker.\n");
   add_item("stone","The stone in the blocks is very dark and " +
      "lusterless nearly black in color.\n");
   add_exit("/d/Rhovanion/mute/dungeon1/int10.c","southwest");
   add_exit("/d/Rhovanion/mute/dungeon1/int11.c","north");
}
