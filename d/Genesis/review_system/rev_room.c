
/*
 * A room that dispenses a review reader to the entrant.
 *						Napture.
 */

inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "review.h"

#ifndef TP
#define TP this_player()
#endif

create_room()
{
    set_short("The review reader room");
    set_long(break_string("This small room appears at first to be empty, " +
	"but you can make out a small hole with a button above it inset " +
	"within the wall. Looking at the walls again, you notice that " +
	"they aren't solid; they are made from a soft padded substance " +
	"that wields to your touch. As you look around, you notice that " +
	"it isn't just the walls, but the floor and ceiling are covered " +
	"with this strange soft substance too.\n", 75));
	
    add_item(({"walls", "floor", "ceiling", "wall", "substance", "padding", 
	"padded substance"}), "Yep, the walls, floor and ceiling are " +
	"covered in a white padded substance....just like the room " +
	"description says!\n");
    add_item(({"hole"}), "This hole looks as though something might pop " +
	"out of it anymoment. As you look at the hole, something catches " +
	"your eye and you look up to see a small button just above " +
	"the hole.\n");
    add_item("button", "The button is slightly inset into the padded " +
	"wall. You feel a strange force just daring you to press that " +
	"button!\n");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
	
    add_exit("Back where you came from!", "back", "@@go_back");
}

#ifdef 0
/* A quick fix so that it is always light in here */
light()
{
    return 1;
}
#endif

go_back()
{
    this_player()->move_living("return",
        this_player()->query_prop(LIVE_O_LAST_ROOM));
    return 1;
}

init()
{
    ::init();
    add_action("press_me", "press");
    add_action("press_me", "push");
    add_action("my_scream","scream");
}

press_me(string str)
{
    object reader;
    string verb;
    
    if (!str) return 0;
    verb = query_verb();
    notify_fail("For some strange reason, you totally failed to " + verb +
	" anything at all!!! Maybe if you could find something here " +
	"that looks like it should be " + verb + "ed?\n");
    if (str!="button" && str!="inset button" && str!="small button")
	return 0;

    if (TP->query_wiz_level() == 50)
	write("As a Keeper, you can go to the review comment room and " +
	    "press the button there to obtain an advanced version " +
	    "of the review reader.\n");
    if (TP->query_wiz_level() > 39 && TP->query_wiz_level() !=50)
	write("As an Arch, you can go to the review comment room and " +
	    "press the button there to obtain an advanced version " +
	    "of the review reader.\n");
    if (member_array(TP->query_real_name(), GLOBAL_READ) != -1)
	write("As a Reviewer, you can go to the review comment room and " +
	    "press the button there to obtain an advanced version " +
	    "of the review reader.\n");

    if (!(reader = clone_object(PATH + "reader.c")))  {
	write("A strange clunking sound comes from behind the button, but " +
	    "nothing else happens. Looks like something has gone wrong!\n");
	return 1;
    }
    if (reader->move(TP))  {
	write("Suddenly, something drops out of the hole, but you're " +
	    "carrying so much junk already, that you just drop it " +
	    "straight on the floor, where it explodes magnificently!\n");
	say(QCTNAME(TP) + " presses the button, but is carrying so much " +
	    "junk, " + TP->query_pronoun() + " drops it on the floor, " +
	    "where it explodes magnificently!\n");
	return 1;
    }
    write("Suddenly, a small review reader pops out of the hole into " +
	"your hand!  It looks like it might have instructions written on " +
	"it already.\n");
    say(QCTNAME(TP) + " pushes the button and deftly catches something " +
	"as it pops out of the hole!\n");
    return 1;
}

my_scream()
{
    write("The soft walls absorb most of your scream!!!\n");
        /* Let the player scream anyway... */
    return 0;
}
