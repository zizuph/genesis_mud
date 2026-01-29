/*
 * cas_t24.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object knight;

void reset_room();

void
create_room()
{
    set_short("Southeast tower");
    set_long("You are in the southeast tower. Through the window you " +
             "hear the song of small birds.\n");
    INSIDE;

    add_item("window", "You can look through it.\n");
    add_cmd_item(({"window", "through window"}), "look",
                 "Just outside the window is a small apple tree.\n");
    add_cmd_item("tree", "climb",
                 "The tree is not large enough for climbing. " +
                 "Perhaps you should try again in a few years.\n");

    add_exit("cas_b12", "northwest");
    reset_room();
}

void
reset_room()
{
    if (knight)
        return;
    
    tell_room(TO, "A vicious guard arrives.\n");

    knight = clone_object(ROKEDIR + "npc/towerg2");
    knight->equip_me();
    knight->move(TO);
}
