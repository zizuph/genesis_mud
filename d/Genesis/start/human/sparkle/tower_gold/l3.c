#pragma save_binary
#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>

#include "../defs.h"

void
create_room()
{
    set_short("3rd floor");
    set_long("\n"+
             "The 3rd floor.\n"+
             "A soft rug is laid on the stone floor. There are four exits, in addition\n"+
             "to the stairs, since the offices of four realms share this level.\n"+
             "On the wall next to the stairs is a small wooden sign.\n"+
             "");


    add_item(({"floor" }),"It is a solid stone floor.\n"+
    "");
    add_item(({"rug" }),"A nice soft woven white rug.\n"+
    "");
    add_item(({"stairs" }),"The stairs lead up to the fourth floor as well as down to the second.\n"+
    "");
    add_item(({"door" }),"Which one?\n"+
    "");
    add_item(({"north door" }),"A sturdy wooden door.\n"+
    "");
    add_item(({"west door" }),"A sturdy wooden door.\n"+
    "");
    add_item(({"east door" }),"A sturdy wooden door.\n"+
    "");
    add_item(({"south door" }),"A sturdy wooden door.\n"+
    "");
    add_item(({"sign" }),"@@sign");

    add_exit(TOWN_DIR + "l2", "down");
    add_exit(TOWN_DIR + "l4", "up");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
}
