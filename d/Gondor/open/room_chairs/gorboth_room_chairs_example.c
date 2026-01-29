/*
 * /d/Gondor/open/room_chairs/room_chairs_example.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * An example of using room_chairs ...
 *
 */

#pragma strict_types

inherit "/std/room";
inherit "/d/Gondor/open/room_chairs/gorboth_room_chairs"; /* after the base room */

#include <stdproperties.h>
#include "/d/Gondor/open/room_chairs/room_chairs.h"

/* names for chair and sofa */
#define	CHAIR_NAME	"comfortable armchair"
#define SOFA_NAME	"large sofa"

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
    set_short("a small parlor");
    set_long(break_string(
	"A small parlor. A large sofa "+
	"is drawn invitingly close to a laden "+
	"tea-tray.", 75)+"\n");
    add_prop(ROOM_I_INSIDE, 1);

    /* add a chair and a sofa to the room */
    add_chair(CHAIR_NAME,
	"[down] [in] / [on] [the] [comfortable] 'chair' / 'armchair'",
	1, "in", 0);
    add_chair(SOFA_NAME, "[down] [on] / [in] [the] [large] 'sofa'", 6);

    /* use VBFC for chair/sofa items */
    add_item( ({ "comfortable chair", "comfortable armchair",
	"chair", "armchair" }), &look_at(CHAIR_NAME) );
    add_item( ({ "large sofa", "sofa" }), &look_at(SOFA_NAME) );

    /* the check_sitting efunc will cause seated players to stand
     * up before they leave
     */
    add_exit("/d/Genesis/wiz/com", "common", check_sitting, 1);

    /* add other items, other exits, etc here ... */

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
 * Description	:	VBFC to describe chair/sofa + occupants
 * Arguments	:	string arg -- what's being looked at
 *				      null str -> it's the room
 * Returns	:	string -- the description
 */
public string
look_at(string arg)
{
    /* ok, the descs are a little lame, but you get the idea ... */
    switch ( arg )
    {
    case CHAIR_NAME:
	return "The armchair is deep and soft; it looks very "+
	    "comfortable.\n" +
	    sitting_on_chair(CHAIR_NAME, this_player(), 0);
    case SOFA_NAME:
	return "The sofa is upholstered in a soft dark green velvet.\n"+
	    sitting_on_chair(SOFA_NAME, this_player(), 0);
    }
} /* look_at */
