/*
 * f8.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object bore1, warpig;

void reset_room();
void reset_room2();

void
create_room()
{
    set_short("Forest on Carisca island");
    set_long("The forest around you is quite dark and damp. The " +
             "trees seem to reach out for you and you hear the " +
             "mating roars of the wild boars in the distance.\n");

    add_exit("f6", "north");
    add_exit("f9", "east");

    reset_room();
}

void
reset_room()
{
    if (!present("egg", TO))
        clone_object(ROKEDIR + "obj/car_egg")->move(TO);
    if (bore1)
        return;
    set_alarm(300.0, 0.0, reset_room2);
    bore1 = clone_object(ROKEDIR + "npc/bore1.c");
    bore1->equip_me();
    bore1->move(TO);

    tell_room(TO, "An ugly wild boar enters with a growl.\n");
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
