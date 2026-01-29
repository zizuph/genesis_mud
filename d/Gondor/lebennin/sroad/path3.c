/*
 * /d/Gondor/lebennin/sroad/path3.c
 *
 * Copyright (C) May 21, 1998 by Ron Miller (Tyr)
 *
 * This is a room of the trail that leads to the lens taken from 
 * the Pelargir lighthouse.
 *
 * Revision history:
 *     5/11/99 - added swim across river to pier
 *     6/17/99 - herbs added by Tyr
 *     6/28/99 - revised per Gnadnar's suggestions by Tyr
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit "/d/Gondor/common/lib/herbsearch";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

/* prototypes */
public void    create_gondor();
public void    init();
public int     cross_river(string arg);
public void    drink_message(string from);

#define HARD_TO_SWIM  25 /* how hard is it to swim across the water? */
#define SWIM_FATIGUE  30 /* how tiring is it to swim? */

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
public void
create_gondor()
{
    FIX_EUID;

    set_short("On a path");

    set_long(BSN("The path appears to end here. Through a break in "+
        "the underbrush, some sort of pier is visible on the "+
        "opposite side."));

    add_item(({"this","trail","here","area"}), BSN("A well-trodden "+
        "pathway has been worn into the grass here. It follows the "+
        "edge of the River Sirith and continues to make its way "+
        "through the underbrush."));

    add_item(({"river","river sirith","sirith","edge","side",
        "opposite bank","west"}), BSN("The River Sirith lies to the "+
        "west of the trail."));

    add_item(({"pier","construction","style"}), BSN("Upon closer "+
        "examination, the construction of the pier appears to be of "+
        "the style normally used by Corsairs."));

    add_item(({"opposite side","other side"}), BSN("On the other side "+
        "of the river, a pier juts out into the river."));

    add_item(({"pathway","path"}), BSN("The passage of people or "+
        "animals has crushed the grass into an obvious path "+
        "alongside the river here."));

    add_item(({"underbrush","bank"}), BSN("The bank of the river is "+
        "lined by a wide variety of shrubs typical of this area."));

    add_item("break", BSN("The bushes here don't grow quite so "+
        "close together, allowing an unobstructed view of the "+
        "river."));

    add_item(({"shrub","shrubs","trees","bushes","woody bushes",
        "variety"}), BSN("The short woody bushes here are actually "+
        "more like small trees. The large bushes to the southeast "+
        "may have been disturbed recently."));

    add_item(({"large bushes","southeast"}), BSN("Despite someone's "+
        "efforts to obsure it, the trail can still be seen as it "+
        "enters the rather large bushes toward the southeast."));

    add_item(({"corsair","corsairs"}), BSN("There are no Corsairs "+
        "lurking about this side of the river at the moment."));

    add_item(({"people","animals","traffic","someone"}), BSN("No one "+
        "who helped create this trail appears to be nearby right "+
        "now."));

    add_item(({"grass","blades","short blades","ground"}), BSN("The "+
        "short blades of grass here have been mashed flat by "+
        "frequent traffic through the area."));

    set_drink_from( ({ "river", "sirith", }) );
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    /* Adding herbs to this room */
    set_up_herbs( ({ (HERB_DIR+"tuo"),
                     (HERB_DIR+"laurel"),
                     (HERB_DIR+"basil"),
                  }),
                  ({ "grass","ground","bush","bushes","underbrush",
                     "path","pathway",}),
                  4);

    add_exit("path2", "northeast", 0, 1);

    /* non-obvious exit thru bushes */
    add_exit("path4", "southeast", 0, 1, 1);

} /* end create_gondor */


/*
 * Function name:	init
 * Description	:	add drink, swim verbs
 */
public void
init()
{
    ::init();
    init_drink();
    add_action(cross_river, "swim");
    add_action(cross_river, "dive");
    add_action(cross_river, "cross");
} /* end init */


/*
 * Function name:	cross_river
 * Description	:	handle attempts to swim across
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	int -- 1 on success, 0 on failure
 */
public int
cross_river(string arg)
{
    int		skill,
		diff,
		tired;
    string	junk;

    if (!strlen(arg) ||
	!parse_command(LOW(arg), ({}),
	    "[into] [over] [in] [across] [the] 'river' / 'sirith' %s",
	    junk))
    {
	NF0(CAP(QVB) + " where?\n");
    }

    /* caculations swiped from ~gondor/common/lib/roads.c */
    skill = TP->query_skill(SS_SWIM);
    diff = HARD_TO_SWIM;
    tired = SWIM_FATIGUE;

    diff = (diff / 2) + random(diff) + 1;
    if (TP->query_encumberance_weight() > 80)
    {
        tired *= 2;
	diff  *= 2;
    }

    if (skill < diff)
    {
        write("This water is too difficult for you to swim safely.\n"
            + "You are struggling.\n"
            + "You start to inhale water!\n"
            + "Your body washes back to near your starting point.\n");
	TP->reduce_hit_point(diff - skill);
        SAYBB(" tries to cross the river, but fails to make it " +
	    "to the other shore.");
    }
    else if (TP->query_fatigue() < tired)
    {
        write("You are too tired to cross the river.\n");
        SAYBB(" is too tired to cross the river.");
    }
    else
    {
	write("You swim across the river.\n");
	SAYBB(" leaves swimming across the river.");
	TP->move_living("M", (LEB_DIR + "sroad/south_pier"));
	TP->add_fatigue(-tired);
	SAYBB(" arrives swimming across the river.");
    }
    return 1;
} /* end cross_river */


/*
 * Function name:	drink_message
 * Description	:	do the msg for drinking
 * Arguments	:	string from -- source from which they drank
 */
public void
drink_message(string from)
{
    write("You drink water from the river. It tastes somewhat muddy.\n");
    SAY(" drinks some water from the river.");
} /* end drink_message */

