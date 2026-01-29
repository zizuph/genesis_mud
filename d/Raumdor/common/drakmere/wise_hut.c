#include "defs.h"
inherit STD_ROOM;
/* By Sarr */

object man;
void reset_room();


void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    ::create_room();
    set_short("Inside a hut");

    set_long("You are in a small hut. There is a large pit in the center "+
    "of the room. The room is bare otherwise.\n");
    add_item("pit","This is a large pit filled with ashes.\n");
    add_exit(DRAKMERE_DIR + "road43","out",0,0);
    reset_room();
}

void
reset_room()
{
    if(!man)
    {
        man = clone_object(COMMON_NPC_DIR + "old_man");
        man->move_living("xxx",TO);
    }
}

