/*
 * f9.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* ged */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object hoodman;

void reset_room();

void
create_room()
{
    set_short("Forest");
    set_long("This is the northern edge of the forest. To the north " +
             "you can see a few mountains in the distance, and to the " +
             "south of you is a small pond surrounded by thick forest. " +
             "It might be hard to go south because there are many small " +
             "thick bushes in the way.\n");
    add_item(({"bush", "bushes"}), "These bushes have very sharp thorns.\n");

    add_exit("fb", "south", "@@block");
    add_exit("f8", "west");
    add_exit("fa", "east");

    reset_room();
}

int
block()
{
    write("Ouch the bushes have sharp thorns !\n");
    return 1;
}

void
reset_room()
{
    if (!hoodman)
    {
        tell_room(TO, "A hooded human arrives.\n");
        hoodman = clone_object(ROKEDIR + "npc/hoodman");
        hoodman->equip_me();
        hoodman->move(TO);
    }
}
