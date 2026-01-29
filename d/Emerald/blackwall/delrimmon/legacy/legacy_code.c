/*
 * This file contains functions which are present in base code from the
 * Gondor domain. Since this area was coded in the Gondor domain, these
 * functions will not be used elsewhere in Emerald, but rather will
 * allow this area to continue in development without a massive
 * structural recode.
 */

static mapping	No_exit_msg = ([]);	/* custom no-exit msgs		*/


/*
 * From: /d/Gondor/std/room.c
 *
 * Function name:	set_no_exit_msg
 * Description	:	set the custom no-exit msg for direction(s)
 * Arguments	:	mixed dir -- either a string or an array of strings;
 *				     each string is a direction for which
 *				     this room does not have an exit.
 * 			string msg -- the msg for these directions
 *
 * So instead of "There is no obvious exit west.", you can tell
 * players "You wander west among the trees for a bit, then return
 * to the road."
 */
public void
set_no_exit_msg(mixed dir, string msg)
{
    int		i, n;

    if ( pointerp(dir) )
    {
	for ( i = 0, n = sizeof(dir); i < n; ++i )
	    No_exit_msg[dir[i]] = msg;
    }
    else if ( stringp(dir) && strlen(dir) )
    {
	No_exit_msg[dir] = msg;
    }
} /* set_no_exit_msg */
