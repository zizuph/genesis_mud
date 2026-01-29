/*
 * Base file for Temples
 * -- Finwe, July 2006
 */
#pragma no_clone
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <terrain.h>

inherit "/std/room";
inherit "/d/Faerun/std/cmd_parse";
inherit "/d/Faerun/temples/default_info.c";

void create_temple()
{
}

void donate_box(string str);

void
create_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Inside a ");
    set_long("This is the inside of a temple to one of the deities of " +
        "Faerun. There is a sign on a wall to read.\n");

    add_item("sign", "Maybe you should read it.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");

    donate_box("");
    create_temple();
}


void
init()
{
    ::init();
}

void
donate_box(string str)
{
    add_item(({"box", "iron box"}),
        "The box is square shaped and made of strong iron. On the top is " +
        "a slot where you can insert platinum coins. To become a follower, " +
        "it will cost you 1 platinum coin. When you insert your coin " +
        "into the box, you will receive an emblem to prove you're a " +
        "follower of " + str + ".\n");
}
