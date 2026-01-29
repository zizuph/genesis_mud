/*
 * cas_c7.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

object wizard, grimoire;

void reset_room();

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("This is the workroom of the great magician Refnas.\n" +
             "Here the walls and the floor are made out of pure " +
             "marble and gently treated with magic to get a really " +
             "scary color. But even though the walls and floor are " +
             "black, this is still the most lit up room on the entire " +
             "level. This comes from the strong magical light emitted " +
             "by the ceiling. There's also a desk here.\n");

    add_item("desk",
             "A large, oak desk without drawers or any kind of markings.\n");

    INSIDE;
    add_exit("cas_c6", "west");

    reset_room();
}

void
reset_room()
{
    if (!wizard)
    {
        tell_room(TO, "A good wizard shimmers into view before you.\n");
        wizard = clone_object(ROKEDIR + "npc/refnas");
        wizard->equip_me();
        wizard->move(TO);
    }
    if (!grimoire)
    {
        tell_room(TO, "The good wizard puts a grimoire on the table.\n");
        grimoire = clone_object(ROKEDIR + "obj/grimoire");
        grimoire->move(TO);
    }
}
