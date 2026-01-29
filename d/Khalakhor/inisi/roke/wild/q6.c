/*
 * q6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object healer;

void reset_room();

void
create_room()
{
    set_short("The edge of a huge rift");
    set_long("You are standing at the edge of a huge rift. Once " +
             "there was a wooden bridge over it, but many " +
             "centuries of hard usage and weather has made it " +
             "deteriorate and fall into the water deep below. " +
             "The only thing remaining are some wooden poles, " +
             "to which the bridge was tied. " +
             "You secretly wonder what it looked like when it " +
             "fell.\n");

    add_exit("q5", "west");

    add_item("poles", "The poles look old and extremely rotten.\n");
    add_item("ruins", "The rotted remains of an old wooden " +
             "bridge have fallen into the chasm below.\n");
    add_item("rift", "A vast chasm or rift opens up before your " +
             "feet, and you hear the sound of rushing water far below. Ahead " +
             "the mist is like a veil, obstructing your view of the other " +
             "side.\n");
    reset_room();
}

void
reset_room()
{
    if (!objectp(healer))
    {
        healer = clone_object(ROKEDIR + "npc/healernew");
        tell_room(TO, "An old male human sits on a rock.\n");
        healer->move(TO);
    }
}

/* h{r skall man kunna kasta en spell som bygger upp en magisk bro. /gres */
