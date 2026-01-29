#pragma strict_types

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "defs.h"

object figure;

void
create_room()
{
    set_short("Musty room");
    set_long("This is an extremely musty and smelly room. It looks\n"
             + "oddly empty. You can crawl back through the small hole \n"
             + "in the wall from which you came.\n");

    add_item(({"hole in the wall", "hole"}),
             "It seems quite small.\n");
    add_item(({"stones", "stone"}), "They are all cut the wrong way, "+
    "and are the incorrect size.\n");
    add_prop(ROOM_I_LIGHT, -2);
    add_prop(ROOM_I_INSIDE,1);


    add_item("hole",
             "A small hole that looks just large enough to crawl through.\n");

    add_cmd_item(({"northwest", "hole"}), "enter", "@@enter");
    add_cmd_item(({"northwest", "hole", "through hole", "back",
                   "through small hole", "back through hole",
                   "back through small hole" }), 
                   "crawl", "@@enter");

    reset_room();
}

void
reset_room()
{
    if(!figure)
    {
        figure = clone_object(S_LOCAL_OBJ_DIR + "figure");
        figure->add_prop(OBJ_I_HIDE, 20);
        figure->move(TO);
    }
}

string
enter()
{
    write("You just manage to squeeze through the hole. It is a good\n"+
          "thing that you are not claustrophobic, or are you?\n");
    set_dircmd("hole");
    TP->move_living("through the hole", S_LOCAL_ROOM_DIR + "r5");
    return "Aahh! It feels good to stand up again!\n";
}

