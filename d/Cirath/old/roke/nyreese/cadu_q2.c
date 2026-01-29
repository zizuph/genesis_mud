/*
 * cadu_q2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object beggar;

void
reset_room()
{
    if (beggar) return;

    beggar = clone_object(ROKEDIR + "npc/beggar");
    beggar->move(TO);
}

void
create_room()
{
    set_short("Town square");
    set_long("You are at the town square in Cadu.\n"+
             "Many of the local farmers have small sheds here, " +
             "in which they sell vegetables and other stuff. " +
             "To the north you detect something emitting very " +
             "powerful magic. Someone has planted a sign-post in " +
             "the middle of the street.\n");

    add_item("shed", "The shed closest to you is filled with meat.\n");
    add_item("sheds", "They look like they're going to fall down " +
             "if you breathe at them.\n");
    add_item(({"sign", "sign-post", "post", "signpost"}),
             "@@signtext");
    add_cmd_item(({"sign", "sign-post", "post", "signpost"}),
                 "read", "@@signtext");

    add_exit("cadu_q5", "north");
    add_exit("cadu_p4", "south");
    add_exit("cadu_q1", "west");
    add_exit("cadu_q3", "east");

    reset_room();
}

string 
signtext()
{
    return  "The signpost has a few signs pointing " +
            "in different directions:\n" +
	    "NORTH: Post office, Adventurer's Guild\n" +
	    "WEST:  Mayor's office, Inn\n" +
	    "EAST:  Shop, Bank, Library, Weaponsmith\n";
}
