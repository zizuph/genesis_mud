/*
 * /d/Gondor/common/doc/examples/room_herbs.c
 *	-- an example room that shows how to add herbs.
 *
 * Created by Gnadnar 28-May-1998
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/herbsearch";

#include "/d/Gondor/defs.h"

/* prototypes */
public void	create_gondor();
 
/*
 * Function name:	create_gondor
 * Description	:	set up the field of herbs
 */
public void
create_gondor()
{
    set_short("a test field");
    set_long(BSN("Knee-high grasses cover this test field."));

    add_item( ({ "knee-high grasses", "grasses", "knee-high grass",
	"grass", "field" }),
	BSN("The grasses have dried to a dusty golden hue, and "+
	    "rustle softly in the wind."));

    /*
     * set up the herbs for this room.
     *
     * the first arg to set_up_herbs() is an array of filenames
     * of the herbs.  you can either provide the name of a specific
     * herb, as we do with garlic here, or you can use the query_herbs()
     * routine and the ONE_OF_LIST() macro to choose a random herb
     * from a list of herbs suitable for this area.  (see
     * /d/Gondor/common/doc/query_herbs for a list of valid areas),
     *
     * if you name specific herbs, be certain that they are not
     * restricted to particular locales, and that the current room
     * is a suitable terrain for them.
     *
     * the second arg to set_up_herbs() is an array of names of items
     * (added with add_item()) that may be searched to find herbs.
     *
     * the third arg is the value for OBJ_I_SEARCH_TIME -- the delay
     * used in the search function.  typical values are between 3 and 8.
     */
    set_up_herbs( ({ (HERB_DIR+"garlic"),
		     ONE_OF_LIST(HERB_MASTER->query_herbs("meadow")),
		     ONE_OF_LIST(HERB_MASTER->query_herbs("plains")),
		  }),
		  ({ "knee-high grasses", "grasses", "knee-high grass",
		     "grass", "field",
		  }),
		  3);
} /* create_gondor */
