/*
 * /d/Gondor/rohan/edoras/rooms/edtransport.c
 *
 * The transport-office of Edoras, where the carriage is cloned and
 * loaded into the game. By Elessar for Genesis, March '92.
 *
 * Modification history:
 *	16-April-1998, Gnadnar: require finding hatch before can
 *				take 'down' exit, conform to domain.rules
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define	PLAYER_I_FOUND_HATCH	"_player_i_found_hatch"

/* prototypes */
public void	create_gondor();
public void	reset_room();
private void	wagon_reset();
public void	start_wagon();
public void	init();
public string	do_search(object searcher, string arg);
public string	exa_hay(string arg);
public int	enter_hatch(string arg);
public int	open_hatch(string arg);

static object	Wagon;


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("a stable");
    set_long(BSN("The stable is dusty, and dimly lit. "
      + "There is a pile of hay in the corner, and a signboard "
      + "hangs on the west wall."));
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_exit(EDORAS_DIR + "path2",    "east",       0, 0);

    add_item("stable", long);
    add_item( ({"pile", "hay", "pile of hay"}), &exa_hay("hay"));
    add_item( ({ "sign", "board", "sign board", "signboard" }),
	"The sign reads:\n"
      + "\tCarriages to Minas Tirith depart outside the stable.\n"
      + "\tThe carriages accept passengers for a modest fee.\n");
    add_item( ({ "square opening", "opening", "open hatch", "hatch" }),
	&exa_hay("hatch"));
    add_item( ({ "floor" }), &exa_hay("floor"));
    add_item( ({ "wooden boards", "boards", "wall", "walls", "west wall" }),
	BSN("The walls are simple wooden boards.  A sign has "+
	    "been attached to the west wall."));
    add_item( ({ "underside", "roof", "ceiling", }),
	BSN("The stable has no true ceiling -- all that is "+
	    "overhead is the underside of the roof."));
    add_item( ({ "hay dust", "dust" }),
	BSN("A fine layer of hay dust covers every surface in the "+
	    "stable."));

    add_cmd_item( ({ "sign", "board", "sign board", "signboard" }),
	"read", 
	"The sign reads:\n"
      + "\tCarriages to Minas Tirith depart outside the stable.\n"
      + "\tThe carriages accept passengers for a modest fee.\n");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    reset_room();
} /* create_gondor */


/*
 * Function name:	reset_room
 * Description	:	set up the wagon if needed
 */
public void
reset_room()
{
    ::reset_room();
    if (!objectp(Wagon) )
    {
	wagon_reset();
    }
} /* reset_room */


/*
 * Function name:	wagon_reset
 * Descriptoin	:	create a new wagon and start it up
 */
private void
wagon_reset()
{
    FIX_EUID;
    Wagon = clone_object(EDORAS_DIR + "obj/edwagon");
    Wagon->move(TO);
    Wagon->set_leavable(1);

    set_alarm(10.0, 0.0, start_wagon);
} /* wagon_reset */


/*
 * Function name:	start_wagon
 * Description	:	harness the horses and get going ...
 */
public void
start_wagon()
{
    if (!objectp(Wagon) ||
	ENV(Wagon) != TO)
    {
	return;
    }

    tell_room(TO, "The driver attaches two horses to the carriage,\n"
	      +   "then drives the wagon out into the street.\n");
    Wagon->set_horses(2);
    Wagon->move(EDORAS_DIR + "path2");
    Wagon->start(20.0);
} /* start_wagon */


/*
 * Function name:	init
 * Description	:	add hatch verbs
 */
public void
init()
{
    ::init();
    add_action(enter_hatch, "enter");
    add_action(enter_hatch, "down");
    add_action(open_hatch, "open");
    add_action(open_hatch, "close");
}


/*
 * Function name:	do_search
 * Description	:	handle searching hay, set prop
 * Arguments	:	object searcher	this player
 *		:	string arg	whatever the player searched
 * Return	:	string describing results of search
 */
public string
do_search(object searcher, string arg)
{
    if (arg != "hay" &&
	arg != "pile" &&
	arg != "pile of hay")
    {
	return "";
    }

    TP->add_prop(PLAYER_I_FOUND_HATCH, 1);
    return BSN(
       "Searching through the hay, you find an open hatch leading "+
       "down beneath the stable.");
} /* do_search */


/*
 * Function name:	exa_hay
 * Description	:	VBFC for hay/hatch
 * Arguments	:	string arg -- "hay", "hatch" or "floor"
 * Returns	:	string -- the description
 */
public string
exa_hay(string arg)
{
    int		found = TP->query_prop(PLAYER_I_FOUND_HATCH);

    if (arg == "hay")
    {
	if (found)
	{
	    return BSN("Hay is piled loosely in the corner of the "+
		"stable around an open hatch.");
	}
	return "Hay is piled loosely in the corner of the stable.\n";
    }
    if (arg == "hatch")
    {
	if (found)
	{
	    return "The hatch is just a square opening in the floor.\n";
	}
	return "You find no hatch.\n";
    }
    /* arg == "floor" */
    if (found)
    {
	return "There's an open hatch in the dusty floor.\n";
    }
    return "The wooden floor is very dusty.\n";
} /* exa_hay */


/*
 * Function name:	enter_hatch
 * Description	:	handle attempts to enter hatch
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
enter_hatch(string arg)
{
    object	tp = TP;
    int		found = tp->query_prop(PLAYER_I_FOUND_HATCH);

    if (QVB == "enter")
    {
	if (!found ||
	    (arg != "hatch" &&
	     arg != "open hatch" &&
	     arg != "the hatch" &&
	     arg != "the open hatch"))
	{
	    NF0("Enter what?\n");
	}
    }
    else if (!found)	/* verb is "down" */
    {
	NF0("There is no obvious exit down.\n");
    }
    write("You climb down through the hatch.\n");
    tp->move_living("into the hay", (EDORAS_DIR + "basement"));
    return 1;
} /* enter_hatch */


/*
 * Function name:	open_hatch
 * Description	:	handle attempts to open/close hatch
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
open_hatch(string arg)
{
    if (!TP->query_prop(PLAYER_I_FOUND_HATCH) ||
        (arg != "hatch" &&
	 arg != "open hatch" &&
	 arg != "the hatch" &&
	 arg != "the open hatch"))
    {
	NF0(CAP(QVB)+" what?\n");
    }
    WRITE("The hatch has no door to "+QVB+"; it is simply "+
	"an opening in the floor.");
    return 1;
} /* open_hatch */
