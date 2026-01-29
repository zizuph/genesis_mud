/*
 * cadu_q4.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object p;

void
reset_room()
{
    if (p) return;

    tell_room(TO, "A human arrives.\n");
    p = clone_object(ROKEDIR + "npc/people");
    p->equip_me();
    p->move(TO);
}

void
create_room() 
{
    set_short("Town square");
    set_long("You are at the town square in Cadu.\n"+
             "To the west is the outdoor cafe of the famous "+
             "inn, the Fisherman's Friend. To the east you sense "+
             "an aura of pure magic.\n");

    add_exit("cadu_out", "west");
    add_exit("cadu_q5" , "east");
    add_exit("cadu_q7" , "north");
    add_exit("cadu_q1" , "south");

    reset_room();
}



