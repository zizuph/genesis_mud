/*
 *  /d/Emerald/blackwall/del_rimmon/lakeside/cliffs/rath_summit.c
 *
 *  This is the summit of Melan Rath. It commands the most complete
 *  view of the basin of Del Rimmon, and was often used as a lookout spot
 *  by Formandil's men because of this virtue.
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


/* prototypes */
public void        create_del_rimmon();
public int         climb_pillar(string arg);
public void        init();
public int         random_noise();
public string      exa_shadow();
public string      exa_location();
public string      exa_melan_earl();
public string      exa_area_shadows();
public string      exa_beacon();
public string      exa_rannath();


/*
 * Function name:        create_del_rimmon
 * Description  :        set up the room
 */
public void
create_del_rimmon()
{
    add_name("del_rimmon_cliffs");
    set_short("atop the summit of Melan Rath");
    set_long(del_rimmon_long);

    set_extraline("Here atop the pinnacle of Melan Rath, many hundreds"
      + " of feet above the ground, the view is truly astonishing."
      + " Below, and to the north,"
      + " the lake of Del Rimmon shimmers beneath the cliffs of the"
      + " surrounding mountains, which ring it on all sides. Just to"
      + " the east, and at roughly level height with this summit,"
      + " Melan Earl stands tall in the distance, a sister peak to"
      + " Melan Rath. Set apart from these two, and slightly to the"
      + " north, Ael Rannath lifts its tall spire from the very water"
      + " of the lake to tower before the falls. A tall iron pillar"
      + " is set into the ground here.");

    add_item( ({ "pillar", "iron pillar", "iron", "pillar of iron" }),
        "A tall pillar of iron rises from the rocks here at the top"
      + " of Melan Rath. It extends perhaps four meters into the air."
      + " Set atop the pillar is what appears to be a sparkling"
      + " jeweled headpiece. A tiny figure has been carved into the"
      + " surface of the pillar.\n");
    add_item( ({ "figure", "tiny figure", "eye", "figure of an eye",
                 "surface of the pillar", "carving", "carved figure" }),
        "Peering closely at the pillar, you notice the figure of an"
      + " eye which has been carved into its surface.\n");
    add_cmd_item( ({ "eye", "figure", "figure of an eye" }),
                  ({ "push", "press", "touch" }),
        "You press lightly on the figure, but nothing happens.\n");
    add_item( ({ "jewel", "jewels", "jeweled headpiece",
                 "sparkling headpiece", "sparkling jeweled headpiece",
                 "headpiece", "torque", "crystal torque",
                 "red-stoned torque", "glittering torque",
                 "glittering red-stoned torque",
                 "glittering red-stoned crystal torque" }),
        "A glittering red-stoned crystal torque has been set atop"
      + " the iron pillar. Light glints off of its surface.\n");
    add_item( ({ "wind", "breeze" }),
        "In this high place, the wind is constant and at times comes"
      + " in strong gusts.\n");
    add_item( ({ "location", "specific location", "tip of the shadow",
                 "shadow's tip", "shadow tip", "shadows tip",
                 "shoreline" }),
                  exa_location);
    add_item( ({ "finger", "finger of shadow", "long finger",
                 "shadow of ael rannath" }),
                exa_shadow);
    add_item( ({ "topmost spire", "topmost spire of melan earl",
                 "summit of melan earl", "beacon", "light",
                 "radiance", "illumination", "dazzling light", 
                 "dazzling illumination", "glow" }), exa_beacon);
    add_item( ({ "shadows", "long shadows" }), exa_area_shadows);

    add_item( ({ "melan earl", "sister peak", "sister spire",
                 "east" }), exa_melan_earl);
    add_item( ({ "ael rannath", "midmost peak", "middle peak",
                 "island" }), exa_rannath);
    add_item( ({ "melan rath", "summit", "peak", "area", "here",
                 "pinnalce", "pinnacle of melan rath" }),
        "Melan Rath rises beneath you, thrusting high into the air"
      + " to form the summit upon which you stand. This peak is one"
      + " of three which rise from this, the southern end of the"
      + " lake of Del Rimmon which shimmers beneath you to the"
      + " north.\n");
    add_item( ({ "view", "vista" }),
        "This high peak commands a magnificent vista of the entire"
      + " region. The surrounding terrain is spread out below like"
      + " a map on all sides.\n");
    add_item( ({ "lake", "river", "del rimmon", "water" }),
        "The lake of Del Rimmon lies to the north, nestled far beneath"
      + " this tall place between the many cliffs of the Blackwall"
      + " Mountains which ring it on all sides. Its waters shimmer and"
      + " gleam in the cool mountain air.\n");
    add_item( ({ "cliffs", "cliff", "head", "heads",
                 "top", "tops", "ridge", "ridges",
                 "rocky ridge", "rocky ridges",
                 "high ridge", "high ridges",
                 "high rocky ridge", "high rocky ridges",
                 "towering cliff", "towering cliffs",
                 "blackwall mountains", "mountains", "mountain" }),
        "The towering cliffs of the Blackwall Mountains spread out"
      + " to the east, west, and north of this high place. They"
      + " completely surround the lake, fencing it in on all sides.\n");
    add_item( ({ "falls", "waterfall", "rimmon falls" }),
        "Just to the east of this peak, the waters of Del Rimmon"
      + " can be seen far below emptying over the giant sluice"
      + " known as Rimmon Falls. The spray and pounding surge"
      + " from the great waterfall is present even from this"
      + " height.\n");
    add_item( ({ "spray", "mist", "vapour", "vapor", "water vapor",
                 "water vapour", "trails", "trails of mist",
                 "trail of mist" }),
        "Trails of mist waft gently up to the east between"
      + " this peak and Melan Earl from the great waterfall"
      + " below.\n");
   add_item( ({ "sluice", "giant sluice" }),
        "There must be hundreds of metric tons of water flowing over the"
      + " sluice each second. The sheer volume and"
      + " grandeur of this natural display is deeply moving.\n");

    add_cmd_item( ({ "torque", "headpiece", "crystal torque",
                     "jeweled headpiece", "red-stoned torque",
                     "glittering torque", "glittering red-stoned torque",
                     "glittering red-stoned crystal torque" }),
                  ({ "get", "take", "search", "touch" }),
        "The torque is mounted atop the iron pillar, far out of your"
      + " reach.\n");


    add_prop(ROOM_I_NO_ALLOW_STEED, 1);
    add_exit(DELRIMMON_DIR + "lakeside/cliffs/rath_ledge", "down");

    add_lakeview();
    add_view();
} /* create_del_rimmon */


/*
 * Function name:        climb_pillar
 * Description  :        allow players to try to climb up the pillar
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
climb_pillar(string arg)
{
    if (!strlen(arg))
    {
        NFN0("What do you wish to climb?");
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [iron] 'pillar' [of] [iron]"))
    {
        return 0; /* can't figure out the syntax */
    }

    write("You grip the sides of the iron pillar, and work to"
        + " climb upward. The surface is somewhat rough, and you"
        + " are able to grip it well enough to slowly make your"
        + " way up its length. As you near the top, and reach to"
        + " touch the crystal torque, a strange force holds you"
        + " in check, and you are unable to continue. After trying"
        + " a few more times, you climb back down, and stand beside"
        + " the pillar once again.\n");

    return 1;
} /* climb_pillar */


/*
 * Function name:        init
 * Description  :        set up the room noises
 */
public void
init()
{
    ::init();
    init_random_noise();

    add_action(climb_pillar, "climb");
} /* init */


/*
 * Function name: random_noise
 * Description  : add blowing breeze to the room
 * Returns      : int -- non-zero if noises should continue,
 *                 zero if they should stop
 */
public int
random_noise()
{
    tell_room(TO, BSN(      ({
        "Cold wind blows against your face and hands.",
        "The wind whips against your clothing.",
        "The light whistle of the wind picks up suddenly.",
        "A few birds fly overhead, fighting the high mountain"
      + " winds.",
        })[random(3)] ) );
    return 1;
} /* random_noise */


/*
 * Function name:        exa_shadow
 * Description  :        allow the player to examine the shadow of
 *                       Ael Rannath. If they have read the tablet, then
 *                       they might know a bit about what they are
 *                       seeing
 * Returns      :        string - the description
 */
public string
exa_shadow()
{
    string txt;

    if (!query_beacon())
    {
        return "You find no " + Exa_arg + ".\n";
    }

    txt = "A long shadow extends from the base of Ael Rannath to the"
        + " western shores of the lake. ";

    if (MANAGER->query_read_tablet(this_player()) == "Yes")
    {
        txt += "The tip of the shadow has the resemblance of a great"
             + " finger, and almost seems to be pointing at a specific"
             + " location along the shoreline.";

        MANAGER->set_saw_shadow(this_player(), "Yes");
    }

    return txt + "\n";
} /* exa_shadow */


/*
 * Function name:        exa_location
 * Description  :        allow the player to examine the location to
 *                       which the shadow points, assuming they might
 *                       know about doing so
 * Returns      :        string - the description
 */
public string
exa_location()
{
    string txt;

    if (MANAGER->query_saw_shadow(this_player()) != "Yes" ||
        !query_beacon())
    {
        return "You find no " + Exa_arg + ".\n";
    }

    MANAGER->assign_door_location(this_player());

    txt = "The tip of the shadow which extends from Ael Rannath appears"
        + " to be pointing directly";

    switch(MANAGER->query_door_location(this_player()))
    {
        case STUMP:
            txt += " at a large hollow stump which rests near to"
                 + " the base of the cliffs.";
            break;
        case CLIFF:
            txt += " to a flattened area of the cliffs directly"
                 + " west from the center of the lake.";
            break;
        case SAND:
            txt += " at a fern-crowded depression along the northwestern"
                 + " slopes of the lake shore which rests within the"
                 + " woods.";
            break;
        case CLEARING:
            txt += " to a small clearing in the woods along the"
                 + " western shores of the lake.";
            break;
        case BOULDER:
            txt += " at a large boulder which rests in the woods"
                 + " along the northwestern shore of the lake.";
            break;
        default:
            txt += " at a wrongness in the fabric of space and time."
                 + " Please bugreport this to Gorboth at once.";
    }

    return txt + "\n";
} /* exa_location */


/*
 * Function name:        exa_melan_earl
 * Description  :        allow players to see Melan Earl, and provide
 *                       special comments if the beacon is lit.
 * Returns      :        string - the description
 */
public string
exa_melan_earl()
{
    string txt = "Melan Earl towers beside the peak upon which you stand,"
               + " rising many hundreds of feet above the water to stand"
               + " summit to summit with Melan Rath. ";

    if (query_beacon())
    {
        txt += "Its topmost spire is completely aglow, sending forth a"
             + " dazzling light which illuminates the entire region,"
             + " sending unnatural shadows radiating from its"
             + " brilliance.";
    }
    else
    {
        txt += "Its topmost spire is bare of any vegetation.";
    }

    return txt + "\n";
} /* exa_melan_earl */


/*
 * Function name:        exa_area_shadows
 * Description  :        describe the shadows which are cast if the
 *                       beacon is lit.
 * Returns      :        string - the description
 */
public string
exa_area_shadows()
{
    if (!query_beacon())
    {
        return "You find no " + Exa_arg + "\n";
    }

    return "The beacon atop the summit of Melan Earl sends long"
         + " shadows radiating out in all directions from its"
         + " brilliance. Here, atop Melan Earl, the shadows point"
         + " due west.\n";
} /* exa_area_shadows */



/*
 * Function name:        exa_beacon
 * Description  :        describe the beacon, assuming that it has been
 *                       lit
 * Returns      :        string - the description
 */
public string
exa_beacon()
{
    if (!query_beacon())
    {
        return "The topmost spire of Melan Earl is bare of any"
             + " vegetation, but otherwise appears nondescript.\n";
    }

    return "From here, you have a very clear view of the beacon which"
         + " shines from atop Melan Earl. You must squint to see it"
         + " clearly, for the blazing light is too intense to stare"
         + " at heedlessly. Strangely, there does not appear to be"
         + " any special object there, but rather, the very rock of"
         + " the spire itself is ablaze with illumination, as if some"
         + " sleeping enchantment has sprung to life.\n";
} /* exa_beacon */


/*
 * Function name:        exa_rannath
 * Description  :        describe ael rannath, with a mention of
 *                       the shadow it casts if the beacon is lit.
 * Returns      :        string - the description.
 */
public string
exa_rannath()
{
    string txt = "Ael Rannath looms majestically to the north, rising"
               + " from the waters of Del Rimmon to tower at almost"
               + " level altitude with this summit. Its tall cliffs"
               + " are steep slopes upon which trees climb, mounting"
               + " one head above another; and above them again are"
               + " grey faces of inaccessible rock, crowned by a"
               + " great spire of stone. ";

    if (query_beacon())
    {
        txt += "The light from the beacon striking the tall island"
             + " creates a dramatic effect - the shadow of Ael"
             + " Rannath extends like a long finger over the"
             + " waters of the lake, pointing toward the western"
             + " cliffs.";
    }

    return txt + "\n";
} /* exa_rannath */


