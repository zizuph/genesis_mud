/* 	lane.c			Styles.   3 Mar 1993
 */

#pragma strict_types

inherit "/std/room";

#include <stdproperties.h>

#include "defs.h"

int fl;

void
create_room()
{
    set_short("A lane to the top of a hill");
    set_long("\n"+
             "A lane leading up to the top of the hill.\n"+
             "The lane is well kept and flowers decorate the edge of the lawn\n"+
             "on both sides.\n"+
             "");

    add_exit("orc_road1","north");
    add_exit("mansion","west");

    add_item(({"flowers","lawn","lane" }), "");

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    fl = random(10)+4;
}

void
reset_room()
{
    fl += random(5);
    if (fl>25) fl = 25;
}

int
clone_flower()
{

    object flower;
    return 1;

    flower = clone_object("/std/heap");
    flower -> set_name("flower");
    flower -> set_pname("flowers");
    flower -> set_adj("yellow");
    flower -> set_long("A beatutful yellow flower.\n");

    flower -> set_heap_size(1);

    return flower->move_object(this_player());
}

int
pick(string what)
{
    if (what == "flower" || what == "flowers") {
        if (!fl) {
            write("You really shouldn't do that. "+
                  " There are not that many left.\n");
            return 1;
        }
        if (!clone_flower()) {
            if (!--fl)
                write("You pick a yellow flower. "+
                      "One of the few that's left.\n");
            else
                write("You pick a yellow flower.\n");
            return 1;
        }
        write("The flower says: Go pick on someone else!\n");
        return 1;
    }
}

void
init()
{
    ::init();

    add_action(pick,"pick");
}

