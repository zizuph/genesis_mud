/*
 * cadu_b3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>
#include <ss_types.h>
#include "bridgedefs.h"

void
reset_room()
{
    object guard;
    guard = present("lifeguard_george");
    if (guard && guard->query_name() != "corpse") return;
    guard=clone_object(ROKEDIR + "npc/lifeguard");
    guard->move(this_object());
    tell_room(this_object(), QCNAME(guard) + " arrives.\n");
}

object
query_guard_present()
{
    object guard;
    guard = present("lifeguard_george");
    if (guard && guard->query_name() != "corpse") return guard;
    return 0;
}
   
void
create_room() {
    set_short("Pier");
    set_long("You are on the pier south of Cadu.\n" +
             "To the east the pier continues towards land.\n" +
             "There is a diving tower here, and below you the " +
             "water looks very inviting.\n");

    add_item("tower", "It looks like a normal diving tower.\n");
    add_item("ladder", "The ladder leads up to the tower.\n");

    add_exit("cadu_b2",    "east");
    add_exit("cadu_tower", "up");
    add_exit(WATERROOM, "down","@@move_down");

    BEACH;

    reset_room();
}

int
move_down()
{
    if (TP->query_skill(SS_SWIM) < DONTDIVE)
    {
        write("You don't dare to go down when you're such a lousy swimmer.\n");
        return 1;
    }
    return 0;
}

int
do_dive(string str)
{
    if (!str || str == "")
    {
        if (TP->query_skill(SS_SWIM) < DONTDIVE)
        {
            write("You do not dare to dive when you're such a lousy swimmer.\n");
            return 1;
        }

        write("You dive into the water.\n");
        say(QCTNAME(TP) + " dives into the water.\n");
        tell_room(WATERROOM, QCNAME(TP) + " dives into the water.\n");

        TP->move_living("M", WATERROOM);

        return 1;
    }
    return 0;
}
 
void
init()
{
    ::init();
    add_action(do_dive, "dive");
    add_action(do_dive, "bath");
}
