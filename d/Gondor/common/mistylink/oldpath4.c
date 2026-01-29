/*
 * /d/Gondor/common/mistylink/oldpath4
 *
 * temporary link from northern ithilien to the misty mountains,
 * will be replaced when anduin opens
 */

#pragma strict_types

inherit "/d/Gondor/std/room";

public int	block();

public void
create_gondor()
{
    set_short("East of Anduin");
    set_long(break_string(
	"The grass is thicker on this side of the river, wilder and "+
	"tougher.  The long grass sways in the wind.  To the east Mirkwood "+
	"Forest encroaches on the land.  Looking far to the northeast you "+
	"see what looks like a large house.  Back west reeds float lazily "+
	"in the Anduin.  You can follow the east bank of the river to the "+
	"north and south.\n",
	75));

    add_exit("oldpath3", "west");
    add_exit("togon1", "south");
    add_exit("Not_a_real_room", "east", block);
    add_exit("Not_a_real_room", "north", block);
}

public int
block()
{
    write(break_string(
	"The vale of Anduin has been flooded by an unusually rainy "+
	"season.  You could try back later when it has had a chance "+
	"to dry out some.\n", 75));
    return 1;
}
