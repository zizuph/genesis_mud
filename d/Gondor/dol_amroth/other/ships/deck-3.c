/* -*- Mode: C -*-
 *
 * other/ships/deck-3.c
 *
 * The deck of a cargo ship.
 */
inherit "/d/Gondor/std/room";

#include "../../defs.h"

object room_ob = this_object();

void
create_gondor()
{
    set_short("on the deck of a cargo ship");
    set_long("You are on the deck of a cargo ship. Some sailors " +
	"are running to and from and derricks are lifting crates " +
	"filled with all kinds of cargo onto deck.\n");

    reset_room();

    add_exit(DOL_TRADE + "piers/r-08", "disembark", 0, 1, 1);
}

void
reset_room()
{
    int i;
    mixed var;
    parse_command("cargo", all_inventory(room_ob), "i", var);
    i = sizeof(var) -1;
    if (i < 3)
    {
	tell_room(this_object(), "A derrick lift one crate up from the hold.\n");
	clone_object(DOL_OBJ+"cargo")->move(this_object());
    }
}
