/*
 * example4.c -- a plate that can be polished.
 * doesn't deal with multiple plates (e.g., "polish second plate")
 * and will work even on hidden plates.
 */

#pragma strict_types

inherit "/std/object";

#include "/d/Gondor/defs.h"

public void	create_object();
public void	init();
public int	polish_plate(string arg);


/*
 * Function name:	create_object
 * Description	:	set up the plate
 */
public void
create_object()
{
    set_name( ({ "plate", "platter", "salver" }) );
    set_adj( ({ "heavy", "antique", "silver" }) );
    set_long(BSN("The antique silver plate would be beautiful, "+
	"if it were not so badly tarnished."));
} /* create_object */

/*
 * Function name:	init
 * Description	:	add polish verb
 */
public void
init()
{
    ::init();
    add_action(polish_plate, "polish");
} /* init */

/*
 * Function name:	polish_plate
 * Description	:	let 'em polish this plate.
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if the arg refers to this object, 0 if not
 */
public int
polish_plate(string arg)
{
    object	target;

    /* same msg works for all failures -- might as well
     * set it up now
     */
    notify_fail("Polish what?\n");

    if (!strlen(arg))
    {
	return 0;	/* no arg */
    }
    arg = LOW(arg);
    if (!parse_command(arg, ({ TO }), "[the] %o", target))
    {
	return 0;	/* not this object */
    }
    WRITE("You try to polish the silver plate, but "+
	"it remains heavily tarnished.");
    return 1;
} /* polish_plate */


