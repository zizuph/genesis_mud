/*
 * soul.c
 *
 * The soul of the Ancient Order of the Dragon 
 *
 * Modification Log:
 *     Cirion, April 14th, 1998
 *     Lilith, Jan 29th, 1999
 */
#pragma save_binary
#pragma strict_types

#include "defs.h"
#include <adverbs.h>
#include <language.h>

inherit "/cmd/std/command_driver";
inherit MONKLIB;

#define SOULDESC(x)  TP->add_prop(LIVE_S_SOULEXTRA, (x))

inherit MONK_LIB + "help";

void reset_euid();

/*
 * Includes for the command sets. These are included from a
 * separate file (rather than inherited) because they utilize
 * functions for /std/command/command_driver.
 */
#include "mappraise.h"
#include "idea.h"
#include "plexus.h"
#include "strike.h"

#include "emotes_a_h.h"
#include "emotes_i_p.h"
#include "emotes_q_z.h"
#include "form_routine.h"
#include "council.h"


string 
get_soul_id()
{
   return MONK_OCC_NAME;
}

int
query_cmd_soul() 
{
    return 1; 
}

mapping
query_cmdlist()
{
    setuid();
    seteuid(getuid());
 
    return ([
                "bless"    : "aod_bless", 
                "bow"      : "aod_bow",
                "center"   : "aod_center", 
                "centre"   : "aod_center",
                "chant"    : "aod_chant", 
                "chastise" : "aod_chastise", 
                "control"  : "aod_control", 
                "dedicate" : "aod_dedicate",
                "ded"      : "aod_dedicate",
                "defend"   : "aod_defend",
                "display"  : "aod_display", 
                "drop"     : "aod_drop",
                "fist"     : "aod_fist",
                "form"     : "aod_form",
                "forms"    : "aod_form", 
                "formstop" : "aod_stop_form",
                "gaze"     : "aod_gaze",
                "growl"    : "aod_growl",
                "hand"     : "aod_slice",
                "inspired" : "aod_inspired", 
                "kiai"     : "aod_kiai", 
                "kill"     : "aod_kill",
                "knuckles" : "aod_knuckles", 
                "nurse"    : "aod_knuckles",
                "knuck"    : "aod_knuckles", 
                "look"     : "aod_look",
                "pray"     : "aod_pray",
                "pity"     : "aod_pity",
                "refuse"   : "aod_refuse",
                "relax"    : "aod_relax",
                "roar"     : "aod_roar",
                "shun"     : "aod_shun", 
                "sketch"   : "aod_sketch",
                "slice"    : "aod_slice", 
                "stop"     : "aod_stop_form", 
                "victory"  : "aod_victory",
                "wing"     : "aod_wing", 
                "warn"     : "aod_warn",

                "mappraise" : "mappraise",
                "mfocus"   : "focus", // focus
                "focus"    : "focus", // focus
                "mplexus"  : "plexus", // plexus special attack
                "plexus"   : "plexus", // plexus special attack
                "mstrike"  : "strike", // strike special attack
                "strike"   : "strike", // strike special attack
                "mtoken"   : "mtoken", // council command
                "mtitle"   : "mtitle", // council command

                "aod"      : "aod", // prefix command to allow execution of conflicting guild commands
           ]) + help_cmdlist();
}

void
reset_euid()
{
    setuid();
    seteuid(getuid(this_object()));
}

void
create()
{
    reset_euid();
    set_help_type(({ "monk", "monks", "dragon", "order" }));
}


int
focus(string str)
{
    // just call it in the shadow, which handles everyting.
    return this_player()->m_start_focus();
}


/*
 * Function name: aod
 * Description  : By prefixing "aod" to the command, players can always execute
 *                the Dragon Order  command, even if the name comflicts with that
 *                of another guild. Copied verbatum from Mercade's Rockfriend soul.
 * Arguments    : string str - the command line argument.
 * Returns      : int 1/0 - success/failure.
 */
int
aod(string str)
{
    string *words;
 
    if (!strlen(str))
    {
        notify_fail("Perform which Dragon Order command? " +
            "Syntax: aod <command> [<arguments>]\n");
        return 0;
    }
 
    words = explode(str, " ");
    if (!stringp(cmdlist[words[0]]))
    {
        notify_fail("The command " + words[0] +
            " is not a known Dragon Order command.\n");
        return 0;
    }
 
    str = ((sizeof(words) > 1) ? implode(words[1..], " ") : "");
    return call_other(this_object(), cmdlist[words[0]], str);
}


