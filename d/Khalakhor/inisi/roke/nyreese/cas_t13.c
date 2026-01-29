/*
 * cas_t13.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*  Ged & Gresolle */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

void
create_room()
{

    set_short("Castle tower");
    set_long("You are in the southwest tower. Large spiders have woven " +
             "their webs in the cracks between the huge rocks forming " +
             "the walls of the castle. A small window has been placed in " +
             "the outside wall.\n");

    add_item(({"spider", "spiders"}), 
             "You don't feel quite comfortable with the " +
             "way the spider looks at you, almost like if it thinks " +
             "that you would be a perfect dinner...\n");

    add_item(({"web", "webs"}), "They are white.\n");
    add_item(({"crack", "cracks"}), "Ordinary cracks.\n");
    add_item("window", "You can look through it.\n");
    add_cmd_item(({"window", "through window"}), "look",
                 "You see the City of Cadu beyond the trees. There are " +
                 "lots of people walking around in the streets.\n");

    add_exit("cas_a9", "northeast");

    INSIDE;
    reset_room();
}

void
reset_room()
{
    if (MAL("guard"))
        return;

    clone_object(ROKEDIR + "npc/towerg1")->move(TO);
    tell_room(TO, "The tower guard arrives.\n");
}
