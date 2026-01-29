/*
 * /d/Gondor/common/mistylink/togon5
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
	"You are on the east bank of the Anduin, which stretches little "+
	"eastward here because of the Undeeps. Mirkwood lies to the north "+
	"and beyond the Anduin to the south, the hills of the Emyn Muil are "+
	"visible. Between Emyn Muil to the south and Mirkwood, there "+
	"stretches a wide empty plain.\n",
	75));

    add_exit("togon4", "northwest");
    add_exit("gondorlink2", "south");
}
