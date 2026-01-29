#include "../defs.h"

inherit TELBERIN_BUILDING;
inherit "/d/Genesis/lib/post";

#include <stdproperties.h>
 
void
create_telberin_building()
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

public mixed
query_location_ids()
{
    return "[the] 'post' / 'postal' [office]";
}

public mixed
query_location_closed()
{
    return 0;
}

public mixed
query_location_desc()
{
    return "It's a post office building.\n";
}
