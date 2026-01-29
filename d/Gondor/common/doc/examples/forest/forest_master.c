/*
 * /d/Gondor/common/doc/examples/forest/forest_master.c
 *
 * Copyright (C) 1999 by Nancy L. Mintz (Gnadnar)
 *
 * Example of a master room for a forest
 * Provides:
 *    VBFC for light level, so light varies with time of day
 *    default init of tod_desc (tod == "time of day") stuff
 *    item descriptions for standard items.
 *    a nice no-exit msg for rooms that don't exist yet
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/tod_descs";
inherit "/d/Gondor/common/lib/herbsearch";

#include <stdproperties.h>	/* for ROOM_I_LIGHT */
#include "/d/Gondor/defs.h"	/* always */

/* the number of alternative descs for items */
#define    N_ITEM_CHOICES    3

/* prototypes */
public void	create_forest();
nomask void	create_gondor();
public void	init();
public int	check_lightlevel();
public int	no_exit();
public int	do_climb(string arg);


/*
 * Function name:	create_forest
 * Description	:	called by inheriting rooms to set
 *			themselves up.
 */
public void
create_forest()
{
} /* create_forest */


/*
 * Function name:	create_gondor
 * Description	:	set up stuff common to all forest rooms
 *
 * notice that we declare this "nomask", instead of "public".
 * this means that rooms that inherit forest_master cannot provide
 * their own create_gondor() -- they will instead provide 
 * create_forest() to handle room-specific setup.
 */
nomask void
create_gondor()
{
    int    desc_index;    /* index into default item descs */

    add_prop(ROOM_I_LIGHT, check_lightlevel);

    /* do the default tod calls before calling create_forest(), so
     * the inheriting rooms can change it in create_forest() if
     * needed.  see ~gondor/common/lib/tod_descs.c for doc re
     * these function calls.
     */
    set_tod_landname("the Dark Wood");
    set_tod_landtype("forest");
    set_long(tod_descs);
    set_tod_prependshort(0);
    set_tod_comes_first(1);

    /* do the specific room setup */
    create_forest();

    /*
     * now set up the generic items.  notice that we call try_item(),
     * rather than add_item(), so as not to wipe out any items added
     * by the individual rooms in create_forest().
     */

    /* first, the usual tod sky stuff .. nothing new here */
    try_item( ({ "sky", "sun", "moon", "star", "stars", }),
            tod_descs );

    /*
     * now it gets interesting :-)
     * 
     * first thing to notice is that we are making a firm assumption
     * that we provide the same # of alternate descriptions 
     * (N_ITEM_CHOICES) for all default items.
     *
     * we choose an index into the alternate descriptions by:
     *        desc_index = random(N_ITEM_CHOICES);
     *
     * then for each set of items, we call try_item().
     *
     * the first argument to try_item() is the usual array of item 
     * names, and the second one is the usual BSN(string). the string
     * arg to BSN is where we get tricky. we want to vary the 
     * description, so we create here an array of N_ITEM_CHOICES
     * different descriptions.  then we use desc_index as an index
     * into that array. the string referenced by that index gets
     * passed as the argument to BSN().
     *
     * it will be easier to find typos if we indent very carefully.
     *
     * the descriptions, of course, are just examples, and they
     * are not complete.
     */

    desc_index = random(N_ITEM_CHOICES);

    try_item( ({"ground", "forest floor", "floor", "plant",
                "plants", }),
        BSN(
            ({"Dry, brown leaves carpet the forest floor."+
                " Here and there amongst the leaves, herbs and"+
                " mushrooms and the odd moss can be seen growing.",
            "The ground is covered with fallen leaves. Here and"+
                " there amongst the leaves, herbs and"+
                " mushrooms and the odd moss can be found growing.",
            "Leaves in various hues of brown and yellow cover"+
                " the ground. Amongst the leaves, herbs and"+
                " mushrooms and the odd moss can be seen growing"+
                " here and there.",
                })[desc_index]
            )
        );
    try_item( ({"herb", "herbs", "mushroom", "mushrooms"}),
        BSN(
            ({"Some herbs and mushrooms can be seen pushing up"+
                " amongst the leaves covering the ground.",
            "Mushrooms and herbs can be seen on the ground here"+
                " and there, having pushed themselves up amongst"+
                " the leaves covering the ground.",
            "Amongst the leaves on the ground, some herbs and"+
                " mushrooms can be seen growing.",
                })[desc_index]
            )
        );
    try_item( ({"moss", "mosses", }),
        BSN(
            ({"Here and there amongst the leaves covering the"+
                " ground, some moss has found bare spots to grow"+
                " on.",
            "In a few places amongst the leaves covering the"+
                " ground, some moss has found a bare spot to grow"+
                " on.",
            "Moss can be seen growing here and there amongst"+
                " the leaves covering the ground, having found"+
                " a bare spot to grow on.",
                })[desc_index]
            )
        );
    try_item( ({"forest", "wood", "woods", "tree", "trees", }),
        BSN(
            ({"Tall, solemn trees grey and lichened"+
                " stand interspersed with younger"+
                " upstarts who strive for a place in the sun.",
            "Trees of all ages grow tall here, old ones dressed"+
                " in lichen and young ones still naked, all"+
                " reaching eagerly for the sky.",
            "The trees stand tall and lichened, each one"+
                " trying to outgrow its neighbours.",
                })[desc_index]
            )
        );
    /* ... continue with items here ... */


    /*
     * set up the herbs for the forest
     *
     * the first arg to set_up_herbs() is an array of filenames
     * of the herbs.  you can either provide the name of a specific
     * herb, as we do with blackberry here, or you can use the query_herbs()
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
    set_up_herbs( ({ (HERB_DIR + "blackberry"),
		     ONE_OF_LIST(HERB_MASTER->query_herbs("forest")),
		     ONE_OF_LIST(HERB_MASTER->query_herbs("forest")),
		  }),
		  ({ "ground", "forest floor", "floor", "plant", "plants",
		     "forest", "wood", "woods", "tree", "trees",
		  }),
		  5);

} /* create_gondor */


/*
 * Function name:    init
 * Description  :    add "climb" verb
 */
public void
init()
{
    ::init();
    add_action(do_climb, "climb");
}/* init */


/*
 * Function name:    check_lightlevel
 * Description  :    determine lightlevel based on time of day
 * Returns    :    int -- light level (always positive)
 *
 * copied from /d/Gondor/common/lib/area_room.c
 */
public int
check_lightlevel()
{
    switch (tod())
    {
    case "night":
        return 1;
    case "early morning":
    case "evening":
        return 2;
    case "morning":
    case "noon":
    case "afternoon":
        return 3;
    default:
        return 1;
    }
} /* check_lightlevel */


/*
 * Function name:    no_exit
 * Description  :    write a nice message and block exits to rooms
 *                   that don't exist yet.
 * Returns      :    1 (exit always fails)
 */
public int
no_exit()
{
    WRITE("You wander " + QVB + ", but soon become disoriented " +
	  "and end up back where you started.");
    return 1;
} /* no_exit */


/*
 * Function name:	do_climb
 * Description	:	respond to attempts to climb a tree
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 if we recognize the arg, 0 if not
 *
 * N.B. In the master room, we don't let them climb the trees, we
 * just print a more interesting message than "What? ".
 * If an individual room did want to allow climbing, it would simply
 * provide its own do_climb() routine that parsed the arg and moved
 * the player.
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
	NF0("Climb what?\n");
    }

    arg = LOW(arg);	/* convert to lowercase */

    /* use parse_command to be more flexible in what we accept.
     * see ~gondor/common/doc/parse_command/README for more info
     *
     * we accept several tree names here.  probably no individual
     * room will have all of these trees in it, but it's also
     * fairly unlikely that a player will try "climb oak" in a room
     * that doesn't mention an oak, so it doesn't hurt to do them
     * all at once.
     */
    if (!parse_command(arg, ({ }),
	"[up] [the] [a] 'tree' / 'trees' / 'oak' / 'oaks' / " +
	"'willow' / 'willows' / 'alder' / 'alders' / 'beech' / 'beeches'"))
    {
	NF0("Climb what?\n");
    }

    /* have a few different messages, for variety's sake. */
    write( ({
	"None of the branches are within your reach.\n",
	"None of the nearby trees seems climbable.\n",
	"You try to climb, but slide back to the ground.\n",
	})[random(3)] );
    return 1;
} /* do_climb */
