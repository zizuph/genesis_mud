#include "local.h"

inherit BUILDING_BASE;
inherit "/d/Genesis/lib/post";

void
create_building()
{
    set_up_cords(5,13);
    add_exit(ROOM_DIR + "building_5_12", "north");

    set_short("within the Post Office of Clach Dun");
}

void
init()
{
    ::init();
    post_init();
}

void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}
