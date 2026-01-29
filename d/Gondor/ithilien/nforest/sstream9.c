/*
 *	/d/Gondor/ithilien/nforest/sstream9.c
 *
 *	Coded by Olorin, 1993.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 *	02-Sep-1998, Gnadnar:	add some items, tidy up
 *   04-Okt-2008, Eowul:    Added drinking support 
 */

#pragma strict_types

inherit "/d/Gondor/common/lib/area_room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

public void	create_area_room();
public void	reset_room();
public string	short_desc();

static object  Deer;


/*
 * Function name:	create_area_room
 * Description	:	set up the ravine
 */
public void
create_area_room()
{
    set_areatype(AREATYPE_FOREST);
    set_areadesc("in a ravine");
    set_area("northern");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_treetype("cedar");
    set_extraline("The land is steep and rocky here, and a stream " +
        "is rushing westwards in a narrow ravine down towards the " +
        "Anduin. The vale of that great river opens to the west, " +
	"with green fields on both sides along the river. " +
	"Among the oaks and cedars that cover the slopes, glades "+
	"open to the sky. To the east, the stream comes flowing " +
        "out of a narrow channel.");
    add_item(({"mountains", "mountain-range", "mountain", "ephel duath"}), 
	BSN("From here the mountains named Ephel Duath appear as " +
        "dark grey shadows beyond the green hills to the east. " +
        "You judge the mountains to be between 5000 to 7000 feet " +
	"tall, and you guess they are several leagues away now."));
    add_item(({"forest", "wood", "woods", "herbs", "glades"}),  BSN(
        "Many great oaks and cedars are growing here in groups. " + 
        "Between them are wide glades with bushes, deep green grasses " +
        "and herbs. There are thickets of tamarisk " +
        "and pungent terebinth. Rocky walls are starred with " +
        "saxifrages and stonecrops. The scent of mints and parsleys " +
        "hangs heavily in the air."));
    add_item(({"flower", "flowers", "primerole", "anemones", "lily",
	"asphodel"}), 
	BSN("Primeroles and anemones are awake in filbert-brakes; " +
        "asphodel and many lily-flowers are nodding their half-opened " +
        "heads in the grass."));
    add_item(({"stream", "pool", "water", "ravine"}),  BSN(
        "The stream has of good size, and is rushing down in a " +
        "narrow ravine towards the Anduin in the west. A smaller " +
        "stream comes running down from a slope to the north to join " +
        "the larger one here."));
    add_item(({"gate", "channel"}),  BSN(
        "The waters of the stream come out of a narrow channel to the " +
        "east. There is a narrow ledge running along the stream through " +
        "the gate on which you might walk east."));
    add_item(({"narrow ledge", "ledge"}),
	BSN("A ledge of grey stone runs alongside the stream. "+
	    "It is sufficiently wide to walk upon."));
    add_item(({"grey stone", "stone"}),
	BSN("The dark grey stone is damp with water from "+
	    "the stream."));

    add_cmd_item(({"stream", "pool", "water", "ravine", 
    	       "in stream", "in pool", "in water", "in ravine", 
    	       "into stream", "into pool", "into water", "into ravine"}), 
	({ "enter", "dive", "swim" }),
	BSN("The ravine is too narrow and the waters too swift "+
	    "for swimming."));

    add_exit(ITH_DIR + "nforest/sstream10", "west", 0, 4);
    add_exit(ITH_DIR + "nforest/pool",      "east", 0, 4);

    BEACH;
    add_prop(OBJ_I_CONTAIN_WATER, -1);
    set_drink_from( ({ "stream", "pool", }) );

    set_up_herbs( ({ HERB_DIR + "tyelka",  HERB_DIR + "redweed",
		     HERB_DIR + "chervil", HERB_DIR + "dill", 
		     HERB_DIR + "oregano", HERB_DIR + "rosemary", }),
		  ({ "herbs", "flowers", "thickets", "stones", 
		     "woods","groves"}), 3);

    reset_room();
} /* create_area_room */

/*
 * Function name:	reset_room
 * Description	:	replenish deer & herbs
 */
public void
reset_room()
{
    set_searched(- random(3));

    Deer = clone_npc(Deer, (NPC_DIR + "deer"), (ITH_DIR + "nforest/"));
} /* reset_room */


/*
 * Function name:	short_desc
 * Description	:	generate the short desc of the room
 * Returns	:	string -- the desc
 */
public string
short_desc()
{
    return CAP(areadesc) + " in the forests of " + CAP(area) + " " + areaname;
} /* short_desc */

public void
init()
{
    ::init();

    init_drink();
}