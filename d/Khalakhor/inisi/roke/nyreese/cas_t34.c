/*
 * cas_t34.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged & Gresolle  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <macros.h>

object knight;

void reset_room();

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("This is just another of those small tower rooms, found " +
             "in almost every castle. However, you feel that this one " +
             "is different. Your feelings may have something to do with " +
             "the small engraving in one of the stones. There is a small " +
             "ladder leading upwards to the top of the tower.\n");

    add_item(({"engraving", "stone"}),
             "Slowly, as you study the ancient letters, a strange tale " +
             "about magic and mighty wizards forms inside your head. The " +
             "last sentences are unreadable but you decide that it has " +
             "something to do with vast forests.\n");
    INSIDE;

    add_item("ladder",
             "The ladder looks like it is going to break any minute.\n");
    add_exit("cas_c12", "northwest");
    add_exit("cas_t44", "up", "@@block");

    reset_room();
}

void
reset_room()
{
    if (knight)
        return;

    tell_room(TO, "A guard arrives\n");

    knight = clone_object(ROKEDIR + "npc/towerg3");
    knight->equip_me();
    knight->move(TO);
}

int
block()
{
    if (MAL("guard"))
    {
        write("You try to climb the ladder, but the guard stops you!\n");
        say(QCTNAME(TP) + " tries to climb the ladder, but is brutally " +
            "stopped by the guard.\n");
        return 1;
    }
    return 0;
}
