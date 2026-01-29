/*
 * /d/Gondor/common/doc/examples/room_search2.c
 *	an example room that lets you search the trash
 *	and find either a torch and/or a rope.
 *
 * Created by Gnadnar 28-May-1998
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <stdproperties.h>	/* for ROOM_I_INSIDE, OBJ_*_SEARCH_* 	*/
#include <language.h>		/* for LANG_ADDART			*/
#include <macros.h>		/* for QCTNAME				*/
#include "/d/Gondor/defs.h"	/* always				*/

#define	TORCH_FILE	(OBJ_DIR + "torch")
#define	ROPE_FILE	(OBJ_DIR + "rope")

static int	Torch_is_here,	/* if true, torch is hidden in trash	*/
		Rope_is_here;	/* if true, rope is hidden in trash	*/

/* prototypes */
public void	create_gondor();
public void	reset_room();
public string	do_search(object tp, string arg);


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("a test room");
    set_long(BSN("This test room is completely empty, except "+
	"for the pile of trash in the corner."));
    add_prop(ROOM_I_INSIDE, 1);

    add_item( ({ "corner", "pile of trash", "pile of garbage",
	"trash", "garbage" }),
	BSN("The pile of trash appears to hold nothing of value."));
    add_item( ({ "floor", "wooden floor", "dust" }),
	BSN("The wooden floor is bare of all but dust"));
    add_item( ({ "wall", "walls" }),
	BSN("The walls are empty of decoration, and none too clean."));
    add_item( ({ "ceiling" }),
	BSN("The ceiling sags alarmingly. It looks as if it "+
	    "might fall at any moment."));

    /* routine to call when they search */
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    /* how long it takes to search -- typical values are 3 - 8 */
    add_prop(OBJ_I_SEARCH_TIME, 5);

    reset_room();
} /* create_gondor */


/*
 * Function name:	reset_room
 * Description	:	set Torch_is_here and Rope_is_here
 */
public void
reset_room()
{
    ::reset_room();
    Torch_is_here = Rope_is_here = 1;
} /* reset_room */


/*
 * Function name:	do_search
 * Description	:	handle searching the room & items
 * Arguments	:	object tp	this player
 *		:	string arg	whatever the player searched
 * Returns	:	string -- describes the result of the search.
 *
 * players can search any of the room items, plus "here". 
 * we are interested in:
 *	"corner", "trash", "garbage", "pile of trash",
 *	"pile of garbage", or any of the above with "for torch"
 *	or "for rope" appended.
 * we reject (return null str) for anything else.
 * we also return null str if there is no torch in trash.
 *
 * when the returned string is null, the mudlib will give the default
 * "Your search reveals nothing special." message to the player.
 */
public string
do_search(object tp, string arg)
{
    string	msg,
		saymsg,
		target;
    object	ob;

    /* arg will never be null. if player does just "search",
     * mudlib will set arg to "here".
     */
    arg = LOW(arg);
    if (arg == "here")
    {
	/* they didn't direct the search to the trash ...
	 * give them a hint.
	 */
	return BSN("You poke aimlessly around the room, "+
	    "but find nothing interesting.");
    }

    if (!Torch_is_here &&
	!Rope_is_here)
    {
	return "";	/* nothing to find */
    }

    /* this will accept "search pile of corner", but what the heck.
     * see /d/Gondor/common/doc/parse_command/README for more info.
     */
    if (!parse_command(arg, ({}),
	    "[pile] [of] 'trash' / 'garbage' / 'corner' [for] %s", target))
    {
	return "";
    }

    if (strlen(target))
    {
	if (target == "torch")
	{
	    if (!Torch_is_here)
	    {
		/* searched for torch, but it's gone */
		return "";
	    }
	}
	else if (target == "rope")
	{
	    if (!Rope_is_here)
	    {
		/* searched for rope, but it's gone */
		return "";
	    }
	}
	else
	{
	    /* searched for something other than rope or torch */
	    return "";
	}
    }
    else
    {
	/* they didn't specify what to search for. we know that
	 * at least one object is present, and possibly both are.
	 * if only one, choose that one; else choose at random.
	 */
	if (!Torch_is_here ||
	    (Rope_is_here &&
	     !random(2)))
	{
	    target = "rope";
	}
	else
	{
	    target = "torch";
	}
    }

    /* success */
    FIX_EUID;
    if (target == "torch")
    {
	ob = clone_object(TORCH_FILE);
    	Torch_is_here = 0;
    }
    else
    {
	ob = clone_object(ROPE_FILE);
	Rope_is_here = 0;
    }

    msg = "You find "+LANG_ADDART(ob->short())+" hidden in the trash.\n";
    saymsg = QCTNAME(tp)+" finds something in the trash.\n";

    if (ob->move(tp))
    {
	/* tp can't hold it -- probably too heavy */
	msg += "Oops, you dropped it.\n";
	saymsg += QCTNAME(tp)+" drops "+LANG_ADDART(ob->short())+".\n";
	ob->move(TO, 1);
    }

    /* other people in the room will always see tp search.
     * this call to say() will let them see tp find stuff.
     *
     * if the hidden object is a quest item, you may want to delete this
     * call to say(), and the lines above that initialize saymsg, so that
     * bystanders don't learn where stuff is hidden just by watching.
     */
    say(saymsg);

    return msg;
} /* do_search */
