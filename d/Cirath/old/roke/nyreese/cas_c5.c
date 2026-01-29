/*
 * cas_c5.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/*  Ged  */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"

#define HARD_TO_FIND 20
#include <ss_types.h>
#include <macros.h>

/*secret exit to c6*/
object guard;

void reset_room();
void check();

void
fixroom()
{
    write("This room looks more like a corridor. The walls are draped " +
          "with black, silk curtains. The light from the ceiling is a " +
          "bit stronger here.\n" +
          "You see exits to your north and to your south.\n");
    check();
}

void
create_room()
{
    set_short("Castle in Cadu");
    set_long("@@fixroom");

    set_noshow_obvious(1);

    add_item("curtain",
             "The black curtains looks heavy. As you try to touch them" +
             " they move away from you... Another magical trick.\n");
    add_item("curtains",
             "The black curtains looks heavy. As you try to touch them" +
             " they move away from you... Another magical trick.\n");

    add_exit("cas_c1", "north");
    add_exit("cas_c9", "south");
    add_exit("cas_c6", "east", "@@block");
    reset_room();
}

int
block()
{
    if (this_player()->query_skill(SS_AWARENESS) >= HARD_TO_FIND ||
        this_player()->query_skill(SS_LOC_SENSE) >= HARD_TO_FIND)
    {
        return 0;
    }
    else
        return 1;
}

void
check()
{
    if (!block())
    {
        write("You also find a hidden exit to the east.\n");
        write("There are three obvious exits: north, south, east.\n");
    }
    else
    {
        write("There are two obvious exits: north, south.\n");
    }
}

void
reset_room()
{
    if (guard)
        return;

    guard = clone_object(ROKEDIR + "npc/knights");
    guard->equip_me();
    guard->move(TO);
    tell_room(TO, "A knight in armour steps out of the curtains.\n");
}
