#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/guild/gondor/no_theft";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_room()
{
   set_short("a corridor inside the Gondorian Rangers Guild");
   set_long("You are standing in the west end of a lamplit corridor. Right\n"+
      "south is a door, from which you can hear the sounds of song and\n"+
      "laughter. The words 'Seven Stars Inn' are written on the door.\n"+
      "An open doorway leads north into the Rangers Equipment Store.\n"+
    "To the west is a room where the Rangers may write mail in peace.\n"+
      "The corridor continues east to the entryhall of the Guild.\n");
   add_exit(RANGER_DIR + "gondor/shop",      "north", 0);
   add_exit(RANGER_DIR + "gondor/post",      "west",  0);
   add_exit(RANGER_DIR + "gondor/boardhall", "east",  0);
   add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_M_NO_STEAL, no_theft);
   clone_object(RANGER_DIR+"obj/inn_door1")->move(TO);
}
