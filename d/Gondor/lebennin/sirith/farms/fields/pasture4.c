/*
 * /d/Gondor/lebennin/sirith/farms/pasture4.c	
 * field in farm community in southern Lebennin
 *
 * Copyright (C) 1997 by Nancy L. Mintz (Gnadnar)
 *
 */

#pragma strict_types

#include "/d/Gondor/defs.h"
#include "../defs.h"			
#include "/d/Gondor/open/room_chairs/room_chairs.h"

inherit "/d/Gondor/lebennin/sirith/farms/outdoors";
inherit "/d/Gondor/open/room_chairs/room_chairs";

#define	BOULDER_NAME	"boulder"

public void	create_outdoors();
public void	init();
public int	do_climb(string arg);
public int	do_sit(string arg);
public int	do_hop(string arg);
public void	do_sit_msgs(object pl, string prep, string name);
public void	do_stand_msgs(object pl, string name);
public int	ditch_msg();
public string	look_boulder();
public void	leave_inv(object ob, object dest);


/*
 * Function name:	create_outdoors
 * Description	:	set up the room
 */
public void
create_outdoors()
{
    set_areatype("pasture");
    set_ditchdir("south");
    set_extraline("In the center of the pasture is a mossy boulder.");

    add_chair(BOULDER_NAME, "[down] [on] [the] [mossy] 'boulder'", 3);
    add_item( ({ "mossy boulder", "moss", "boulder" }), look_boulder);

    add_cmd_item( ({ "mossy boulder", "boulder" }),
	({ "push", "move", "roll", "shove", "get", "take" }),
	"You cannot budge the boulder.\n" );

    add_exit("pasture6", "north", check_sitting, 2, 1);
    add_exit("pasture5", "northwest", check_sitting, 2, 1);
    add_exit("field9", "south", ditch_msg, 3, 1);
    add_exit("track8", "southwest", check_sitting, 2, 1);
    add_exit("track9", "west", check_sitting, 2, 1);

    set_no_exit_msg( ({ "northeast", "east", "southeast" }),
	"You stroll about the pasture.\n");
} /* create_outdoors */


/*
 * Function name:	init
 * Description	:	add player verbs
 */
public void
init()
{
    ::init();
    init_room_chairs();
    add_action(do_climb, "climb");
    add_action(do_hop, "hop");
    add_action(do_hop, "jump");
    add_action(do_hop, "down");
} /* init */


/*
 * Function name:	do_climb
 * Description	:	transform "climb boulder" to "sit on boulder"
 *			and "climb down" to "hop down".
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_climb(string arg)
{
    int	seated = (TP->query_prop(LIVE_S_SITTING) == BOULDER_NAME);

    if (!arg)
    {
	NF0("Climb "+( seated ? "where?\n" : "what?\n" ));
    }

    if (parse_command(arg, ({}),
        "[onto] / [upon] / [up] [on] [the] [mossy] 'boulder'"))
    {
    	return do_sit("on boulder");
    }
    if (seated)
    {
	return do_hop(arg);
    }
    NF0("Climb what?\n");
} /* do_climb */


/*
 * Function name:	do_sit
 * Description	:	mask parent to block "sit" and "sit down"
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_sit(string arg)
{
    if (!arg ||
	arg == "down")
    {
	NF0("Sit on what?\n");
    }
    return ::do_sit(arg);
} /* do_sit */


/*
 * Function name:	do_hop
 * Description	:	transform "hop down from boulder" to "stand up"
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_hop(string arg)
{
    string	vb = QVB;

    if (vb == "down")
    {
	if (strlen(arg))
	{
	    return 0; /* ?? good NF0 msg ?? */
	}
    }
    else if (!arg ||
	     (arg != "down" && 
              !parse_command(arg, ({}),
			     "[down] [from] [the] [mossy] 'boulder'")))
    {
	NF0(CAP(vb)+" where?\n");
    }
    return do_stand("up");
} /* do_hop */


/*
 * Function name:	do_sit_msgs
 * Description	:	mask parent so the boulder msgs look right
 * Arguments	:	object pl -- the person who's sitting
 *			string prep -- the preposition
 *			string name -- the name of the chair
 */
public void
do_sit_msgs(object pl, string prep, string name)
{
    write("You climb on the boulder and sit down.\n");
    SAY(" climbs on the boulder and sits down.");
} /* do_sit_msgs */


/*
 * Function name:	do_stand_msgs
 * Description	:	mask parent so the boulder msgs look right
 * Arguments	:	object pl -- the person who's standing
 *			string name -- the name of the chair
 */
public void
do_stand_msgs(object pl, string name)
{
    write("You hop down from the boulder.\n");
    SAY(" hops down from the boulder.");
} /* do_stand_msgs */


/*
 * Function name:	ditch_msg
 * Description  :	mask parent so we do you-stand msgs for seated
 *			players first
 * Returns      :	0 (exit is possible)
 */
public int
ditch_msg()
{
    ::check_sitting();
    ::ditch_msg();
    return 0;
} /* ditch_msg */


/*
 * Function name:	look_boulder
 * Description	:	VBFC for boulder; include occupants.
 * Returns	:	string -- the desc
 */
public string
look_boulder()
{
    return "The head-high boulder is covered with soft green moss.\n" +
	sitting_on_chair(BOULDER_NAME, TP, 0);
} /* look_boulder */


/*
 * Function name:	leave_inv
 * Description	:	mask parent to be sure that departing players
 *			are removed from boulder occupants
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand.
 * However, if they leave by quitting, going netdead, teleporting, etc
 * and we don't call leave_inv_room_chairs(), then they'll still look
 * as if they're here.
 */
public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
    leave_inv_room_chairs(ob, dest);
} /* leave_inv */
