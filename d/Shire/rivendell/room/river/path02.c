/*
 * Shore of river Bruinen
 * By Finwe, August 1998
 */
#pragma strict_types
#include "/d/Shire/sys/defs.h" 
#include "local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
 
inherit SHORE_BASE;

#define HARD_TO_SWIM 16 /* new value for skill = 30 */
#define HARD_TO_CLIMB  5 /* how hard is it to climb the slope? */
#define SWIM_FATIGUE  30 /* how tiring is it to swim? */

#define QVB              query_verb()

static string RName = "Brunien";
 
void
create_shore_room()
{

    set_area("next to");
    set_areaname("the River Bruinen");
    set_land("Eriador");
    set_areatype(7);
    set_areadesc("riverbank");
    set_grass("sparse, dry");
    set_treetype("conifer");

    set_extraline("You stand on the eastern side of the river. The river " +
        "flows by lazily by under overhanging branches of the nearby " +
        "trees. The forest is thick but rising above it are the Misty " +
        "Mountains.");

//set_vbfc_extra(shore_desc);
    add_exit(RIVER_DIR + "path03", "east",0,4);
//    add_exit(RIVER_DIR + "path01", "southwest",0,4);

    reset_shire_room();

}

void
reset_shire_room()
{
}


/*
 * Function name:	init
 * Description	:	add the drinking and river verbs
 */
public void
init()
{
    ::init();
//    init_drink();

    add_action("cross_river", "swim");
    add_action("cross_river", "dive");
    add_action("cross_river", "cross");
} /* init */

/*
 * Function name: swim
 * Description:   Can we cross a body of water by swimming?
 * Argument:      diff  - the difficulty
 *                tired - the fatigue
 * Returns:       0 - success, 1 - failure.
 */
public int
swim(int diff = 10, int tired = 10)
{
    int     skill = TP->query_skill(SS_SWIM);

    diff = diff/2 + random(diff) + 1;
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
        SAYBB(" fails to make it to the other shore.");
        return 1;
    }
    if (TP->query_fatigue() < tired)
    {
        write("You are too tired to cross the river.\n");
        SAYBB(" is too tired to cross the river.");
        return 1;
    }

    write("You swim across the river" 
	  + (strlen(RName) ? " " + RName : "") + ".\n");
    return 0;
}

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
	"'river' / 'brunien' / 'loudwater' %s", junk))
    {
	NF(CAP(QVB) + " where?\n");
        return 0;
    }

    if (!swim(HARD_TO_SWIM, SWIM_FATIGUE))
    {
	SAYBB(" leaves swimming across the river.");
	TP->move_living("M", (RIVER_DIR + "path01"));
	if (TP->query_encumberance_weight() > 80)
	{
	    tired *= 2;
	}
	TP->add_fatigue(-tired);
	SAYBB(" arrives swimming across the river.");
    }
    return 1;
} /* cross_river */

