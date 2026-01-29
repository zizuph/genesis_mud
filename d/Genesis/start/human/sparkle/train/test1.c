/* test room for calling up item descs from another file */

#pragma strict_types

inherit "/std/room.c";

#include <macros.h>
#include <stdproperties.h>

string medusa_desc();
string my_long();

public void
create_room()
{
    set_short("before a gate");
    set_long(my_long);

    add_item(({"medusa","medusa head"}), "@@medusa_desc");

    add_exit("gate12", "north", 0, 1);

    reset_room();
}

string
my_long()
{
    cat("/d/Genesis/start/human/sparkle/obj/pics/gates.pic");
    return "";
}

string
medusa_desc()
{
    cat("/d/Genesis/start/human/sparkle/obj/pics/medusa.pic");
    return "";
}
