/*
 * f10.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object bore1, bore2, warpig;

void reset_room();
void reset_room1();
void reset_room2();

void
create_room()
{
    set_short("Forest on Carisca island");
    set_long("The forest around you is quite dark and damp. The " +
             "trees seem to reach out for you and you hear the " +
             "mating roars of the wild boars in the distance. " +
             "This looks like the home of the wild boars.\n");

    add_exit("f7", "north");
    add_exit("f9", "west");
    reset_room();
}

void
reset_room()
{
    set_alarm(30.0, 0.0, reset_room1);
    if (bore1)
        return;
    bore1 = clone_object(ROKEDIR + "npc/bore1.c");
    bore1->equip_me();
    bore1->move(TO);

    tell_room(TO, "An ugly wild boar enters with a growl.\n");
}

void
reset_room1()
{
    set_alarm(30.0, 0.0, reset_room2);
    if (bore2)
        return;
    bore2 = clone_object(ROKEDIR + "npc/bore2.c");
    bore2->equip_me();
    bore2->move(TO);

    tell_room(TO, "An huge wild boar enters with a growl.\n");
}

void
reset_room2()
{
    if (warpig)
        return;

    warpig = clone_object(ROKEDIR + "npc/warpig.c");
    warpig->equip_me();
    warpig->move(TO);

    tell_room(TO, "A fat warpig enters with an oink.\n");
}
