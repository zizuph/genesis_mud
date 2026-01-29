/*
 * /d/Gondor/common/guild/ithilien/window.c
 *
 * Modifications:
 * 13 Oct 1998, Gnadnar: conform to coding standards, add some items
 */

#pragma save_binary

inherit "/d/Gondor/std/room";
inherit "/d/Gondor/common/lib/drink_water.c";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

#define	MIN_SWIM_SKILL		25
	
#define	PARSE_STR	"[in] [into] [the] [falling] " + \
    "'water' / 'waters' / 'waterfall' / 'falls' / 'window' / 'veil'"

/* prototypes */
public void	create_gondor();
public void	init();
public string	long_func();
public string	exa_window();
public int	do_put(string arg);
public void	drink_message(string where);
public int	do_dive(string arg);


/*
 * Function name:	create_gondor
 * Description	:	set up the room
 */
public void
create_gondor()
{
    set_short("the Window of the Sunset");
    set_long(long_func);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1);
    add_prop(OBJ_I_CONTAIN_WATER, 1);

    add_exit((RANGER_ITH_DIR + "passage1"),    "south", 0, 0);
    add_exit((RANGER_ITH_DIR + "rockchamber"), "east", 0, 0);

    add_item( ({ "waters", "water", "falls", "waterfall",
	"veil", "window" }),
	exa_window);
    add_item( ({ "archway", "rough-hewn gate", "gate", }),
	"A low, roughly shaped arch of stone opens onto dim caves beyond.\n");
    add_item( ({ "dark passage", "passage", }),
	BSN("The dark passage leads south into darkness. Narrow " +
	    "steps are just visible within the shadows of the passage."));
    add_item( ({ "shadows", "stairs", "stair", "narrow steps", "steps", }),
	BSN("Barely visible in the shadows to the south, narrow steps " +
	"wind upwards."));
    add_item( ({ "wet floor", "floor" }),
	"The polished floor glistens with moisture from the waterfall.\n");
    add_item( ({ "fine rain", "rain", "mist", "mists", "moisture" }),
	BSN("Moisture from the waterfall fills the air with a fine rain " +
	"and gleams on the polished surface of the floor."));
    add_item( ({ "surface", "polished stone", "stone", "rock", }),
	BSN("The stone of the floor is polished and gleaming, but " +
	    "the rock walls and roof are rough surfaced and dark."));
    add_item( ({ "wall", "walls" }),
	BSN("The walls appear to be solid rock, roughly finished " +
	    "and damp with moisture from the falls."));
    add_item( ({ "roof", "ceiling" }),
	"Dark rock, uneven and rough surfaced, stoops close overhead.\n");

    /* i don't add "water" and "waters" to this list, even tho they
     * are item names for the waterfall, since the required syntax
     * is "drink water from <place>" and "drink water from water" 
     * looks weird
     */
    set_drink_from( ({ "waterfall", "window", "veil", "falls" }) );
} /* create_gondor */


/*
 * Function name:	init
 * Description	:	add verbs for waterfall
 */
public void
init()
{
    ::init();
    init_drink();

    add_action(do_dive, "dive");
    add_action(do_dive, "enter");
    add_action(do_put, "put");
    add_action(do_put, "hold");
    add_action(do_put, "reach");
    add_action(do_put, "touch");
} /* init */


/*
 * Function name:	long_func
 * Description	:	VBFC for the room description
 * Returns	:	string -- the description
 */
public string
long_func()
{
    string  longtxt =
	"This wet floor of polished stone is the doorstep to a "
      + "rough-hewn gate of rock opening to the east.  A dark "
      + "passage leads away south, and to the west hangs the thin veil of "
      + "a waterfall, so near that its mists fill the air.";

    switch(tod())
    {
        case "night":
            longtxt += " The waterfall is now a dazzling veil of silk "
              + "and pearls and silver thread; melting icicles of "
              + "moonlight.";
            break;
        case "early morning":
            longtxt += " The curtain of water glows yellow with early dawn.";
            break;
        case "morning":
        case "noon":
        case "afternoon":
            longtxt += " Through the veil of the waterfall daylight enters, "
              + "being twisted by the falling water. It is as if the veil "
              + "were pure magic.";
            break;
        case "evening":
            longtxt += " The level shafts of the setting sun behind "
              + "beat upon it, and the red light breaks into many "
              + "flickering beams of ever-changing colour.";
            break;
    }
    return BSN(longtxt);
} /* long_func */


/*
 * Function name:	exa_window
 * Description	:	VBFC for the window desc
 * Returns	:	string -- the description
 */
public string
exa_window()
{
    string  desc;

    switch(CLOCK->query_time_of_day())
    {
        case "evening":
            desc = "The waterfall is to the west, and level rays from "
              + "the setting sun behind it beat upon it, red light being "
              + "broken into many flickering beams of ever-changing "
              + "colour. It is as if you are standing at the window of "
              + "some elven-tower, curtained with threaded jewels of "
              + "silver and gold, and ruby, sapphire and amethyst, all "
              + "kindled with an unconsuming fire.";
            break;
        case "night":
            desc = "The veil of water is now like a dazzling curtain of "
              + "silk and pearls and silver thread and melting icicles "
              + "of moonlight.";
            break;
        case "early morning":
            desc = "The window of the waterfall now glows with a pale "
              + "yellow light now at dawn.";
            break;
        case "morning":
        case "noon":
        case "afternoon":
            desc = "The thin veil of water glows with a bright light "
              + "now in the daytime.";
    }
    return BSN(desc);
} /* exa_window */


/*
 * Function name:	do_put
 * Description	:	handle attempts to put hand in waterfall
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_put(string arg)
{
    string vb = QVB;
    if (!strlen(arg))
    {
	NF0(CAP(vb)+" what where?\n");
    }

    /* they may "reach/put/hold hand/arm .." into the water
     * or they may just touch the water
     */
    if (vb == "put" ||
	vb == "hold" ||
	vb == "reach")
    {
        if (!parse_command(arg, ({}), "'arm' / 'hand' [out] " + PARSE_STR))
	{
	    NF0(CAP(vb)+" what where?\n");
	}
    }
    else if (!parse_command(arg, ({}), PARSE_STR))
    {
	NF0(CAP(vb)+" what?\n");
    }

    write(BSN("You hold your arm out into the falling water. The icy "
      + "water refreshes your weary limb."));
    SAY(" holds " +POSSESSIVE(TP)+" arm out into the falling water.");
    return 1;
} /* do_put */


/*
 * Function name:	drink_message
 * Description	:	do text for drinking from waterfall
 * Arguments	:	string where -- unused
 */
public void
drink_message(string where)
{
    write(BSN("You reach out a cupped hand to catch the falling water, "
      + "and drink an icy draught. The water tastes wholesome, and waves "
      + "of relaxation wash through your tired limbs, soothing your "
      + "weariness."));
    SAY(" reaches out a cupped hand to catch the falling water, and "
      + "drinks an icy draught. A wave of relaxation seems to wash "
      + "through " + POSSESSIVE(TP) + " tired limbs.");
    TP->add_fatigue(10);
} /* drink_message */


/*
 * Function name:	do_dive
 * Description	:	handle attempts to dive into falls
 * Arguments	:	string arg -- whatever the player typed
 * Returns	:	1 on success, 0 on failure
 */
public int
do_dive(string arg)
{
    string	dest;

    if (!strlen(arg) ||
	!parse_command(LOW(arg), ({}), PARSE_STR))
    {
	NF0(CAP(QVB)+" where?\n");
    }

    if (TP->query_skill(SS_SWIM) < MIN_SWIM_SKILL)
    {
	NFN0("You advance to the edge of the waterfall, but " +
	    "change your mind when the icy waters flow " +
	    "across your face.");
    }

    write(BSN( "You dive into the waterfall."));
    SAYBB(" dives into the waterfall.");
    WRITE("You fall through mist-filled air and land " +
	"with a splash in foaming, churning waters.");
    TP->move_living("M", (RANGER_ITH_DIR + "pool"));
    tell_room(ENV(TP),
	QCNAME(TP)+" plunges through the waterfall high above your " +
	"head and lands in the pool.\n", TP);
    return 1;
} /* do_dive */
