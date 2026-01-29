#pragma strict_types

#include "defs.h"
inherit TBASE;

public void
tunnel_room(void)
{
    set_long("In the center of the room is the base of a "+
	"wide, circular stairwell leading up through "+
	"an enormous hole in the low ceiling. Smooth walls "+
	"frame this large room, opening into a roughly "+
	"hewn tunnel. "+ LDESC +"A narrow passageway leads "+
	"south, from where a soft glittering is cast all "+
	"about. Hot, dry wind flows in from the @@get_north@@ " +
	"and up the opening in the ceiling.\n");

    add_item(({"stair","stairs","stairwell"}),
	"The circular stair rises up throught the opening in the "+
	"ceiling and into darkness.\n");

    add_exit("pool","south");
    add_exit("stair_bottom", "up");
    northern("tunnel2");
}
