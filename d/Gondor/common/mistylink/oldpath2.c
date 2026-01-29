/*
 * /d/Gondor/common/mistylink/oldpath2
 *
 * temporary link from northern ithilien to the misty mountains,
 * will be replaced when anduin opens
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

public void
create_gondor()
{
    set_short("Bank of Anduin");
    set_long(break_string(
	"To the east lies Anduin, the great river, and beyond it, "+
	"Mirkwood.  The river is shallow enough to be forded at this spot, "+
	"though it looks impassable to the north and the south.  Back west "+
	"lie the Misty Mountains, and the plains follow the river north and "+
	"south.\n",
	75));

    add_exit("oldpath1", "west");
    add_exit("oldpath3", "east");
}
