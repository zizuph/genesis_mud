/*
 * /d/Gondor/common/mistylink/oldpath3
 *
 * temporary link from northern ithilien to the misty mountains,
 * will be replaced when anduin opens
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

public void
create_gondor()
{
    set_short("Fording the Anduin");
    set_long(break_string(
	"The Anduin runs slowly by here.  At this spot, the river is wide "+
	"and shallow.  The water is warm around your legs.  To the east "+
	"lies more of the old path, and back west lie the Misty Mountains. "+
	"To the north and south, the river becomes swift and deep.\n",
	75));

   add_exit("oldpath2", "west");
   add_exit("oldpath4", "east");
}
