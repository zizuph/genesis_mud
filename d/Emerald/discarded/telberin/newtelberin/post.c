#include "defs.h"

inherit TELBERIN_ROOM;
inherit "/d/Genesis/lib/post";

#include <stdproperties.h>
 
void
create_telberin_room()
{
    set_short("Royal Post Office of Telberin");
    set_em_long("The post office of Telberin is a marvel in " +
        "the city. It's quick and efficent and never ceases to " +
        "astound the elves. Several elves busily work here " +
        "sorting all of the mail that comes in and goes out. " +
        "From here, you may send messages to anyone in Emerald " +
        "or to foreign lands. " + get_std_use());

    add_item(({"elves", "elf"}),
        "The elves are hurridely sorting all the mail that " +
        "needs to be delivered. They don't have time to talk " +
        "to you.\n");
    add_item (({ "head postmaster", "postmaster" }),
        "He's supervising his employees, making sure " +
        "they do their work properly.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit("tel04_09", "east");
}
 
void
init()
{
    ::init();
    post_init();
}

void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    post_leave_inv(ob, to);
}
