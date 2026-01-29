/* Ashlar, 20 Oct 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <macros.h>
#include "../guild/guild.h"

inherit TEMPLE_BASE;
inherit "/lib/guild_support";

void
reset_neraka_room()
{
}

string
long_descr()
{
    return "You are in a small dark room. A soft carpet covers the floor, " +
    "where you can meditate on your training. You may also list guilds " +
    "here.\n";
}

void
create_neraka_room()
{
    set_short("small dark room");
    set_long("@@long_descr");

    add_temple_items();
    add_item(({"carpet","soft carpet"}),
    "It feels soft and comfortable. It is dark, like the rest of the room.\n");

    reset_room();

    add_exit(NTEMPLE + "start", "north");
}

void
init()
{
    ::init();

    init_guild_support();
}
