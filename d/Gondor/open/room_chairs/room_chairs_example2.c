/*
 * /d/Gondor/open/room_chairs/room_chairs_example2.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 * An example of using a "chair" that is not immediately visible --
 * let players sit on a boulder.  This is not a realistic example;
 * it's simply intended to show how to configure more subtle chairs.
 */

#pragma strict_types

inherit "/std/room";
inherit "/d/Gondor/open/room_chairs/room_chairs"; /* after the base room */

#include <stdproperties.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"

/* names for seat */
#define BOULDER_NAME	"large boulder"

/* prototypes */
public void	create_room();
public void	init();
public void	leave_inv(object ob, object dest);
public string	look_at(string arg);	/* VBFC for chairs */


/*
 * Function name:	create_room
 * Description	:	room constructor
 */
public void
create_room()
{
    set_short("a rocky field");
    set_long(
	"A barren, rocky field. Nothing seems to grow here "+
	"except boulders.\n");

    /* args: name, parse_string, capacity, preposition,
     * whether the chair is xplicitly mentioned in room desc
     */
    add_chair(BOULDER_NAME,
	"[down] [on] [the] [large] 'boulder'",
	5, "on", 0);

    /* don't append list of seated players to room desc */
    set_no_sitting_in_desc(1);

    add_item( ({ "large boulder", "particularly large boulder",
	"boulder" }), &look_at(BOULDER_NAME) );

    /* the check_sitting efunc will cause seated players to stand
     * up before they leave
     */
    add_exit("/d/Genesis/wiz/com", "common", check_sitting, 1);

    add_item( ({ "rocks", "boulders", "stones" }),
        &look_at("rocks"));

} /* create-room */


/*
 * Function name:	init
 * Description	:	mask parent so we can call init_room_chairs()
 */
public void
init()
{
    ::init();
    init_room_chairs();	/* add chair verbs */
} /* init */


/*
 * Function name:	leave_inv
 * Description	:	mask parent to be sure that departing players
 *			are removed from chair/sofa occupants
 * Arguments	:	object ob -- the departing object
 *			object dest -- its destination
 *
 * If they leave via a normal exit, they've already been made to stand
 * by the exit efunc check_sitting().
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


/*
 * Function name:	look_at
 * Description	:	VBFC to describe boulder + occupants
 * Arguments	:	string arg -- what's being looked at
 *				      null str -> it's the room
 * Returns	:	string -- the description
 */
public string
look_at(string arg)
{
    /* fourth arg of 1 to sitting_on_chairs() will cause
     * definite article to be used
     */
    if (arg == BOULDER_NAME)
    {
    	return "The large boulder is weathered and smooth.\n" + 
	    sitting_on_chair(BOULDER_NAME, this_player(), 0, 1);
    }
    /* looked at boulders generally -- use indefinite article */
    return "Grey boulders are tumbled about the field.\n" +
	sitting_on_chair(BOULDER_NAME, this_player(), 0, 0);
} /* look_at */
