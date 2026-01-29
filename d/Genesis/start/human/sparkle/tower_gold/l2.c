#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("The 2nd floor");
    set_long("\n"+
             "This is the second floor.\n"+
             "From here you can enter the offices of two of the most favoured\n"+
             "realms in the world. Decorations on the walls and around the room\n"+
             "are first class and just standing here gives you a comfortable feeling.\n"+
             "There is a beautiful silver sign on the north wall.\n"+
             "");

    add_item(({"floor" }),"You can almost see your own reflection.\n"+
    "");
    add_item(({"door" }),"Which one? East or west?\n"+
    "");
    add_item(({"stairs" }),"The stairs lead up to the third floor as well as down to the first.\n"+
    "");
    add_item(({"west door" }),"You get a strong feeling of well being as you approach\n"+
    "the west door. You feel actually quite happy. It is made of\n"+
    "polished oak and is very skillfully carved.\n"+
    "");
    add_item(({"east door" }),"This is a genuine sturdy oak door. It is well crafted and shows\n"+
    "proof of excellent workmanship.\n"+
    "");
    add_item(({"sign" }),"@@sign");

    add_exit(TOWN_DIR + "l1", "down");
    add_exit(TOWN_DIR + "l3", "up");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
