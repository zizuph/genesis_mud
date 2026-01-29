/* 
 *      /d/Gondor/tharbad/trail/path10.c
 *
 *      Copyright (C) June 24, 1998 by Ron Miller (Tyr)
 *
 *      This is a trail that leads to the mirror taken from the Pelargir
 *      lighthouse.
 *
 * Revision history:
 *    6/17/99 - herbs added by Tyr
 *    6/28/99 - Revised per Gnadnar's suggestions by Tyr
 */

#pragma strict_types

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit "/d/Gondor/common/lib/herbsearch";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define HARD_TO_SWIM  25 /* how hard is it to swim across the water? */
#define SWIM_FATIGUE  30


/* prototypes */
public void    create_gondor();
public void    init();
public int     cross_river(string arg);
public void    drink_message(string from);

/*
 * Function name:    create_gondor
 * Description:      create the basic room
 */
public void
create_gondor()
{
    FIX_EUID;

    set_short("On a path");

    set_long(BSN("A well-trodden pathway makes its way through the "+
        "underbrush and ends here on the banks of the river "+
        "Greyflood."));
   
    add_cmd_item( ({ "river", "greyflood", "water", "across river", }), 
        ({ "swim", "cross", }), cross_river);

    add_item( ({"path", "pathway" }) , BSN("The path ends here on the "+
        "bank of the Greyflood. A few faint footprints actually "+
        "continue into the water."));

    add_item( ({ "river", "river greyflood", "greyflood", "gwathlo", }),
        BSN("The river Greyflood runs sluggishly in deep channels "
            + "here, its water being brown and murky. It is almost "
            + "too wide to cross, but an experienced swimmer might "
            + "be able to reach the other shore."));

    add_item("water", "The water of the river is brown and murky, "
        + "deep and full of strange eddies.\n"); 

    add_item( ({ "scrubby evergreen creepers", "creepers", "rosebushes" }) ,
        BSN("The limbs and branches of the vegetation here have been "+
        "carefully rearranged to hide a footpath which heads "+
        "to the west."));

    /* Adding herbs to this room */
    set_up_herbs( ({ (HERB_DIR+"blueberry"),
                      (HERB_DIR+"redweed"),
                     (HERB_DIR+"morgurth"),
                  }),
                  ({ "grass", "ground", "bush", "bushes", "underbrush",
                     "path", "pathway", }),
                  5);

    add_exit("path10", "west", 0, 1, 1);
        
    set_drink_from( ({ "river", "river greyflood", "greyflood",
	"gwathlo", }) );
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);

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
	    "[into] [over] [in] [across] [the] " +
	    "'river' / 'greyflood' / 'gwathlo' %s",
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
        TP->move_living("M", (THARBAD_DIR + "pier/pier4"));
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
    WRITE("You drink some water from the Greyflood. " +
        "It tastes as muddy as it looks.\n");
    SAYBB(" drinks some water from the river.");
}   /* end drink_message */
