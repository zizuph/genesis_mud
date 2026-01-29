/*
 * coded by Amelia 12/25/97
 * old forest room north of Ten Alders
 * specials:  room_tell.c and search for herbs
*/

#pragma no_clone
#pragma strict_types

inherit "/d/Earthsea/std/room";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

public void
create_earthsea_room()
{
    set_short("Dark pit");
    set_long("You find yourself at the bottom of a " +
        "dark pit, which functions as an effective trap since " +
        "the walls are nearly vertical. On the ground are " +
        "sharp rocks and briars. There is not much else " +
        "here.\n");
    add_item((({"rocks", "sharp rocks", "briars"})),
        "You landed on sharp rocks and briars when you " +
        "fell.\n");
    add_item("walls", "The walls of the pit are nearly vertical, " +
        "and slimy with mud and sludge, are very difficult to " +
        "climb.\n");
    add_item((({"ground", "floor"})),
        "The floor of the pit is oozing with sludge, and sharp " +
        "rocks lay all over it.\n");
    add_prop(ROOM_I_LIGHT, -1);
}

public int
climb(string str)
{
    object tp = this_player();

    if(str != "up" && str != "out")
    {
        return notify_fail("Climb where?\n");
    }

    if(((tp->query_skill(SS_CLIMB) > 45) &&
        (tp->query_stat(SS_DEX) > 20)) ||
        random(20) > 14)
    {
        say(QCTNAME(tp) + " scrambles up the sides of the pit.\n");
        write("You scramble up the nearly vertical sides of the pit!\n");
        tp->move_living("M", "/d/Earthsea/gont/tenalders/high_fall/trail3", 1, 0);
        say(QCTNAME(tp) + " climbs in.\n");
        return 1;
    }

    tp->add_fatigue((tp->query_max_fatigue() / 5) * -1);
    tp->heal_hp((tp->query_max_hp() / 20) * -1);

    write("You try to climb up the nearly vertical wall but fall back " +
        "in a heap!\n");
    say(QCTNAME(tp) + " tries to climb up the wall, but falls back " +
        "in a heap.\n");

    return 1;
}

public void
init()
{
    object tp = this_player();

    ::init();
    add_action(climb, "climb");

    write("Ouch!\n");
    tp->heal_hp((tp->query_max_hp() / 5) * -1);
}
