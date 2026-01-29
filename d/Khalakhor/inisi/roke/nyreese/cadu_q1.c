/*
 * cadu_q1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object k1,k2,k3;

void
reset_room()
{
    if (k1 && k2 && k3) return;

    if (!k1)
    {
        k1 = clone_object(ROKEDIR + "npc/kid");
        k1->move(TO);
    }
    if (!k2)
    {
        k2 = clone_object(ROKEDIR + "npc/kid");
        k2->move(TO);
    }
    if (!k3)
    {
        k3 = clone_object(ROKEDIR + "npc/kid");
        k3->move(TO);
    }

    k1->team_join(k2);
    k1->team_join(k3);
    k2->team_join(k1);
    k2->team_join(k1);

    tell_room(TO, "A few playing children run in from the east.\n");
}

void
create_room()
{
    set_short("Town square");
    set_long("This is the southwest part of Cadu's townsquare.\n" +
             "It's surrounded by large houses to the south and " +
             "the west. There is a small fire, used by the poor people " +
             "of Cadu to warm themselves and to prepare food, "+
             "as they stand outside the mayor's house, begging for "+
             "help.\n");
    
    add_item("house", "The mayor lives in the house to the west.\n");
    add_item("houses", "They look like they belong to very wealthy people.\n");
    add_item("fire", "Ouch! That was hot!!!\n");

    add_exit("cadu_q4", "north");
    add_exit("cadu_q5", "northeast");
    add_exit("cadu_q2", "east");
    add_exit("cadu_m" , "west");
    
    OUTSIDE;

    set_alarm(1.0, 0.0, reset_room);
}

