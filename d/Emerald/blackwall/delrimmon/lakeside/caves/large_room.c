/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/caves/large_room.c
 *
 *  A little ways into the cave which lies in the side of the western
 *  cliffs which surround Del Rimmon in the Blackwall Mountains..
 *
 *  Copyright (c) September 1998, by Cooper Sherry (Gorboth) 
 *
 *  Special thanks to Gnadnar for helping me tustle with parse_command
 *  in this file. - Gorboth
 *
 *  Emerald Conversion: July 2001
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/legacy/random_noise";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
void           create_del_rimmon();
public int     random_noise();
public void    init();
public int     do_enter(string arg);
public int     do_climb(string arg);

/*
 *  Function name:    create_del_rimmon
 *  Description  :    set up the room
 */
void
create_del_rimmon()
{
    set_noise_interval(70, 60);

    set_short("a large cavernous chamber within the cliffs of the"
            + " Blackwall Mountains");
    set_long(BSN(
        "Dark cavern walls rise high above this chamber to form a vaulted"
      + " ceiling within the cliffs. Niches in the rock are dimly visible"
      + " along the walls, giving an even more spacious feel to this"
      + " already massive cavern. To the east, the walls narrow"
      + " and a passageway leads toward a tiny point of light in the"
      + " distance. A doorway of some kind lies just to the west."));

    add_item( ({"cave", "cavern", "here", "area", "chamber"}), BSN(
        "This cavern is very spacious, with a high vaulted ceiling"
      + " of naturally formed rock and steep walls running in a wide"
      + " circular perimeter."));
    add_item( ({"ceiling", "high ceiling", "vaulted ceiling",
                "high vaulted ceiling", "up", "roof", "cave roof",
                "cavern roof", "roof of the cave", 
                "roof of the cavern"}), BSN(
        "The ceiling rises high above the cavern floor here, supported"
      + " by rock walls on all sides which slope gradually"
      + " inward to form massive support structures. Thousands of"
      + " stalagtites of varied size hang from the wet stone roof."));
    add_item( ({"wet roof", "stone roof", "wet stone roof"}), BSN(
        "The many stalagtites which hang from the roof are an indication"
      + " that water from some high place has seeped into this cave."));
    add_item( ({"water from some high place"}), BSN(
        "The origin of the water which drips from the ceiling is not"
      + " known to you."));
    add_item( ({"stalagtite", "stalagtites"}), BSN(
        "Stalagtites cling to the high vaulted ceiling of this cavern,"
      + " adding a quality of beauty to the stone. Droplets of water"
      + " fall from their height to the ground occasionally."));
    add_item( ({"droplets", "droplet", "drip", "drips",
                "droplets of water", "droplet of water",
                "drip of water", "drips of water"}), BSN(
        "Water drips slowly and continuously from the roof of this"
      + " large cavern. A small pool has formed at one end of the"
      + " cave, where the falling droplets seem to have collected."));
    add_item( ({"pool", "dark pool", "small pool", "pool of water"}), BSN(
        "A dark pool of water rests toward the northern corners of this"
      + " cavern. The surface of the water appears to be perfectly still,"
      + " aside from the occasional ripples which extend from a falling"
      + " droplet of water."));
    add_item( ({"surface of the water", "surface of the pool"}), BSN(
        "The surface of the pool tells little of the depth of the water"
      + " or of anything lying beneath the liquid. The water appears"
      + " black and silent."));
    add_item( ({"water", "moisture", "liquid"}), BSN(
        "There appears to be quite a bit of moisture in this cave."
      + " Droplets fall from stalagtites high above into a quiet pool"
      + " which rests in the northern corner of this cavern."));
    add_item( ({"depth", "depth of the pool"}), BSN(
        "The bottom of the pool is not visible, and the surface of the"
      + " water does not betray the depths that rest beneath it."));
    add_item( ({"rock", "rocks", "stone", "stones"}), BSN(
        "The rock which forms the entire cavern is black and very rough"
      + " and crumbled."));
    add_item( ({"wall", "walls", "steep wall", "steep walls", 
                "dark walls", "cavern walls", "dark cavern walls",
                "cave wall", "cave walls", "walls of the cave",
                "rock wall", "rock walls", "dark wall",
                "cavern wall", "dark cavern wall"}), BSN(
        "The walls of this cavern rise steeply above and to all sides,"
      + " forming a wide and spacious perimeter. Niches lie cracked"
      + " in the walls, especially to the northwest and south, where"
      + " they appear to run a ways into the rock. Above, the walls"
      + " slope inward to form massive support structures for the"
      + " vaulted ceiling of the cavern."));
    add_item( ({"niche", "niches", "perimeter", "circular perimeter",
          "wide perimeter", "spacious perimeter",
          "wide and spacious perimeter"}), BSN(
        "There are many niches in this cavern, where the walls have"
      + " cracked and been eroded over the centuries. Two particularly"
      + " large niches are visible - one to the south and one to the"
      + " northwest."));
    add_item( ({"northwest", "northwest niche", "northwestern niche",
                "niche to the northwest", "one to the northwest"}), BSN(
        "Water from a pool in this corner of the cave extends into the"
      + " base of this niche, which appears to run a short distance"
      + " into the cave wall."));
    add_item( ({"base of the niche", "base of this niche"}), BSN(
        "There is no easy way to tell how deep the water is in the"
      + " niche short of actually wading in."));
    add_item( ({"south", "south niche", "southern niche",
                "niche to the south", "one to the south"}), BSN(
        "The niche in the wall to the south is tall and very thin,"
      + " seemingly little more than a crack in the rock itself."));
    add_item( ({"sky", "sun", "moon"}), BSN(
        "The sky is not visible from within this cavern, making it"
      + " difficult to tell whether it is day or night."));
    add_item( ({"passageway", "passageway to the east"}), BSN(
        "The cave walls to the east extend into the distance, narrowing"
      + " as they approach a tiny point of light in the distant"
      + " darkness."));
    add_item( ({"distance", "distant darkness", "light", "point",
                "point of light", "tiny point",
                "tiny point of light",
                "tiny point of light in the distance"}), BSN(
        "A tiny point of light is visible in the distant darkness to"
      + " the east, where a passageway leads out of this spacious"
      + " cavern."));
    add_item( ({"dark", "darkness"}), BSN(
        "Darkness fills this cavern, working its way into every niche"
      + " and corner."));
    add_item( ({"corner"}), BSN(
        "For the most part, this cavern is round, aside from a corner"
      + " to the northwest, where a pool of water rests in the"
      + " shadows."));
    add_item( ({"shadow", "shadows"}), BSN(
        "Shadows are all around you here."));
    add_item( ({"northwest corner", "corner to the northwest"}), BSN(
        "A small pool of water rests quietly in the corner to the"
      + " northwest, tucked silently in among the shadows."));
    add_item( ({"ground", "floor", "cavern floor", "cave floor"}), BSN(
        "The cavern floor is rocky and dark, except to the north,"
      + " where a pool lies nestled in a corner of the cave."));
    add_item( ({"crack", "cracks", "crack in the rock",
                "cracks in the rock"}), BSN(
        "The niche in the rock wall to the south is tall and thin,"
      + " most likely formed by natural processes."));
    add_item( ({"door", "doorway", "doorway of some kind"}), BSN(
        "A doorway has been carved in the cave wall to the west,"
      + " quite obviously by forces other than those of nature."));

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);

    add_exit(DELRIMMON_DIR + "lakeside/caves/entrance", "east");
    add_exit(DELRIMMON_DIR + "lakeside/caves/cave_fork", "west");

    set_no_exit_msg( ({ "northwest", "north", "northeast",
                        "southwest", "south", "southeast" }),
        "The dark cave walls block your progress.\n");
} /* create_del_rimmon */

/*
 * Function name: random_noise
 * Description  : the player can hear drips in the chamber
 * Returns      : int -- non-zero if noises should continue,
 *                 zero if they should stop
 */
public int
random_noise()
{
    tell_room(TO, BSN(        ({
        "A sudden sound of water dripping breaks the silence, and you"
      + " see ripples running to the edges of a pool in the shadows.",
        "The sound of dripping water echoes through the cavern.",
        "A droplet of water echoes through the cave as it falls from"
      + " somewhere above.",
        })[random(3)] ) );

    return 1;
} /* random_noise */

/*
 * Function name:   init
 * Description  :   init the random noises
 */
public void
init()
{
    ::init();
    init_random_noise();

    add_action(do_enter, "swim");
    add_action(do_climb, "climb");
    add_action(do_enter, "enter");
} /* init */

/*
 * Function name:        do_climb
 * Description  :        handle attempts to climbing (you can't)
 * Arguments    :        arg -- what the player typed
 */
public int
do_climb(string arg)
{
    NFN0("Climbing is not possible in this cave, as the walls are"
       + " very steep, and angle inward.");
} /* do_climb */

/*
 * Function name:       do_enter
 * Description  :       handle attempts to enter pool/niches
 * Arguments    :       string arg -- whatever the player typed
 * Returns      :       1 on success, 0 on failure
 */
public int
do_enter(string arg)
{
    if (!strlen(arg))
    {
        NFN0(CAP(QVB)+" where?");
    }
    arg = LOW(arg);

    if (!CAN_SEE_IN_ROOM(TP))
    {
        NFN0("You can not see well enough in here to try that.");
    }

    if (arg == "niche" || arg == "in niche")
    {
        NFN0("There are only two niches in the cavern walls which appear"
           + " large enough for that - one to the northwest, and one"
           + " to the south.");
    }

    if (parse_command(arg, ({}),
        "[small] [dark] [small] 'pool' [of] [water]"))
    {
        WRITE("You wade carefully into the pool of water, which is"
            + " apparently quite shallow. There is clearly not enough"
            + " depth for one to swim here, and so you emerge from the"
            + " pool with little more than wet feet.");
        return 1;
    }
    if (parse_command(arg, ({}),
        "[in] [the] [northwest] / [northwestern] 'niche' / " +
        "'one' [to] [the] [northwest]"))
    {
        WRITE("The niche appears to narrow dramatically as it travels"
            + " into the rock, growing extremely cramped. After a few"
            + " feet, the roof of the niche is just barely above the"
            + " water which extends into the crack, and you cannot"
            + " proceed.");
        return 1;
    }
    if (parse_command(arg, ({}),
        "[in] [the] [south] / [southern] 'niche' / "
      + "'one' [to] [the] [south]"))
    {
        WRITE("Stepping into the niche to the south, you are"
            + " immediately impressed by the height of this crack in"
            + " the cave wall. Finding nothing of particular interest,"
            + " you step back into the perimeter of the cavern.");

        return 1;
    }
    NFN0(CAP(QVB) + " where?");
} /* do_enter */
