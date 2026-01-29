#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_OUTSIDE;

create_tantallon_room()
{
    set_short("On path");
    set_long(
        "You are standing on a twisty little path. It both leads south into " +
        "Tantallon and east following those big mountains you can see north " +
        "from here. West stands a tent, while a small path leads north.\n");

    add_item(({"mountain","mountains"}), BS(
        "The mountains are very high. The look very dark and unfriendly. In " +
        "fact most people avoid getting any closer than this to them.", SL));
    add_item("path",
        "It looks well used.\n");
    add_item(({"tent", "west tent"}), BS(
    "It's a small grey tent. There isn't a sound to be heard from it. " +
        "You can enter it by walking west.", SL));

    add_exit(TDIR + "city4", "east", 0);
    add_exit(TDIR + "city6", "south", 0);
    add_exit(TDIR + "tent8", "west", 0);
    add_exit(TDIR + "griffon/landing2", "north", 0);
}
