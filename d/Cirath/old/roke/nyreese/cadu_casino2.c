/*
 * cadu_casino2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>

object table;

void
reset_room()
{
    if (!table)
    {
	table = clone_object(ROKEDIR + "obj/roulette");
	table->move(this_object());
	table->set_no_show_composite(1);
    }
}

void
create_room()
{
    set_short("Roulette room");
    set_long("You are in the roulette room of the casino. " +
             "In the middle of the room there is a roulette table. " +
             "You see a box of cigars on a shelf.\n");

    add_item(({"box", "cigars", "box of cigars"}),
             "It's a box of nice cigars.\n");
    add_item("shelf", "You see a box of cigars on it.\n");

    add_exit("cadu_casino" , "north");
    add_prop(ROOM_M_NO_ATTACK, "No violence in here, please.\n");

    reset_room();
}

int
get(string str)
{
    if (!str || str != "cigar") return 0;

    if (present("cigar", this_player()))
    {
	write("You already have a cigar! Don't be greedy!\n");
	return 1;
    }
    clone_object(ROKEDIR + "obj/cigar")->move(this_player());
    write("You get yourself a nice cigar.\n");
    say(QCTNAME(this_player()) + " gets " + this_player()->query_objective() +
	"self a nice cigar.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(get, "get");
}
