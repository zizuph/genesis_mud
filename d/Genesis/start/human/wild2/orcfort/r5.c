#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "local.h"

void
create_room()
{
    set_short("Small room");
    set_long("You have walked into a small dark room that contains " +
             "no windows. There is a small portrait mounted upon the " +
             "wall. You notice a small hole in the wall to your " +
             "northwest. You can go south back through the archway to " +
             "leave this room.\n");

    add_exit(ORC+"r4", "south");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "orc_temple.txt");

    add_item(({"portrait", "small portrait"}), "For some odd " +
    "reason, the portrait resembles you!\n");
    add_item("hole",
             "A small hole that looks just large enough to crawl through.\n");

    add_cmd_item(({"northwest", "hole", "through hole", "into hole"}),
        ({"enter", "crawl"}), "@@enter");
//    add_cmd_item("hole","enter","@@enter");
}

string
enter()
{
    write("You just manage to squeeze through the hole. It is a good "+
          "thing that you are not claustrophobic, or are you?\n");
    set_dircmd("hole");
    TP->move_living("through the hole", ORC+"hiderm");
    return "Aahh! It feels good to stand up again!\n";
}
