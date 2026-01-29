/* 
 * The base outdoor room for the aesthetics quarter of Palanthas.
 * Mortis 12.2005
 */
#pragma strict_types

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <stdproperties.h>
#include <composite.h>
#include <ss_types.h>
#include <macros.h>
#include CLOCKH

/* Inherit the Ansalon room */
inherit OR_FILE
inherit TDIR + "smell_world";
inherit TDIR + "palanthas_alley";

#define CREATE "create_palan_room"
#define RESET  "reset_palan_room"

public void        init();
public int         do_smell(string arg);
public int         do_alley(string arg);

/*
 * IN NORMAL CASES YOU SHOULDN'T NEED TO CHANGE ANYTHING BELOW
 */

/*
 * This function is called from the main Krynn room. It checks
 * whether or not the room should be reset.
 * The function returns TRUE if there should be a reset.
 */
nomask public int
query_reset()
{
    if (function_exists(RESET, TO))
	return 1;
    return 0;
}

/*
 * This function is called from the main Krynn room.
 */
nomask public void
create_krynn_room()
{
    call_other(TO, CREATE);
	ITEM(({"marble", "rock", "stone"}), "The marble used for building in "
	+ "Palanthas is translucent appearing almost white in the sun.\n");

	ITEM(({"road", "roads", "street", "streets"}), "The road is paved "
	+ "with footlong blocks of translucent marble.  Dust and dirt have "
	+ "ground their way in between the cracks.  Small side streets and "
	+ "alleys occasionally branch off here and there.\n");

	ITEM(({"alley", "alleys", "side street", "side streets"}), "In a city "
	+ "like Palanthas a web of smaller streets and alleys lead into the "
	+ "shadows between the great buildings.  Try <alley> to add "
	+ "convenience to your adventures in the city.\n");

	ITEM(({"block", "blocks"}), "The blocks of marble used for the top layer "
	+ "of the roads in Palanthas are cut from the same translucent marble "
	+ "used throughout the city.  These blocks show a few signs of chisel "
	+ "work, but are more or less smooth.  The marble is so translucent "
	+ "that the brownish-red clay bricks beneath give it a bricklike hue.\n");

	ITEM(({"lamps", "street lamps", "lamp", "street lamp", "glow",
		"yellow glow", "lamp posts", "lamp post"}), "@@get_time_item@@");

    ITEM(({"building", "buildings"}), "Very old marble buildings and homes "
	+ "rise two to three stories here in the Aesthetics quarter.  The "
	+ "oldest buildings share a common architecture, a distinguishing "
	+ "feature of which is a band of chiseled reliefs near the top of some "
	+ "and at the borders between stories in others.  A good many of those, "
	+ "especially near the inner city, bear gargoyles at their top "
	+ "corners just below the roofs.  The newer buildings, such as some "
	+ "shops and homes, are not so antiquated in their styling and more "
	+ "frequently use small marble blocks, tan bricks, and even wood in "
	+ "the poorest areas.\n");

	ITEM(({"band", "bands", "relief", "reliefs"}), "Some of the old "
	+ "buildings in this party of the city are ringed with bands of "
	+ "the chiseled images of citizens, warriors, towers and castles, "
	+ "fantastic beasts and dragons, and events from the city's history.  "
	+ "Others bear popular monks and professors and their works which "
	+ "seem to be popular.\n");

	ITEM(({"gargoyle", "gargoyles"}), "A good many of the older buildings "
	+ "bear gargoyles at the corners of their rooftops, created long ago, "
	+ "it is said, to ward off spirits seeking to do harm.  Though very old "
	+ "they are in sufficient condition to appraise the skill which went "
	+ "into their finely chiseled details.  All the ones you've seen "
	+ "are all generally lanky, squating, and winged with long recurving "
	+ "claws, flat long-mouthed faces, and dull drooping eyes.\n");
	
	ITEM(({"mountains", "peaks"}), "High mountains ring the city save for the "
	+ "southeast pass to the High Clerist's tower and the bay of Branchala to "
	+ "the north.\n");

    ITEM(({"white tower", "tower"}), "The Tower of Lord Amothus Palanthas "
	+ "rises high above the palace in the palatial plaza towards the north "
	+ "at city center.  The polished white marble finishing its walls and "
	+ "crenellations can still be made out from here.  The view from the "
	+ "top is said to be the most splendid in the city.\n");

	ITEM(({"library", "great library", "great library of palanthas"}),
	  "The library is a magnificent, three-story building of translucent "
	+ "marble edged all over in smoothly chiseled elegant patternry and "
	+ "roofed in copper tiles and copper-plated spires which have turned "
	+ "green with exposure to the elements.  Its larger, central spire is "
	+ "topped with an arrow weather vane currently pointing south which "
	+ "can be seen even from this distance.\n");

	ITEM(({"dark tower", "grey tower", "tower of high sorcery"}),
	  "Set deep in the center of a grove of trees generally northwest from "
	+ "here rises a tower of great and dark grey blocks of stone.  At its "
	+ "top are visible from this distance several pinnacles from which no "
	+ "banners fly.\n");

}

public void
init()
{
    ::init();  /* vitally important! never forget this line! */

    add_action(do_smell, "smell");
    add_action(do_smell, "sniff");
    add_action(do_smell, "inhale"); /* a few different verbs, same effect*/
	add_action(do_alley, "alley");
} /* init */


/*
 * Function name:        do_smell
 * Description  :        allow the player to smell the air
 * Arguments    :        string arg - the commands following the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_smell(string arg)
{
    if (strlen(arg) && !parse_command(arg, ({}),
        "[the] 'air' / 'here' / 'area' [of] [the] [city]"))
    {
        return 0; /* the player used syntax we don't agree with */
    }

    /*
     * Note: The above if statement searches for combinations of the
     *       syntax in quotes. Statementes in [] are optional, statements
     *       in '' are required, with / acting as "or" statements. Thus,
     *       we can handle a vast number of combinations, including, but
     *       not limited to:
     *
	 *       air
     *       the air
     *       the air of the city
     *       here
     *       area
     *       etcetera
     *
     *       Of course, we have also made possible odd combinations such
     *       as:
     * 
     *       here the
     *       the area city
     *       etcetera
     *
     *       But a small price to pay for being user friendly. :-)
     */


    smell_world(this_player());
    return 1;
} /* do_smell */

/*
 * Function name:        do_alley
 * Description  :        allow the player to enter a hidden alley
 * Arguments    :        string arg - the commands following the verb
 * Returns      :        int 1 - success, 0 - failure
 *
 */

public int
do_alley(string arg)
{
	if (strlen(arg) && !parse_command(arg, ({}),
        "[n] / [north] / [s] / [south] / [e] / [east] / [w] / [west] / [ne] / [northeast] / [se] / [southeast] / [sw] / [southwest] / [nw] / [northwest]"))
    {
		write("Which alley are you trying to enter?\n");
        return 1; /* the player used syntax we don't agree with */
    }

    palanthas_alley(arg);
    return 1;
}


/*
 * This function is called from the main Krynn room.
 */
nomask public void
reset_krynn_room()
{
    call_other(TO, RESET);
}

string get_time_item()
{
	string ilamp;
    switch(GET_TIMEOFDAY)
	{
    case TOD_DAWN:
	ilamp = "Tall, grey lamp posts are arranged somewhat far apart along the "
	+ "streets, sometimes sporadically, throughout the aesthetic quarter.  "
	+ "They are unlit now, but at night the area is fairly lit thanks to "
	+ "them.\n";
	break;

	case TOD_DAY:
	ilamp = "Tall, grey lamp posts are arranged somewhat far apart along the "
	+ "streets, sometimes sporadically, throughout the aesthetic quarter.  "
	+ "They are unlit now, but at night the area is fairly lit thanks to "
	+ "them.\n";
	break;

    case TOD_TWILIGHT:
	ilamp = "Tall, grey lamp posts are arranged somewhat far apart along the "
	+ "streets, sometimes sporadically, throughout the aesthetic quarter.  "
	+ "City lampiers are out with their long candlestaves lighting the lamps "
	+ "before darkness falls.\n";
	break;

	case TOD_NIGHT:
	ilamp = "Oil lamps atop tall, grey lamp posts glow yellow combining with "
	+ "starlight to illuminate the streets of the aesthetic quarter at night.  "
	+ "They are far enough apart, sometimes sporadically so, to become pools "
	+ "of light in a sea of starlit streets by the bay.\n";
	break;
    default:
	break;
    }
    return ilamp;
}

string constable_symbol()
{
	return "a symbol of an upturned sword over the white palatial tower.";
}