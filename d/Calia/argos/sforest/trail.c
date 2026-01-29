/*********************************************************************
 * - trail.c                                                       - *
 * - Base room for the trail in the silent forest.                 - *
 * - Created by Damaris@Genesis 10/2008                            - *
 *********************************************************************/
#include "sforest.h"
#include <macros.h> /* For the Q macros in messages.. */
#include <stdproperties.h> /* for room props */


inherit "/d/Calia/std/room";

void
create_trail_room()
{
}

nomask void
create_room()
{
	/* To set the short desc. in the rooms. */
	set_short("small over-grown trail");
	/* To set the long desc. in room. */
	set_long("   Pine and maple trees converge together along "+
	"this over-grown trail. Loose dirt and pine needles mark the "+
	"trail with leaves swept to the side giving notice to the "+
	"wilderness beyond.\n");
	
	/* To add items to be examined in rooms. */
	add_item(({"dirt"}),
	"The dirt is dark with rich soil.\n");
	add_item(({"loose dirt"}),
	"The dirt along the trail is loose and you may be able "+
	"to take a sample.\n");
	add_item(({"soil", "dark soil", "rich soil"}),
	"The soil is dark indicating rich minerals.\n");
	add_item(({"minerals", "mineral"}),
	"The minerals found in the dirt can only be tested by "+
	"an expert.\n");
	add_item(({"trees", "tree"}),
	"The trees are maple and pine, which converge together "+
	"creating a huge canopy above.\n");
	add_item(({"leaves"}),
	"Leaves are scattered and some swept to the side of the trail.\n");
	add_item(({"canopy"}),
	"The canopy above is formed from the convergence of trees.\n");
	add_item(({"maple trees", "maple tree"}),
	"The maple trees are of the three-flowered Maple species, "+
	"distinguished by having trifoliate leaves.\n");
	add_item(({"trail"}),
	"The trail is over-grown with maple and pine trees.\n");
	add_item(({"pine trees", "pine tree"}),
	"The pine trees are very tall and very old giving off "+
	"a soft scent.\n");
	add_item(({"pine needles", "needles"}),
	"The pine needles are normal size and scatterd on the ground "+
	"as well as growing on the trees.\n");	
	add_item(({"trifoliate leaves"}),
	"The three leaflets than make up the trifoliate are sturdy "+
	"and colourful.\n");
	add_item(({"wilderness"}),
	"The wilderness is untamed and just beyond the trail.\n");
	add_item(({"air"}),
	"The air is filled with the soft scent of pine.\n");

	create_trail_room();

}
