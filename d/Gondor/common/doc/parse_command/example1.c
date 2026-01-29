/*
 * example1.c -- a room with a niche you can reach inside.
 * this one allows you to use optional adjectives.
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
	"For testing, try: 'reach inside niche', 'reach inside " +
	"dark niche', 'reach inside narrow niche', " +
	"'reach inside dark narrow niche'."));
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
    /* same msg works for all failures -- might as well
     * set it up now
     */
    notify_fail(CAP(QVB)+" inside where?\n");

    if (!strlen(arg))
    {
	return 0;	/* no arg */
    }
    arg = LOW(arg);	/* be sure it's lowercase */
    if (!parse_command(arg, ({}), "'inside' [dark] [narrow] 'niche'"))
    {
	return 0;	/* bad arg */
    }
    /* decide if the book is there, write the
     * appropriate messages for niche w/ or w/out book
     */
    write("You "+QVB+" inside the niche, but find nothing.\n");
    return 1;		/* good arg */
} /* reach_niche */
