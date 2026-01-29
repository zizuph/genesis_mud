/* 
 * /d/Gondor/tharbad/ford/f04.c
 *
 * Coded by Zephram.
 *
 * Modification log:
 * 26-Jan-1997, Olorin:    Changed crossing of the river,
 *                         changed inheritance, general revision.
 *
 * 18-June-1998, Tyr:   Added hidden trail exit
 * June-1999, Gnadnar:	clean up, add temporary block on
 *			exit until ready to open.
*  Jan 2000, Morbeche:  Adjusted swim requirements
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/roads.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

// #define HARD_TO_SWIM 25  /* old value for skill = 50 */
#define HARD_TO_SWIM 16 /* new value for skill = 30 */
#define HARD_TO_CLIMB  5 /* how hard is it to climb the slope? */
#define SWIM_FATIGUE  30 /* how tiring is it to swim? */


/* prototypes */
public void	create_roads();
public void	init();
public int	cross_river(string arg);
public int	climb();
public void	drink_message(string from);
public string	tmp_item();


/*
 * Function name:	create_roads
 * Description	:	set up the room
 */
public void
create_roads() 
{
    set_street("riverbank");
    set_where("southeast");
    set_county("Cardolan");
    set_land("Eriador");
    set_mountain("Greyflood slopes");
    set_vegetation("scrubby evergreen creepers and rosebushes");
    set_extraline("An overgrown wide stone road made of cracked and "
      + "slippery paving stones to is running northwest through "
      + Vegetation + " covering the land of " + County + ". The "
      + "road ends here on the northwest bank of a brown turbid "
      + "wide river, the Greyflood or Gwathlo, beneath the ruins "
      + "of a bridge.");

    add_exit((THARBAD_DIR + "road/r28"), "northwest", climb, 6);
    add_exit((THARBAD_DIR + "trail/path1"), "southwest", 0, 2, 1);

    add_item( ({ "road", "old stone road", "old stone paved road",
	"old road", "greenway" }), 
      BSN("The Greenway once crossed the Greyflood here on a "
	+ "bridge that connected it to the old South Road, but "
	+ "the bridge was destroyed long ago when Tharbad "
	+ "was deserted. Now the Greenway ends here on the bank "
	+ "of the Greyflood among the ruins of the bridge. Only "
	+ "a small path continues into the water."));
    add_item( ({ "river", "river greyflood", "greyflood", "gwathlo", }),
      BSN("The river Greyflood runs sluggishly in deep channels "
	+ "here, its water being brown and murky. It is almost "
	+ "too wide to cross, but an experienced swimmer might "
	+ "be able to reach the island in the middle of the "
	+ "river."));
    add_item( ({ "island", }), BSN("Across a wide expanse of brown "
	+ "and muddy water, you can make out a large island in the "
	+ "middle of the river. Long ago, there probably stood one "
	+ "of the pillars that supported the arches of the bridge "
	+ "before it was destroyed. An experienced swimmer might be "
	+ "able to reach the island."));
    add_item( ({ "bridge", "ford", "fords", "fords of tharbad", }),
      BSN("The bridge which once crossed the Greyflood lies in "
	+ "ruins. All that remains of bridge are large heaps of "
	+ "rubble, one right here on this bank of the river, "
	+ "where the old road ends beneath it, another visible "
	+ "on the island in the middle of the river. A narrow path runs "
	+ "from the end of the bridge down to the water, probably "
	+ "used by those who cross the river by swimming across it."));
    add_item( ({ "city", "tharbad", "ruin", "ruins", "old city" }),
      BSN("The ruins of Tharbad are just barely visible on the other "
	+ "bank of the river, but it is impossible to make out "
	+ "any detail from this distance."));
    add_item("water",
      BSN("The water of the river is brown and murky, "
	+ "deep and full of strange eddies."));
    add_item( ({ "scrubby evergreen creepers", "creepers", "rosebushes" }),
      BSN("The limbs and branches of the vegetation here has been "
	+ "carefully rearranged to hide a footpath which heads "
	+ "to the southwest."));
    add_item( ({ "overgrown path", "overgrown footpath", "path",
	"footpath" }),
      BSN("An overgrown path, nearly obscured by vegetation, " +
	"leads southwest."));
    set_drink_from( ({ "river", "greyflood", "gwathlo", }) );
    add_prop(OBJ_I_CONTAIN_WATER, 1000000);
    add_prop(ROOM_I_TYPE, ROOM_BEACH);
} /* create_roads */


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
 * Function name:	cross_river
 * Description	:	handle attempts to cross the river
 * Arguments	:	string arg -- whatever the player typed
 * Returns	    :	int -- 1 if we understand the arg, 0 if not
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
	TP->move_living("M", (THARBAD_DIR + "ford/f03"));
	if (TP->query_encumberance_weight() > 80)
	{
	    tired *= 2;
	}
	TP->add_fatigue(-tired);
	SAYBB(" arrives swimming across the river.");
    }
    return 1;
} /* cross_river */


/*
 * Function name:	climb
 * Description	:	check the uphill exit
 * Returns	:	int -- 0 if may climb, 1 if not
 */
public int
climb()
{   
    int     diff = random(HARD_TO_CLIMB),
    climb = TP->query_skill(SS_CLIMB);

    if (climb < diff)
    {
	write("This hill is too dangerous for you to climb safely.\n");
	write("You lose your footing.\n");
	write("You fall down in a shower of small rocks and gravel!\n");
	TP->reduce_hit_point(diff - climb);
	write("Your body tumbles to a stop near your starting point.\n");
	SAY(" fails to make it up the slope.");
	return 1;
    }
    write("You climb up the stone-choked road.\n");
    return 0;
} /* climb */


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
 * Function name:	tmp_item
 * Description	:	do some items only for wizards until we open
 * Returns	:	string -- the item desc
 */
public string
tmp_item()
{
    if (!TP->query_wiz_level())
    {
	return("You find no " + query_exa_arg() + ".\n");
    }
    if (query_exa_arg() == "path")
    {
	return BSN("The limbs and branches of the vegetation here has been "
	  + "carefully rearranged to hide a footpath which heads "
	  + "to the southwest.");
    }
    return BSN("An overgrown path, nearly obscured by vegetation, " +
      "leads southwest.");
} /* check_open */
