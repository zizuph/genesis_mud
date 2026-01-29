/*
 * /d/Gondor/tharbad/pier/pier4.c
 *
 * The ship to Poros & Lebennim lands here
 *
 * Modification log:
 *    6/18/98 - Generally reformatted code &
 *              Added exit to swim river by Tyr
 *    6/28/99 - Revised per Gnadnar's suggestions by Tyr
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

#define HARD_TO_SWIM  25 /* how hard is it to swim across the water? */
#define HARD_TO_CLIMB  7 /* how hard is it to climb the slope? */
#define SWIM_FATIGUE  30 /* how tiring is it to swim? */

inherit "/d/Genesis/gsl_ships/lib/pier";

public void	init();
public int	cross_river(string arg);
public void	drink_message(string from);

/*
 * Function name:    create_gondor
 * Description:      create the room
 */
public void
create_roads() 
{
    object  sign;

    set_short("A ruined pier in Tharbad, in the south of Eriador");
    set_extraline("You stand on an old decrepit pier beside the "+
        "Greyflood River. Other than the water, you see little sign "+
        "that ships land here. Now and then, ships from far away dock "+
        "here, but since Tharbad is deserted, you could wait for days "+
        "and still not see a ship. Northeast, you see more piers and "+
        "the fords, while the way southwest is blocked by a marsh.");


    add_item( ({ "marsh", "swamp", "marshes" }) , BSN("This marsh stretches "+
        "for a long way next to the Greyflood that feeds its water "+
        "supply. Occasionally, swamp gases burp up from the surface, "+
        "wafting sulfurous odors in your direction."));

    add_item( ({ "pier", "piers" }) , BSN("This pier is one of "+
        "several along the riverbank."));

    add_item( ({ "riverbank", "river bank", "bank" }) , BSN("The "+
        "clear cold water is in sharp contrast to the ruined "+
        "surroundings. Southwesterly, you see the Greyflood winding "+
        "its way towards the sea."));
    add_item( ({ "water", "river", "river greyflood",
	"greyflood", "gwathlo", }),
        BSN("The river Greyflood runs sluggishly in deep channels "
            + "here, its water brown and murky. It is almost "
            + "too wide to cross, but an experienced swimmer might "
            + "be able to reach the island in the middle of the "
            + "river."));

    /*
    sign = clone_object(SHIP_DIR+"vingaard_sign");
    sign->set_file(SHIP_DIR+"poros_tharbad.txt");
    sign->move(TO);
    */

    add_exit(THARBAD_DIR + "pier/pier3", "northeast", 0, 2);

    set_drink_from( ({ "river", "greyflood", "gwathlo", }) );
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
   add_pier_entry(MASTER_OB(TO), "Tharbad", "Line to Pelargir and Poros");
   initialize_pier();
    
}   /*  end create_gondor()  */

/*
 * Function name:	init
 * Description	:	add the drinking and river verbs
 */
public void
init()
{
    ::init();
    init_drink();

    add_action(cross_river, "swim");
    add_action(cross_river, "dive");
    add_action(cross_river, "cross");
} /* init */


/*
 * Function name:	drink_message
 * Description	:	do the msgs for drinking from river
 */
public void
drink_message(string from)
{
    write("You drink some of the muddy water of the Greyflood.\n"
        + "It tastes as muddy as it looks.\n");
    SAY(" drinks some water from the river.");
} /* drink_message */


/*
 * Function name:	cross_river
 * Description	:	handle attempts to cross the river
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	int -- 1 if we understand the arg, 0 if not
 */
public int
cross_river(string arg)
{
    string	junk;
    int		tired = SWIM_FATIGUE;

    if (!strlen(arg) ||
	!parse_command(LOW(arg), ({}),
	    "[into] [over] [in] [across] [the] " +
	    "'river' / 'greyflood' / 'gwathlo' %s", junk))
    {
	NF0(CAP(QVB) + " where?\n");
    }

    if (!swim(HARD_TO_SWIM, SWIM_FATIGUE))
    {
        SAYBB(" leaves swimming across the river.");
        TP->move_living("M", (THARBAD_DIR + "trail/path11"));
        if (TP->query_encumberance_weight() > 80)
            tired *= 2;
        TP->add_fatigue(-tired);
        SAYBB(" arrives swimming across the river.");
    }
    return 1;
} /* cross_river */

