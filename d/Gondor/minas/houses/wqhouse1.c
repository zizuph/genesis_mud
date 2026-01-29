/*
 *	/d/Gondor/minas/houses/wqhouse1.c
 *
 *	Coded by ???
 *
 *	Modification log:
 *	28-Jan-1997, Olorin:	General revision.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void
create_gondor()
{
    set_short("in a private garden in Anorien Street in Minas Tirith");
    set_long(BSN("Lovely red flowers grow in flowerbeds along the walls of this garden. "+
    "The garden itself is not large, but nice enough. A few clothes have "+
    "been hung out to dry on a line in the corner. An open gate leads south "+
    "into Anorien Street in the Second Circle."));
    add_item("clothes",BSN("The clothes look to be of good quality, but they do seem "+
			   "to be well-used and worn. "));
    add_item("flowers",BSN("The red flowers makes the garden smell pleasant. They are "+
    "placed in well-tended flower-beds on each side of the garden. "));
    add_item("garden",BSN("The garden is not big, being only about twenty times "+
    "twenty feet. It looks nice though, with well-tended flower-beds "+
    "on each side. Worn out tiles lead up to the front door "+
    "from the open gate. "));
    add_item(({"path","tiles"}),BSN("The tiles are old and worn, from being trodden on year "+
    "after year. They would be best replaced with new ones. "));
    add_item(({"flower-beds","flowerbeds"}),
    BSN("The flowerbeds are well-tended, and large red flowers "+
    "stretch upwards during daylight hours. In a second row of beds, further away from " +
    "the tiled path, herbs have been planted. "));
    add_item("gate",BSN("The gate once included an iron-bar door, but it is now lying "+
    "broken in a corner of the garden, all rusty and bad. Through the "+
    "open gate you can enter the Anorien Street to the south. "));

    add_exit(MINAS_DIR + "n2crc2", "south", 0, 1);

    clone_object(MINAS_DIR+"obj/wqoutdoor")->move(TO);

    set_up_herbs( ({ HERB_DIR + "lothore", HERB_DIR + "foxglove", 
		     HERB_DIR + "basil", HERB_DIR + "oregano",
		     HERB_DIR + "thyme", }),
		 ({ "flowers", "flower-beds", "flowerbeds", "garden"}), 3);
}
