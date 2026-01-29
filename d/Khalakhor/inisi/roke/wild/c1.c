/*
 * c1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object kato;

void reset_room();

void
create_room()
{
    set_short("cave entrance");
    set_long("You are surrounded by mysterious sculptures, and you " +
             "realize that this must be a holy place of some ancient " +
             "religion. The cave leads west into a smaller chamber, and " +
             "further east into a dark hole " +
             "from which you detect a faint smell of sulphur.\n");

    INSIDE;

    add_item("hole", "It looks very dark.\n");
    add_item("sculptures", "They look rather nasty.\n");

    add_exit("c5", "west");
    add_exit("c2", "east");
    add_exit("d6", "down");

    reset_room();
}

void
reset_room()
{
    if (!objectp(kato))
    {
        reset_euid();
        kato = clone_object(ROKEDIR + "npc/kato");
        kato->equip_me();
        kato->arm_me();
        kato->move_living("arrives creeping", this_object());
    }
}
