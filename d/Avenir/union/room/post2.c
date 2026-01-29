/*
 * Post office for the Union Council
 *
 * Lucius, Jul 2011: Changed to inherit the regular post to reduce
 *                   duplication.
 */
#pragma strict_types
#include "../defs.h"

inherit (ROOM + "post");

public void
union_room(void)
{
    ::union_room();

    set_short("oval chamber");
    set_long("This is a large, silent chamber with smooth stone walls "+
	"that reach around to form an oval. In the centre of the "+
	"room rises a rock table with a small chair before it, upon "+
	"which you can read and write letters.\nThe only exit is to "+
	"the south, where a hallway can be made out.\n");

    /* Remove inherited exits. */
    remove_exit("up");   
    remove_exit("south");

    add_exit("council", "south");
}
