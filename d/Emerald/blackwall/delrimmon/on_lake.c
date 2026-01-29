#pragma strict_types

inherit "/d/Gondor/river/anduin/anduin_onwater";
inherit "/d/Emerald/blackwall/delrimmon/emyn_muil";
inherit "/d/Gondor/common/lib/random_noise.c";

#include "/d/Emerald/blackwall/delrimmon/defs.h"
#include "/d/Gondor/std/water/onwater.h"
#include "/d/Gondor/river/anduin/anduin.h"

/* global variables */
public string   Shore_Desc;  /* desc of the shoreline from the room */

/* prototypes */
public void    create_nen_hithoel();
nomask void    create_anduin_onwater();
public int     random_noise();
public void    init();

public void    set_shore_desc(string s) { Shore_Desc = s; }


/*
 * function name:        create_nen_hithoel
 * description  :        dummy routine for inheriting rooms
 */
public void
create_nen_hithoel()
{
} /* create_nen_hithoel */

/*
 * function name:        create_anduin_onwater
 * description  :        set up the room with area presets
 */
nomask void
create_anduin_onwater()
{
    set_shore_desc("The shoreline is a good distance from your"
      + " current position on the lake.");

    create_nen_hithoel();

    set_short(emyn_muil_short);
    set_long(emyn_muil_long);

    /* water stuff */
    set_watertype("lake");
    set_watername("Del Rimmon");
    set_waterrefs( ({ "water", "waters", "lake", "del rimmon",
        "lake of del rimmon" }) );

    try_item( ({ "shore", "shoreline", "beach", "shore line",
                 "lakeshore", "lake shore", "shore of the lake" }),
        BSN(Shore_Desc));
    try_item( ({ "bank", "banks", "muddy bank", "muddy banks",
                 "west", "west side", "western side",
                 "west side of the lake" }), BSN(
        "The river is surrounded by muddy banks which rise from"
      + " the water along its western side."));
    try_item( ({ "east", "east side", "eastern side",
                 "east side of the lake", "rock", "steep rock",
                 "wall", "wall of rock", "walls of rock", "rock wall",
                 "steep wall of rock", "steep rock", "steep walls",
                 "steep wall", "steep walls of rock" }), BSN(
        "The eastern side of the lake is fenced in by steep sloping"
      + " walls of rock which rise from the water to form the feet"
      + " of the mighty cliffs above them."));
    try_item( ({ "water", "waters", "water of the lake" }), BSN(
        "The water of the lake spreads out around and below you."
      + " Its surface is filled with peaceful grey waves which"
      + " bob unevenly in constant motion."));
    try_item( ({ "wave", "waves", "surface",
                 "surface of the lake", "surface of the water" }), BSN(
        "The surface of the water is in constant motion. Waves"
      + " ripple across the lake, stirring with the occasional"
      + " gust of wind which comes from the east."));

    try_item( ({"rimmon", "rimmon falls", "waterfall", "falls",
                "great waterfall", "great falls"}), BSN(
        "Though it is not visible from this distance, the rumour"
      + " is strong of Rimmon Falls, which booms endlessly as its"
      + " sluice empties the waters of Del Rimmon to the depths"
      + " below the Blackwall Mountains to the distant south."));
    add_view();

} /* create_anduin_onwater */


/*
 * Function name: random_noise
 * Description  : allows us to let the player hear the falls of Rimmon
 * Returns      : int -- non-zero if noises should continue,
 *                 zero if they should stop
 */
public int
random_noise()
{
    tell_room(TO, BSN(      ({
        "In the distance, a deep rumbling echoes along the"
      + " lakeshore.",
        "The deep voice of Rimmon Falls rumbles to the"
      + " southeast.",
        "Calling out in a deep rumble, a great waterfall"
      + " can be heard along the lakeshore.",
        "Endlessly rolling over the lake, the deep voice"
      + " of Rimmon Falls can be heard in the distance.",
        "A deep and throbbing rumble echoes across the lakeshore.",
        })[random(4)] ) );
    return 1;
} /* random_noise */


/*
 * Function name:   init
 * Description  :   init the random noises, and drinking
 */
public void
init()
{
    ::init();
    init_random_noise();
} /* init */
