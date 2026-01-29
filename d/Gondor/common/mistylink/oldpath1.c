/*
 * /d/Gondor/common/mistylink/oldpath1
 *
 * temporary link from northern ithilien to the misty mountains,
 * will be replaced when anduin opens
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

public void
create_gondor()
{
    set_short("Old path");
    set_long(break_string(
	"This grassy path is surprisingly pleasant considering how close "+
	"to Mirkwood it is.  Back to the west are the Misty Mountains, and "+
	"to the east lurks Mirkwood forest.  You can wander in the vale of "+
	"Anduin to the north and the south.  Looking north, you vaguely "+
	"make out a tall spire of rock.\n",
	75));

    add_exit("/d/Shire/misty/p13", "west");
    add_exit("oldpath2", "east");
}
