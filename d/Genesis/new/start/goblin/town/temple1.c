/*
 * File         : /d/Genesis/new/start/goblin/town/temple1.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : September 14, 1999
 * Modifications: 
 * Purpose      : Temple of Xi Voch - West Wing
 * Related Files: 
 * Comments     : 
 * TODO         : 
 */

inherit "/std/room.c";
inherit "/lib/guild_support";

#include <composite.h>
#include <macros.h>
#include <language.h>
#include <ss_types.h>
#include <state_desc.h>
#include <std.h>
#include <stdproperties.h>	

#define GS_NUM_GUILDS       3
#define GS_GUILD_EXTENSIONS ({ "race", "occ", "lay" })
#define GS_GUILD_FULL_NAMES ({ "racial", "occupational", "layman" })
#define GS_ADVANCE_DESCS    ({ "very far from", "far from", "halfway to", \
    "close to", "very close to" })
#define GS_SIZEOF_ADVANCE_DESCS   5
#define GS_POINTS_PER_STAT_LEVEL 17
#define GS_STAT_LEVELS            8
#define GS_APPROACH_EPIC        119  /* == ((8 - 1) * 17) */

int rack_occupied = 0;

/* Prototypes */
int gs_meditate(string str);
void gs_hook_start_meditate();
int gs_rise();
void gs_hook_rise();
int gs_catch_all(string arg);

/*
 * Function name: create_room
 * Description  : It creates the room object.
 * Arguments    :
 * Returns      : 
 */
public void 
create_room()
{
    set_short("You are in the west wing of the Temple of Xi Voch");

    set_long("You are in the west wing of the Temple of Xi Voch.\n" +
    "A shrine to Mother Earth rises before you in the form of an " +
    "elaborate stone sculpture. At the base is a gruesome looking " +
    "meditation rack. By using <meditate>, you can redefine your " +
    "personal priorities. A passage leads out of the Temple to the " +
    "south while a large chamber lies to the east.\n");

    add_item(({"shrine", "stone shrine", "shrine to mother earth",
    "sculpture", "stone sculpture"}),
    "The unique sculpture depicts a goblin growing out of the rock. " +
    "From the look on his face, it appears to be quite a painful " +
    "process.\n");

    add_item(({"rack", "meditation rack"}),
    "Carved from solid limestone, the rack looks very, very uncomfortable. " +
    "There are two metal wrist cuffs attached to the rack. You can't imagine " +
    "what they might be for.\n");

    add_exit("temple2", "east");
    add_exit("cavern_d2", "south");

    set_noshow_obvious(1);
}

/*
 * Function name: gs_meditate
 * Description  : Player wants to meditate.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
gs_meditate(string str)
{
    if (this_player()->query_prop(LIVE_I_MEDITATES))
    {
        return gs_hook_already_meditate();
    }

    if (rack_occupied == 0)
    {
    object tgive;
    int    index;
    int    stat;
    int    level;
    int    residue;
    int   *orig_prefs;

    rack_occupied = 1;
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, " is on the rack");

    this_player()->add_prop(LIVE_I_MEDITATES, 1);

    this_player()->reveal_me(1);

    gs_hook_start_meditate();
    write("Here you may also <restrict> yourself from playing.\n\n");

    index = -1;
    while(++index < SS_NO_EXP_STATS)
    {
        stat = this_player()->query_stat(index);
        if (stat >= 160)
        {
            write("You have the " + SD_LONG_STAT_DESC[index] +
                " of an immortal.\n");
            continue;
        }

        if (stat >= 136)
        {
            write("You have reached epic " + SD_LONG_STAT_DESC[index] +
                ".\n");
            continue;
        }

        level = (stat / GS_POINTS_PER_STAT_LEVEL);
        residue = (((stat - (level * GS_POINTS_PER_STAT_LEVEL)) *
            GS_SIZEOF_ADVANCE_DESCS) / GS_POINTS_PER_STAT_LEVEL);

        tgive = this_player()->find_stat_describer(index);
        if (objectp(tgive))
        {
            write("You are " + GS_ADVANCE_DESCS[residue] + " advancing to " +
                ((stat >= GS_APPROACH_EPIC) ?
                ("epic " + SD_LONG_STAT_DESC[index]) :
                tgive->query_stat_string(index, -(level + 1))) + ".\n");
        }
        else
        {
            write("You are " + GS_ADVANCE_DESCS[residue] + " advancing.\n");
        }
    }

    write("Your learning preferences are now as follows.\n");
    write("   STR   DEX   CON   INT   WIS   DIS   Total\n");
    orig_prefs = this_player()->query_learn_pref(-1);
    index = -1;
    level = 0;
    while(++index < SS_NO_EXP_STATS)
    {
        level += orig_prefs[index];
        write(sprintf("   %3d", orig_prefs[index]));
    }
    write(sprintf("   = %3d\n", level));

    add_action(gs_catch_all, "", 1);
    return 1;
    }
    else
    {
        write("The rack is already occupied.\n");
        say(QCTNAME(this_player()) + " tries to lay down on the rack but fails.\n");
        return 1;
    }
}

/*
 * Function name: gs_hook_start_meditate
 * Description  : This hook is called when player starts to meditate.
 */
void
gs_hook_start_meditate()
{
    write("Laying down on the hard, stone rack, you stretch out your arms to " +
        "either side and slip your hands through the metal cuffs. You block " +
        "off your senses and concentrate solely upon your own mind. Suddenly, " +
        "you are blinded by a harsh, yellow light. You feel your skin baking " +
        "under a smothering heat. At one with the suffering of the goblin " +
        "ancestors, you find a gentle peace washing over you. You find " +
        "yourself able to <set> your preferences as you desire. Simply <rise> " +
        "when you are done meditating. You estimate your stats and the progress " +
        "you are making toward improving them.\n");
    say(QCTNAME(this_player()) + " lays down on the stone rack and slips into a " +
        "deep trance.\n");
}

/*
 * Function name: gs_rise
 * Description  : Player rises from meditation.
 * Returns      : int 1 - always.
 */
int
gs_rise()
{
    rack_occupied = 0;
    gs_hook_rise();
    this_player()->remove_prop(LIVE_I_MEDITATES);
    return 1;
}

/*
 * Function name: gs_hook_rise
 * Description  : This hook is called when player rises from the meditation.
 */
void
gs_hook_rise()
{
    write("With a startling suddenness, you are snapped back into consciousness. " +
        "You exhale, feeling strangely refreshed as you get up and leave the rack.\n");
    say(QCTNAME(this_player()) + " rises from the meditation rack.\n");
}

/*
 * Function name: gs_catch_all
 * Description  : Catch all commands the player makes while meditating.
 * Returns      : int 1/0 - success/failure.
 */
int
gs_catch_all(string arg)
{
    if (!this_player()->query_prop(LIVE_I_MEDITATES))
    {
        return 0;
    }

    switch(query_verb())
    {
    case "meditate":
        return gs_meditate("");

    case "set":
        set_prefs();
        return 1;

    case "rise":
        this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
        gs_rise();
        return 1;

    case "restrict":
        gs_restrict(arg);
        return 1;

    case "quit":
        rack_occupied = 0;
        return 0;

    case "help":
    case "stats":
    case "save":
    case "drop": /* For those that quit from meditation */
    case "commune":
    case "reply":
    case "bug":
    case "typo":
    case "idea":
    case "praise":
    case "sysbug":
    case "systypo":
    case "syspraise":
    case "sysidea":
        return 0;

    default:
        return gs_hook_catch_error(arg);
    }
}

void
init()
{
    ::init();

    add_action(gs_meditate, "meditate");
}
