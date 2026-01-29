/*
 * cas_a6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged & Gresolle */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object guard1,guard2,guard3;

/* the globals are set to NULL when the monster is killed */

void reset_room();

void
create_room()
{
    INSIDE;

    set_short("Guard room");
    set_long("You have entered one of the guard rooms of the castle.\n" +
             "Here, the guards usually meet to play cards and drink cheap " +
             "wine between guard duty.\n");

    add_exit("cas_a5", "west");

    reset_room();
}

void
reset_room()
{
    if ((guard1 || guard2 || guard3)) /* don't update `til all dead */
        return;

    guard1 = clone_object(ROKEDIR + "npc/guard1");
    guard2 = clone_object(ROKEDIR + "npc/guard1");
    guard3 = clone_object(ROKEDIR + "npc/guard1");
            
    guard1->equip_me();
    guard2->equip_me();
    guard3->equip_me();

    guard1->move(TO);
    guard2->move(TO);
    guard3->move(TO);
            
    guard1->team_join(guard2);
    guard1->team_join(guard3);
}
