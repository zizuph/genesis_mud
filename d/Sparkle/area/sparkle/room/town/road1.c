#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Sparkle Road");
    set_long("\n"+
             "The north end of Sparkle road.\n"+
             "You are standing in front of the post office and the " +
             "sparkle office of the Archives of Genesis.\n"+
             "The stockade, running around the village, prevents you\n"+
             "from going further north. The road continues south.\n"+
             "");

    add_item(({"stockade" }),"It is quite high and well built.\n"+
    "");
    add_item(({"post office","post","office","road" }),"");

    add_exit("road2","south");
    add_exit(S_DOMAIN_START_DIR + "human/post","east");
    add_exit("notary_room","west");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}

