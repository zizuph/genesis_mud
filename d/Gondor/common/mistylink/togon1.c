/*
 * /d/Gondor/common/mistylink/togon1
 *
 * temporary link from northern ithilien to the misty mountains,
 * will be replaced when anduin opens
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

public void
create_gondor()
{
    set_short("East of Anduin");
    set_long(break_string(
	"You are on the east bank of the Anduin. To the east, a wide plain "+
	"stretches towards dark Mirkwood visible in the distance.\n",
	75));

    add_exit("oldpath4", "north");
    add_exit("togon2", "south");
}
