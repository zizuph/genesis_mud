/*
 * balcony.c
 *
 * Skippern 20(c)02
 *
 * A balcony. It is possible to tie a rope to the railing in order to 
 *  climb down to the fine garden. Add hints to descriptions/items suggesting
 *  mortals it is possible to climb down with a rope. We are able to get
 *  the mortals here for the quest with the charm, but the must hint them
 *  to enter the garden from here.
 */
inherit "/d/Gondor/std/room";

#include "../../defs.h"
#include "../defs.h"
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

/* Globale variables */
object tied; /* The rope that is tied here. */

string railing();

void
create_gondor()
{
    set_short("on a balcony");
    set_long("You are on a balcony, with a nice view over a garden, " +
	     "and the town behind it. The balchony is half-moon " +
	     "shaped, with an arch leading into the garden. Along the " +
	     "front side of the balchony a railing goes preventing " +
	     "people from falling down. White collums holds up the massive " +
	     "roof.\n");

    add_item("railing", &railing());
    add_item("collums", "White collums in ancient style holds up the massive roof.\n");
    add_item("roof", "A massive roof is held up by white collums. The roof is " +
	     "tiled with fine crafted red tiles.\n");
    add_item("town", "Behind the garden you see the town of Dol Amroth streatches out.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_AMROTH_BALCONY);

    add_exit(DOL_HILLS + "m-11/bedroom", "west", 0, 1);
}

int
climb(string arg)
{
    notify_fail("Climb what?\n");

    if (!arg)
	return 0;

    if (arg == "down" || arg == "rope")
    {
	if (tied)
	{
	    write("You jump over the railing and climbs down the rope. " +
		  "You suddenly realises the rope is too short, but " +
		  "looses your grip before you manages to pull yourself " +
		  "up.\nYou sigh.\n");
	    say(this_player()->query_nonmet_name() + " jumps over the " +
		"railing and climbs down the rope.\n");
	    this_player()->move_living("M", DOL_HILLS + "m-11/garden2", 1, 0);
	    say(this_player()->query_nonmet_name() + " tumbles down and " +
		"sighs as "+this_player()->query_pronoun()+" realises " +
		"the rope was too short.\n");

	    return 1;
	}
	else
	    notify_fail("You need a rope to climb down.\n");
    }

    return 0;
}

int
view(string arg)
{
    string garden;
    object *items, surroundings, actor = this_player();

    if (arg == "garden")
    {
        garden = DOL_HILLS + "m-11/garden2";
	garden->teleledningsanka();
	surroundings = find_object(garden)->long();
	items = FILTER_CAN_SEE(all_inventory(find_object(garden)), actor);
	if (items)
	{
	    if (sizeof(FILTER_DEAD(items)))
	        surroundings += CAP(COMPOSITE_DEAD(FILTER_DEAD(items))) +
		    ".\n";
	    if (sizeof(FILTER_LIVE(items)))
	        surroundings += CAP(COMPOSITE_LIVE(FILTER_LIVE(items))) +
		    ".\n";
	}
	actor->catch_tell("You lean over the railing and looks down.\n" +
	    "This is what you see:\n\n" +
            surroundings + "\n");
	tell_room(environment(actor), QCTNAME(actor) + " leans over the " +
		  "railing and looks down.\n",
	    ({actor}));
	return 1;
    }

    notify_fail("View what?\n");
    return 0;
}

void
init()
{
    ::init();
    add_action(climb, "climb");
    add_action(view, "view");
}

int
tie_object(object rope, string where)
{
    if (where != "railing")
    {
        notify_fail("You you try to tie your "+rope->short()+" " + where +
		    " but fail to make the knot.\n");
        return 0;
    }

    if (tied)
    {
        notify_fail("Something is already tied to the railing.\n");
        return 0;
    }

    tied = rope;
    return 1;
}

untie_object(rope)
{
    if (tied == rope)
    {
        tied = 0;
        return 1;
    }

    return 0;
}

object query_tied() { return tied; }

string
railing()
{
    if (!tied)
	return "The railing looks sturdy. It can hold a rope.\n";
    return "The railing looks sturdy. A rope is tied to it.\n";
}
