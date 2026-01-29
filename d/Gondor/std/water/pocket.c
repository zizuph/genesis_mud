/*
 * /d/Gondor/std/water/pocket.c
 *
 * a bare bones underwater room, used by onwater rooms that don't have
 * a "down" exit to hold dropped items.
 */

#pragma strict_types

inherit "/d/Gondor/std/water/underwater";

public void	create_underwater();

/*
 * Function name:	create_underwater
 * Description	:	set up the underwater pocket
 */
public void
create_underwater()
{
    set_short("under water");
    set_long("Under water. It's difficult to see very far.\n");
} /* create_underwater */
