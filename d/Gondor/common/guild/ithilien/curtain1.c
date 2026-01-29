/*
 * /d/Gondor/common/guild/ithilien/curtain1.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * the curtain in erockchamber. the other side is 
 * curtain2 in ithilien_train
 */

#pragma strict_types

inherit "/d/Gondor/common/guild/ithilien/door";

#include "/d/Gondor/defs.h"

public void	create_door();
public int	pass_door(string arg);
public int	lock_door(string arg);
public int	unlock_door(string arg);

/*
 * Function name:	create_door
 * Description	:	set up the curtain
 */
public void
create_door() 
{
    ::create_door();
    set_door_id("ith_curtain");
    set_door_name( ({ "grey cloth curtain", "cloth curtain", "curtain" }));
    set_close_command( ({ "close", "draw" }) );
    set_pass_command( ({"e", "east"}) );
    set_door_desc("The curtain is made of dull grey cloth. It reaches " +
        "to the floor, and appears fairly heavy.\n");

    set_open_desc(0);
    set_closed_desc(0);

    set_other_room(RANGER_ITH_DIR + "ithilien_train");

    set_open(1);		/* 1 if open, 0 if closed */
    set_locked(0);		/* 1 if locked, 0 if unlocked */
    set_knock_command(0);	/* cannot knock on a curtain */

    /* cannot tie/untie curtain from this side, but 
     * set up the commands so the failure messages look right
     */
    set_lock_command("tie");
    set_lock_mess( ({ "ties the grey cloth curtain shut.\n", "" }) );
    set_fail_lock( ({ "The grey cloth curtain is already tied shut.\n",
	"You must close the grey cloth curtain before you can "+
	"tie it shut.\n" }) );
    set_fail_open( ({ "The grey cloth curtain is already open.\n",
	"The grey cloth curtain is tied shut.\n" }) );
    set_unlock_command("untie");
    set_unlock_mess( ({ "unties the grey cloth curtain.\n", "" }) );
    set_fail_unlock("The grey cloth curtain is already untied.\n");
    set_no_pick();
} /* create_door */


/*
 * Function name:	pass_door
 * Description	:	mask parent to allow passing closed
 *			(but not tied) curtain, and to do
 *			custom messages
 * Arguments	:	string arg -- unused
 * Returns	:	1 -- always
 */
public int
pass_door(string arg)
{
    if (!other_door)
    {
	load_other_door();
    }

    if (open_status)
    {
	write("You brush past the curtain, and enter the recess.\n");
	this_player()->move_living(query_verb(), other_room);
    }
    else if (!lock_status)
    {
	/* say "falls shut" here, because when they see the new room
	 * its long desc will be describing a closed curtain
	 */
	WRITE("You open the curtain just enough to let you enter the " +
	    "recess. The curtain falls shut behind you.");
	SAY(" opens the grey cloth curtain just enough to slip past.");
	tell_room(other_room, 
	    "The grey cloth curtain opens.\n");
	this_player()->move_living(query_verb(), other_room);
	tell_room(other_room,
	    "The grey cloth curtain falls shut.\n", TP);
	tell_room(ENV(),
	    "The grey cloth curtain falls shut.\n");
    }
    else
    {
	write("The grey cloth curtain is tied shut.\n");
    }
    return 1;
} /* pass_door */


/*
 * Function name:	unlock_door
 * Description	:	mask parent so always to fail from this side.
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
unlock_door(string arg)
{
    if (strlen(arg) &&
	parse_command(LOW(arg), ({}), "[the] [grey] [cloth] 'curtain'"))
    {
	write("You see no way to untie the grey cloth curtain from here.\n");
	return 1;
    }
    return 0;
} /* unlock_door */


/*
 * Function name:	lock_door
 * Description	:	mask parent so always to fail from this side.
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
lock_door(string arg)
{

    if (strlen(arg) &&
	parse_command(LOW(arg), ({}),
 	    "[the] [grey] [cloth] 'curtain' [shut]"))
    {
	write("You see no way to tie the grey cloth curtain from here.\n");
	return 1;
    }
    return 0;
} /* lock_door */
