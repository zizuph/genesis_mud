/*
 * /d/Emerald/blackwall/delrimmon/obj/trance_shadow.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 * Intercepts all messages to the player while s/he's in a trance
 *
 * XXX:
 *	what about armageddon?  
 *	ditto tell's from wizards?
 *	assume we don't need to autoload?
 *	need to test what happens if go linkdead and return
 */

#pragma strict_types

inherit "/std/shadow";

#include <macros.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

#define	PARALYZE_OBJECT	"/std/paralyze"

static int	Debug;

public void	catch_tell(string msg);
public void	catch_msg(mixed str, object from_player);
public void	trance_msg(string msg);
public object	query_trance_shadow();
public void	set_debug(int d);
public int	query_debug();


/*
 * Function name:	catch_tell
 * Description	:	mask parent to block all messages
 *			except those from the paralyze obj
 * Arguments	:	string msg - the message
 */
public void
catch_tell(string msg)
{
    int		i;
    object	prev;

    if (objectp(prev = previous_object()) &&
	function_exists("create_paralyze", prev) == PARALYZE_OBJECT)
    {
	shadow_who->catch_tell(msg);
    }
    else if (Debug)
    {
	shadow_who->catch_tell("DBG catch_tell: previous objects:\n");
	while (objectp(prev = previous_object(i--)))
	{
		shadow_who->catch_tell("\t" + file_name(prev) + "\n");
	}
    }
    return;
} /* catch_tell */


/*
 * Function name:	catch_msg
 * Description	:	mask parent to block all messages
 *			except those from the paralyze obj
 * Arguments	:	string msg - the message
 *			object from_player -  the object that generated
 *					      the message
 */
public void
catch_msg(mixed msg, object from_player)
{
    object	prev;
    int		i;

    if (objectp(prev = previous_object()) &&
	function_exists("create_paralyze", prev) == PARALYZE_OBJECT)
    {
	shadow_who->catch_msg(msg, from_player);
    }
    else if (Debug)
    {
	shadow_who->catch_tell("DBG catch_msg: previous objects:\n");
	while (objectp(prev = previous_object(i--)))
	{
		shadow_who->catch_tell("\t" + file_name(prev) + "\n");
	}
    }
    return;
} /* catch_msg */


/*
 * Function name:	trance_msg
 * Description	:	pass trance messages to player
 * Arguments	:	string msg -- the message to print
 */
public void
trance_msg(string msg)
{
    /* XXX if need VBFC, use catch_msg */
    shadow_who->catch_tell(msg);
} /* trance_msg */

/*
 * Function name:	query_trance_shadow
 * Description	:	query the shadow
 * Returns	:	object -- this object
 */
public object
query_trance_shadow()
{
    return TO;
} /* query_trance_shadow */




public void	set_debug(int d)	{ Debug = d; }
public int	query_debug()		{ return Debug; }
