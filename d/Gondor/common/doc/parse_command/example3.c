/*
 * example3.c -- a room with a fireplace in which you can put wood.
 * this illustrates how to learn exactly which one of a set of
 * allowed words (e.g., "fire" and "fireplace") the player actually used.
 *
 * this is of course incomplete as a room goes, but it's just a demo.
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

#include <macros.h>
#include "/d/Gondor/defs.h"

public void	create_gondor();
public void	init();
public int	lookat(string arg);
public int	put_wood(string arg);
public int	extinguish(string arg);

static int	Fire_is_lit;


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("test room");
    set_long(BSN("A test room with a wide stone fireplace. "+
	"For testing, you might try putting some wood in it."));
} /* create_gondor */

/*
 * Function name:	init
 * Description	:	add verbs for fireplace
 */
public void
init()
{
    ::init();
    add_action(lookat, "look");
    add_action(lookat, "exa");
    add_action(lookat, "examine");
    add_action(put_wood, "put");
    add_action(put_wood, "place");
    add_action(extinguish, "extinguish");
} /* init */


public int
lookat(string arg)
{
    string	tmpstr;
    if (!strlen(arg))
    {
	return 0;
    }
    arg = LOW(arg);
    if (QVB == "look" &&
	sscanf(arg, "at %s", tmpstr) == 1)
    {
	arg = tmpstr;
    }
    if (parse_command(arg, ({}), "[the] [wide] [stone] 'fireplace'"))
    {
	WRITE("The fireplace is built of smooth river stones.");
	if (Fire_is_lit)
	{
	    WRITE("It contains a briskly burning fire that "+
		"casts a warm light over the room.");
	}
	return 1;
    }
    if (parse_command(arg, ({}), "[the] 'fire' [in] [the] "+
		      "[wide] [stone] [fireplace]"))
    {
	if (Fire_is_lit)
	{
	    WRITE("The fireplace contains a briskly burning fire that "+
		"casts a warm light over the room.");
	}
	else
	{
	    WRITE("There is no fire in the fireplace just now.");
	}
	return 1;
    }
    return 0;
} /* lookat */

/*
 * Function name:	put_wood
 * Description	:	handle putting wood on fire
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we understand the arg, 0 if not
 */
public int
put_wood(string arg)
{
    string	*names = ({ "fireplace", "fire" });

    /* no point in doing notify_fail().  if it fails here
     * it will always fall through to the mudlib "put" command,
     * so our notify_fail message will never be seen.
     */
    if (!strlen(arg))
    {
	return 0;	/* no arg */
    }
    arg = LOW(arg);
    if (!parse_command(arg, ({}),
		       "'wood' / 'firewood' 'on' / 'in' [the] "+
		       "[wide] [stone] %p", names))
    {
	return 0;	/* bad arg */
    }
    /* assume we have a global variable Fire_is_lit that 
     * keeps track of the state.
     * 
     * first (0th) element of names array is the name
     * that they used.
     */
    if (names[0] == "fire" &&
	!Fire_is_lit)
    {
	write("The fire is not lit just now.\n");
	return 1;
    }
    write("You put some wood in the fireplace.\n");
    if (!Fire_is_lit)
    {
	Fire_is_lit = 1;
	write("You light a fire in the fireplace.\n");
    }
    return 1; 	/* good arg */
} /* put_wood */


/*
 * Function name:	extinguish
 * Description	:	douse the fire
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	int -- 1 on success, 0 on failure
 */
public int
extinguish(string arg)
{
    if (strlen(arg) ||
	parse_command(LOW(arg), ({}), "[the] 'fire'"))
    {
	if (Fire_is_lit)
	{
	    write("You extinguish the fire.\n");
	    say(QCTNAME(TP) + " extinguishes the fire.\n");
	    Fire_is_lit = 0;
	    return 1;
	}
	notify_fail("The fire is not lit.\n");
	return 0;
    }
    notify_fail("Extinguish what?\n");
    return 0;
} /* extinguish */
