#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "defs.h"

void
create_room()
{
    set_short("Small room");
    set_long("You have walked into a small dark room that contains\n"+
             "no windows. There is a small portrait mounted upon the\n"+
             "wall. You notice a very small hole in the wall to your\n"+
             "northwest. You can go south back through the archway to\n"+
             "leave this room.\n");

    add_exit("r4", "south");
    add_prop(ROOM_I_INSIDE, 1);
    add_item(({"portrait", "small portrait"}), "For some odd " +
    "reason, the portrait resembles you!\n");
    add_item("hole",
             "A small hole that looks just large enough to crawl through.\n");

    add_cmd_item(({"northwest", "hole"}), "enter", "@@enter");
    add_cmd_item("hole","enter","@@enter");
}

string
enter()
{
    write("You just manage to squeeze through the hole. It is a good\n"+
          "thing that you are not clostrophobic, or are you?\n");
    set_dircmd("hole");
    TP->move_living("through the hole", S_LOCAL_ROOM_DIR+"hiderm");
    return "Aahh! It feels good to stand up again!\n";
}

