/*
 * cas_c10.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

int last;
int idle;

void statue_msg();
void init_statue();

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("You are in a long corridor leading east and west in the castle.\n" +
             "Along the walls you see small statuettes showing multiple-armed " +
             "humanoids wielding different kinds of weapons and standing in " +
             "different bodily positions. They are all looking in your direction. " +
             "This is really a place full of magic. \n");

    add_exit("cas_c9", "west");
    add_exit("cas_c11", "east");

    add_item("statue", "The little nasty statue is staring at you.\n");

    idle = 1;
    init_statue();
}

void
init_statue()
{
    last = time();
    if (idle)
    {
        set_alarm(itof(5 + random(5)), 0.0, statue_msg);
        idle = 0;
    }
}

void
init()
{
    ::init();
    init_statue();
}

void
statue_msg()
{
    if (random(2))
        tell_room(TO, "The small statue snatches after you!\n");
    else
        tell_room(TO, "Suddenly you hear a nasty growl from one of the statues!\n");

    if (time() - last > 120)
    {
        idle = 1;
        return;
    }
    set_alarm(itof(15 + random(5)), 0.0, statue_msg);
}
