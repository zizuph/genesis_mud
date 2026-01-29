#pragma save_binary
/*
 *  /d/Gondor/guilds/rangers/ithilien/window.c
 *
 * Modifications:
 * 13 Oct 1998, Gnadnar: conform to coding standards, add some items
 * 20-Jul-2001, Alto: more tidy up, change inheritance for new
 *                   rangers. Added stairwell.
 * 25-Sep-2006, Toby: Added new line in lookers drinking.
 */
inherit "/d/Gondor/std/room.c";
inherit "/d/Gondor/common/lib/drink_water.c";

#include "../rangers.h"
inherit RANGERS_ITH_DIR + "ith_funcs.c";
inherit RANGERS_DIR + "member_vote.c";


#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/common/lib/clock.h"
#include "/d/Gondor/defs.h"
#include "exit.c"


#define MIN_SWIM_SKILL 25

#define PARSE_STR      "[in] [into] [the] [falling] 'water' / " + \
                       "'waters' / 'waterfall' / 'falls' / 'window' / 'veil'"

/* prototypes */
public void     create_gondor();
public void     init();
public string   long_func();
public string   exa_window();
public int      do_put(string arg);
public void     drink_message(string where);
public int      do_dive(string arg);
object          gMaster;
int             gRqStageStored = rq_stage();


/*
 * Function name: create_gondor
 * Description  : set up the room
 */
public void
create_gondor()
{
    set_short("the Window of the Sunset");
    set_long(long_func);
    create_votes("ithilien");

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(OBJ_I_CONTAIN_WATER, 1);
    add_prop(ROOM_M_NO_SCRY, 1);

    add_exit((RANGERS_ITH_DIR + "passage1"),    "south", &check_ranger());
    add_exit((RANGERS_ITH_DIR + "rockchamber"), "east",  &check_ranger());
    add_exit((RANGERS_ITH_DIR + "vantage1"),    "up", &check_ranger());

    add_item( ({ "waters", "water", "falls", "waterfall", "veil",
        "window" }), exa_window);
    add_item( ({ "archway", "rough-hewn gate", "gate", }), "A low, "
        + "roughly shaped arch of stone opens onto dim caves beyond.\n");
    add_item( ({ "dark passage", "passage", }), "The dark passage leads "
        + "south into darkness. Narrow steps are just visible within the "
        + "shadows of the passage.\n");
    add_item( ({ "shadows", "stairs", "stair", "narrow steps", "steps", }),
        "Barely visible in the shadows to the south, narrow steps "
        + "wind upwards.\n");
    add_item( ({ "wet floor", "floor" }), "The polished floor glistens "
        + "with moisture from the waterfall.\n");
    add_item( ({ "fine rain", "rain", "mist", "mists", "moisture" }),
        "Moisture from the waterfall fills the air with a fine rain "
        + "and gleams on the polished surface of the floor.\n");
    add_item( ({ "surface", "polished stone", "stone", "rock", }),
        "The stone of the floor is polished and gleaming, but "
        + "the rock walls and roof are rough surfaced and dark.\n");
    add_item( ({ "wall", "walls" }), "The walls appear to be solid rock, "
        + "roughly finished and damp with moisture from the falls.\n");
    add_item( ({ "roof", "ceiling" }), "Dark rock, uneven and rough "
        + "surfaced, stoops close overhead.\n");
    add_item(({"stairs", "stairwell", "steps", "step"}), "Beside the "
        + "waterfall is a small stairwell, carved into the wall of the "
        + "cave. It looks slippery.\n");

    set_drink_from( ({ "waterfall", "window", "veil", "falls" }) );
    reset_room();
}

/*
 * Function name: init
 * Description  : Add verbs for waterfall.
 */
public void
init()
{
    ::init();
    init_member_vote();
    init_drink();
    add_action(do_dive, "dive");
    add_action(do_dive, "enter");
    add_action(do_put, "put");
    add_action(do_put, "hold");
    add_action(do_put, "reach");
    add_action(do_put, "touch");
}

void
reset_room()
{    

    check_member_end_vote();
    if ( !objectp(gMaster) )
    {
        if (gRqStageStored < RQ_LEFT_HOBBITON)
            gMaster = clone_object(RANGERS_NPC + "faramir");
        else
            gMaster = clone_object(RANGERS_NPC + "mablung");
        gMaster->move(TO, 1);
        gMaster->command("emote removes his hood as he enters.");
    }
    return;
}


/*
 * Function name: long_func
 * Description  : VBFC for the room description
 * Returns      : string -- the description
 */
public string
long_func()
{
    string  longtxt = "This wet floor of polished stone is the doorstep "
      + "to a rough-hewn gate of rock opening to the east. A dark "
      + "passage leads away south, while a small stairwell has been "
      + "carved into the stone toward the north. To the west hangs the thin "
      + "veil of a waterfall, so near that its mists fill the air.";

    switch(tod())
    {
        case "night":
            longtxt += " The waterfall is now a dazzling veil of silk "
              + "and pearls and silver thread, melting icicles of "
              + "moonlight.";
            break;

        case "early morning":
            longtxt += " The curtain of water glows yellow with early dawn.";
            break;

        case "evening":
            longtxt += " The level shafts of the setting sun behind "
              + "beat upon it, and the red light breaks into many "
              + "flickering beams of ever-changing colour.";
            break;

        case "morning":
        case "noon":
        case "afternoon":
        default:
            longtxt += " Through the veil of the waterfall daylight enters, "
              + "being twisted by the falling water. It is as if the veil "
              + "were pure magic.";
            break;
    }

    return (longtxt + "\n");
}


/*
 * Function name: exa_window
 * Description  : VBFC for the window desc
 * Returns      : string -- the description
 */
public string
exa_window()
{
    string desc;

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
        default:
            desc = "The thin veil of water glows with a bright light "
              + "now in the daytime.";
        break;
    }

    return (desc + "\n");
}


/*
 * Function name: do_put
 * Description  : handle attempts to put hand in waterfall
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 on success, 0 on failure
 */
public int
do_put(string arg)
{
    string vb = query_verb();
    if (!strlen(arg))
    {
        notify_fail(CAP(vb) + " what where?\n");
        return 0;
    }

    /* They may "reach/put/hold hand/arm .." into the water
     * or they may just touch the water.
     */
    if (vb == "put" || vb == "hold" || vb == "reach")
    {
        if (!parse_command(arg, ({}), "'arm' / 'hand' [out] " + PARSE_STR))
        {
            notify_fail(CAP(vb) + " what where?\n");
            return 0;
        }
    }
    else if (!parse_command(arg, ({}), PARSE_STR))
    {
        notify_fail(CAP(vb) + " what?\n");
        return 0;
    }

    write("You hold your arm out into the falling water. The icy "
        + "water refreshes your weary limb.\n");
    say(QCTNAME(TP) + " holds " + POSSESSIVE(TP) + " arm out into "
        + "the falling water.\n");
    return 1;
}

/*
 * Function name: drink_message
 * Description  : do text for drinking from waterfall
 * Arguments    : string where -- unused
 */
public void
drink_message(string where)
{
    write("You reach out a cupped hand to catch the falling water, "
      + "and drink an icy draught. The water tastes wholesome, and waves "
      + "of relaxation wash through your tired limbs, soothing your "
      + "weariness.\n");
    say(QCTNAME(TP) + " reaches out a cupped hand to catch the falling "
      + "water, and drinks an icy draught. A wave of relaxation seems to "
      + "wash through " + POSSESSIVE(TP) + " tired limbs.\n");
    TP->add_fatigue(10);
}

/*
 * Function name: do_dive
 * Description  : handle attempts to dive into falls
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 on success, 0 on failure
 */
public int
do_dive(string arg)
{
    string dest;
    object tp = this_player();

    if (!strlen(arg) || !parse_command(LOW(arg), ({}), PARSE_STR))
    {
        notify_fail(CAP(query_verb()) + " where?\n");
        return 0;
    }

    if (tp->query_skill(SS_SWIM) < MIN_SWIM_SKILL)
    {
        notify_fail("You advance to the edge of the waterfall, but "
            + "change your mind when the icy waters flow across your face.\n");
        return 0;
    }

    write("You dive into the waterfall.\n");
    SAYBB(" dives into the waterfall.");
    write("You fall through mist-filled air and land with a splash in "
        + "foaming, churning waters.\n");
    tp->move_living("M", (RANGERS_ITH_DIR + "pool"));
    tell_room(ENV(tp), QCNAME(tp) + " plunges through the waterfall "
        +"high above your head and lands in the pool.\n", ({tp}));
    return 1;
}
