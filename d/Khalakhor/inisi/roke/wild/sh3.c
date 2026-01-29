/*
 * sh3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object k1, k2, k3;

void reset_room();

void
create_room()
{
    set_short("small cave");
    set_long("This is a small cave in one of the huge mountains on Nyreese. " +
             "It is somewhat dark here, but luckily the small opening " +
             "provides enough light for you to be able to see.\n");

    add_item("opening", "The opening leads out from the cave.\n");

    add_exit("sh2", "west");

    reset_room();
}

void
reset_room()
{
    if (k1 || k2 || k3)
        return;

    k1 = clone_object(ROKEDIR + "npc/kobold1");
    k1->equip_me();
    k2 = clone_object(ROKEDIR + "npc/kobold2");
    k2->equip_me();
    k3 = clone_object(ROKEDIR + "npc/kobold3");
    k3->equip_me();

    k1->move(TO);
    k2->move(TO);
    k3->move(TO);

    k1->team_join(k2);
    k1->team_join(k3);

    tell_room(TO, "Some dirty kobolds arrive from the opening.\n");
}
