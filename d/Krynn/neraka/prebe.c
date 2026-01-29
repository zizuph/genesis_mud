/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

create_tantallon_room()
{
    set_short("In front of a bridge");
    set_long(BS(
        "You are standing on vast plain, you feel the wind in your hair. " +
        "West you can see a small river and over it stands a bridge. Behind " +
        "the bridge you can see a small city. East a vast plain stretches " +
        "out.", SL));

    add_item(({"city", "town"}), BS(
        "You can't see much of it, maybe if you go west to the bridge you'll " +
        "get a better look of it.", SL));
    add_item("bridge",
        "It's an old fashioned stone bridge, it looks quite safe.\n");
    add_item("river", BS(
        "The river runs from north to south. The only way to cross it is on " +
        "that bridge.", SL));
    add_item("plain",
        "It's just very very big, nothing interesting.\n");

    add_exit(TDIR + "bridgee", "west", 0);
    add_exit(TDIR + "prebe", "east", "@@construction");
}

construction()
{
    write("This exit is closed for now.\n");
    return 1;
}
