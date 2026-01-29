/*
 * c2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>

int rope;

void
create_room()
{
    set_short("inside cave");
    set_long("This is the dark inside of the cave. The walls are rather " +
             "damp, and looks like the perfect place to grow mushrooms " +
             "In the ground is a hole leading down, and next to the hole " +
             "you see a sturdy iron ring, securely fastened in the mountain.\n");

    DARK;
    INSIDE;

    rope = 0;

    add_item("ring", "@@ring");
    add_item("hole", "The hole leads down, deep into the mountain.\n");
    add_item("walls", "They are extremly damp.\n");

    add_exit("c1", "west");
    add_exit("c3", "down", "@@block");
}

int
block()
{
    if (!rope)
    {
        write("You don't dare to jump down there.\n");
        return 1;
    }
    say(QCTNAME(TP) + " climbs down on the rope.\n");
    write("You climb down on the rope.\n");
    return 0;
}

string
ring()
{
    if (!rope)
        return "You could most likely tie something to it.\n";
    return "Someone has tied a rope to it.\n";
}

void
init()
{
    ::init();

    add_action("tie", "tie");
    add_action("untie", "untie");
}

int
tie(string s)
{
    object ob;

    NF("Tie what to what?\n");
    if (s != "rope to ring")
        return 0;

    NF("You wish that you have a rope.\n");
    if (!(ob = present("rope", TP)))
        return 0;

    NF("Someone has already tied a rope to the ring.\n");
    if (rope)
        return 0;

    ob->move(TO);
    ob->set_no_show_composite(1);
    ob->add_prop(OBJ_I_NO_GET, "The rope is securely tied to the ring.\n");

    add_my_desc("There is a rope hanging down into the hole.\n", ob);
    rope = 1;

    write("You tie the rope to the ring, and throw the other end " +
          "into the hole.\n");
    say(QCTNAME(TP) +
        " ties a rope to the iron ring, and throws it into the hole.\n");

    return 1;
}

int
untie(string s)
{
    NF("Untie what?\n");
    if (s != "rope")
        return 0;

    if (!rope)
        return 0;

    NF("The knots are too hard.\n");
    if (rope)
        return 0;
}
