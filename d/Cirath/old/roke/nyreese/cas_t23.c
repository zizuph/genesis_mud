/*
 * cas_t23.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  & Gresolle */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object knight;

void reset_room();

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("You are in the southwest tower. This room is, judging from " +
             "the smell, the 'facilities' of the castle. A large hole is " +
             "leading out through the wall.\n");

    add_item("hole",
             "The hole is leading out through the wall. Unfortunately it is " +
             "placed right above a huge hole in the ground, and during the " +
             "years the hole has been filled with various kinds of debris. " +
             "It would not be wise to leave through through this hole.\n");
    add_cmd_item("hole", "enter",
                 "You look at the mud below the hole and realize that you " +
                 "don't want to do that. You decide that it is better to " +
                 "stay where you are.\n");

    INSIDE;
    add_exit("cas_b9", "northeast");
    reset_room();
}

void
reset_room()
{
    if (knight)
        return;

    tell_room(TO, "A guard arrives.\n");
    knight = clone_object(ROKEDIR + "npc/towerg2");
    knight->equip_me();
    knight->move(TO);
}
