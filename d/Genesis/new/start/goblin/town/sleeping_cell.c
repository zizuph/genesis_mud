/*
 * File         : /d/Genesis/new/start/goblin/town/sleeping_cell.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 13, 1999
 * Modifications: 
 * Purpose      : Goblin sleeping cell/First room of racial start loc!
 * Related Files: 
 * Comments     : 
 * TODO         : 
 */

inherit "/std/room.c";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Genesis/login/login.h"

/*
 * Function name: create_room
 * Description  : It creates the room object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_room()
{
    set_short("You are in a goblin sleeping cell");

    set_long("You are in a goblin sleeping cell.\n" +
    "It is dark here. Water drips periodically from the ceiling of " +
    "the cave. Perhaps it was water which bore this room out of the " +
    "cool rock. Tiny creatures peer at you from a myriad of crevices. " +
    "Something has been carved into the east wall. A fire burns in " +
    "the center of the cave. The sound of rushing water is almost " +
    "deafening. A large opening has been cut into the north wall of " +
    "the cell, opening out onto a ledge. A tunnel leads south.\n");

    add_item(({"water", "dripping water", "stalagtites"}),
    "Tiny drops of water drip lazily from the ceiling's muster of " +
    "stalagtites. Rather than pooling on the floor, the water drains " +
    "quickly away down the many cracks in the rock.\n");

    add_item(({"creatures", "tiny creatures"}),
    "It is hard to get a good look at the little creatures. They " +
    "certainly seem interested in you, however.\n");

    add_item(({"fire", "flame", "fire pit"}),
    "A small fire burns with a warming reassurance in the cell's " +
    "fire pit.\n");

    add_item(({"ceiling"}),
    "The ceiling of the cave is a jagged landscape of damp " +
    "stalagtites.\n");

    add_item(({"cave", "cell"}),
    "This is one of many sleeping cells where goblins come to rest " +
    "from their adventures. It looks large enough to comfortably " +
    "accomodate a family of five or six goblins.\n");

    add_item(({"rock"}),
    "The rock here is so smooth that it is hard to imagine it was " +
    "carved out by hand.\n");

    add_item(({"crevice", "crevices"}),
    "Tiny creatures peep at you from several cracks in the walls and " +
    "floor of the cell. These openings also seem to catch the water " +
    "dripping from the ceiling and channel it somewhere.\n");

    add_item(({"wall"}),
    "Which wall?\n");

    add_item(({"north wall", "opening", "large opening", "ledge"}),
    "The north wall of the cell opens onto a small ledge which " +
    "looks out over the cavern beyond.\n");

    add_item(({"east wall", "carving", "something"}),
    "It would take a scholar of ancient goblin texts to be able " +
    "to translate this writing.\n");

    add_item(({"south wall", "tunnel", "passageway", "passage"}),
    "The south wall offers an entrance into a dark passageway.\n");

    add_item(({"west wall"}),
    "The west wall bears nothing of interest.\n");

    add_exit("sleeping_ledge", "north");
    add_exit("sleeping_tunnel1", "south");

    reset_room();
}

int
start(string str)
{
    if (str != "here")
    {
	notify_fail("Start where? Here?\n");
	return 0;
    }

    if (RACESTART[this_player()->query_race()] != MASTER)
    {
	notify_fail("This is not your racial starting location.\n");
	return 0;
    }

    if (this_player()->set_default_start_location(MASTER))
    {
	write("Next time you enter the game, you will start here.\n");
    }
    else
    {
	write(break_string("Somehow it is not possible for you to start " +
	    "here. The room apparently has not been approved of by the " +
	    "archwizards of Genesis. Please mail the archwizard of " +
	    "player affairs to get it allowed.", 74) + "\n");
    }

    return 1;
}

void
reset_room()
{
    if (!present("faq_book"))
    {
        clone_object("/d/Genesis/start/FAQ/faq_book")->move(this_object());
    }
}

void
init()
{
    ::init();

    add_action("start", "start");
}