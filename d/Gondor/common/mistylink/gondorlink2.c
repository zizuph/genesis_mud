/*
 * /d/Gondor/common/mistylink/gondorlink2
 *
 * temporary link from northern ithilien to the misty mountains,
 * will be replaced when anduin opens
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

public void
create_gondor()
{
    set_short("Border of Rhovanion");
    set_long(break_string(
	"You have reached the border of the land called Rhovanion. It "+
	"stretches vast and dangerous to the north while to the south "+
	"starts the land known under the name of Gondor.\n",
	75));

    add_exit("togon5", "north");
    add_exit("/d/Gondor/common/shirelink2", "southeast");
}
