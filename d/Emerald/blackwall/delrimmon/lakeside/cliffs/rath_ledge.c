/*
 *  /d/Emerald/blackwall/del_rimmon/lakeside/cliffs/rath_ledge.c
 *
 *  This is a ledge which runs along the south side of Melan Rath,
 *  overlooking Rimmon Falls. A stone stairwell here runs up to the
 *  heights of the tall peak.
 *
 *  Copyright (c) March 2001, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/legacy/del_rimmon_room";
inherit "/d/Emerald/blackwall/delrimmon/del_rimmon";
inherit "/d/Emerald/blackwall/delrimmon/legacy/random_noise";

#include <stdproperties.h>
#include <macros.h>      /* for QCTNAME, etc */
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/*
/* prototypes */
public void        create_del_rimmon();
public int         do_climb(string arg);
public void        init();
public string      exa_melan_earl();
public string      exa_beacon();
public string      exa_shadows();
public int         random_noise();


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    add_name("del_rimmon_cliffs");
    set_short("a ledge along the southern slopes of Melan Rath");
    set_long(del_rimmon_long);

    set_extraline("A long ledge here curves around the southern slopes"
      + " of Melan Rath, whose high peaks rise out of sight. The ledge"
      + " seems to have come to a halt here, dwindling to nothing more"
      + " than a shift in the walls of rock to the northeast. Downwards"
      + " and to the northwest, it leads around to the eastern base of"
      + " the peak. Just to the east, far below these heights, the tumult"
      + " of Rimmon Falls rises as a dull roar.");

    add_item( ({ "mountains", "blackwall mountains", "mountain",
                 "hill", "hills", "range" }),
        "The Blackwall Mountains extend to the east and west as far"
      + " as the eye can see. The range extends far to the north as"
      + " well, but that view is not available here.\n");
    add_item( ({ "ledge", "here", "area", "long ledge", "path",
                 "pathway", "shift" }),
        "The ledge beneath you juts out from the rock walls just far"
      + " enough to provide a comfortable walking space. It does not"
      + " appear to have seen much use for a very long time, as it"
      + " is crowded with many fallen stones and loose rocks which must"
      + " have fallen from above. To the east and northeast it narrows"
      + " to the point of being unusable. It does not appear that it"
      + " ever went much past this point.\n");
    add_item( ({ "wall", "walls", "rock wall", "rock walls",
                 "cliff", "side", "sides", "cliffside", "cliffsides",
                 "slope", "slopes", "wall of rock", "walls of rock" }),
        "The cliff slopes of Melan Rath rise above and below this"
      + " path to the north. The path itself seems to have been"
      + " hewn from their sides, formed by carving away a portion of"
      + " the rock to create a walking space. A narrow cleft of some"
      + " kind rises just to the north of the path here.\n");
    add_item( ({ "cleft", "narrow cleft", "north" }),
        "Just to the north of the pathway, a narrow cleft is visible"
      + " in the walls of the cliff. Looking closer, you notice what"
      + " appear to be steps carved there, though they are in a state"
      + " of significant disuse.\n");
    add_item( ({ "step", "steps", "stair", "stairs", "stairway" }),
        "There is no mistaking the steps. They run from the path up"
      + " the slopes of Melan Rath, apparently to the very summit."
      + " It seems clear that they have been traversed very little"
      + " for many long years, as they are crowded by stones and"
      + " debris which have collected.\n");
    add_item( ({ "melan rath", "peak" }),
        "Melan Rath looms before, above, and below you. Its high peaks"
      + " rise up above many hundreds of feet, and its base is a long"
      + " way below. This ledge appears to be roughly halfway up its"
      + " slopes.\n");
    add_item( ({ "summit", "top" }),
        "The summit of Melan Rath is high above, quite out of view"
      + " from this ledge.\n");
    add_item( ({ "base", "base of melan rath" }),
        "The base of Melan Rath is far below, framing the western"
      + " edge of Rimmon Falls.\n");
    add_item( ({ "falls", "waterfall", "waterfalls", "water",
                 "rimmon", "rimmon falls" }),
        "Rimmon Falls are visible far below to the east of this ledge."
      + " Even from this great height, the low rumble of the massive"
      + " sluice emptying its contents to the depths churns your"
      + " innards.\n");
    add_item( ({ "del rimmon", "lake", "waters", "waters of the lake" }),
        "The lake itself is not visible from here, though the waterfall"
      + " which empties its waters most certainly is.\n");
    add_item( ({ "melan earl", "east" }), exa_melan_earl);
    add_item( ({ "rocks", "stones", "debris", "stone", "rock",
                 "loose rock", "loose rocks" }),
        "Debris clutter the ledge, strong evidence that this way"
      + " has been travelled very little over the years.\n");
    add_item( ({ "beacon", "beacon of light", "magic beacon",
                 "summit of Melan Earl", "summit of melan earl",
                 "dazzling beacon" }), exa_beacon);
    add_item( ({ "shadow", "shadows", "long shadow", "long shadows" }),
                  exa_shadows);

    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_exit(DELRIMMON_DIR + "lakeside/east_overlook", "northwest");
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/rath_summit", "up",
             0, 10, 1);

    set_no_exit_msg( ({ "north" }),
        "The slopes of Melan Rath rise to block your movement to the"
      + " north.\n");
    set_no_exit_msg( ({ "northeast" }),
        "The path narrows dramatically in that direction. There is no"
      + " room to walk further northeast.\n");
    set_no_exit_msg( ({ "east", "southeast", "south", "southwest",
                        "west" }),
        "You step close to the edge, and peer downward. You decided not"
      + " to continue any further in that direction.\n");

    add_view();
} /* create_del_rimmon */


/*
 * Function name:        do_climb
 * Description  :        allow the player to climb up the steps
 * Arguments    :        string - what the player typed.
 * Returns      :        int 1 - success, 0 - failure
 */
public int
do_climb(string arg)
{
    if (!strlen(arg))
    {
        NFN0("Climb what?");
    }

    if (arg == "up")
    {
        write("What do you wish to climb up?\n");
        return 1;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [stone] 'stair' / 'stairs' / 'stairway' /"
      + " 'steps' / 'cleft'"))
    {
        return 0; /* we don't follow their syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally, we would move the player 'up' here using"
            + " command. Since you are a wizard, you'll have to move"
            + " yourself manually. Just type 'up'.\n");
        return 1;
    }

    write("You struggle to climb up the long stairway to the"
        + " summit.\n");
    this_player()->command("$up");

    return 1;
} /* do_climb */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();
    init_random_noise();

    add_action(do_climb, "climb");
} /* init */


/*
 * Function name:        exa_melan_earl
 * Description  :        allow the player to examine melan earl. If
 *                       the beacon is lit, we get additional desc.
 * Returns      :        string - the description
 */
public string
exa_melan_earl()
{
    string txt;

    txt = "To the east, Melan Earl rises to frame the eastern side of"
        + " Rimmon Falls. A sister peak to Melan Rath, it rises many"
        + " hundreds of feet above the waters of the lake. ";

    if (query_beacon())
    {
        txt += " A brilliant light blazes from atop its summit, as if"
             + " some kind of dazzling beacon is there lit.";
    }

    return txt + "\n";
} /* exa_melan_earl */


/*
 * Function name:        exa_beacon
 * Description  :        allow the player to examine the beacon atop
 *                       Melan Earl, assuming that it has been lit
 * Returns      :        string - the description
 */
public string
exa_beacon()
{
    if (!query_beacon())
    {
        return "The summit of Melan Earl is made up of flat, barren"
             + " rock.\n";
    }

    return "From this distance, you are not able to see any great"
         + " detail atop the summit of Melan Earl. The beacon there"
         + " blazes brilliantly, sending unnatural illumination"
         + " througout the entire area, and casting long shadows.\n";
} /* exa_beacon */


/*
 * Function name:        exa_shadows
 * Description  :        if the beacon is lit, we allow the players
 *                       to see shadows
 * Returns      :        string - the description
 */
public string
exa_shadows()
{
    if (!query_beacon())
    {
        return "You find no " + Exa_arg + ".\n";
    }

    return "From here, the shadows all point away from the source of"
         + " light atop Melan Earl, mostly pointing west southwest.\n";
} /* exa_shadows */


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
        "The rush and thunder of the falls shakes the air.",
        "The voice of Rimmon Falls issues up from below, a"
      + " mighty roaring mingled with a deep throbbing boom.",
        "Rimmon Falls roar on, endlessly.",
        "Deep and unchanging, the roar of Rimmon Falls calls"
      + " out beneath the slopes.",
        })[random(3)] ) );
    return 1;
} /* random_noise */
