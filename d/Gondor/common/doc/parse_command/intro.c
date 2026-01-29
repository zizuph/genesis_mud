/*
 * intro.c -- a room with a niche you can reach inside.
 * this one allows only "reach inside niche".
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <macros.h>
#include "/d/Gondor/defs.h"

public void	create_gondor();
public void	init();
public int	reach_niche(string arg);

/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("test room");
    set_long(BSN("A test room with a dark narrow niche. "+
	"For testing, try 'reach inside niche'."));
    add_item( ({ "dark niche", "narrow niche", "niche",
	"dark narrow niche", "crevice" }),
	BSN("The crevice is too dark to see inside it."));
}

/*
 * Function name:	init
 * Description	:	add verbs for niche
 */
public void
init()
{
    ::init();
    add_action(reach_niche, "reach");
    add_action(reach_niche, "feel");
} /* init */

/*
 * Function name:	reach_niche
 * Description	:	let 'em reach inside the niche,
 *			maybe find book
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
reach_niche(string arg)
{
    if (arg != "inside niche")
    {
	notify_fail(CAP(QVB)+" inside where?\n");
	return 0;	/* failure */
    }
    /* decide if the book is there, write the
     * appropriate messages for niche w/ or w/out book
     */
    write("You "+QVB+" inside the niche, but find nothing.\n");
    return 1;		/* success */
} /* reach_niche */
