/*
 * /d/Gondor/guilds/rangers/soul/rangers_soul.c
 *
 * The Ranger Guild soul
 *
 * Description of included files and their contents
 * can be found in /d/Gondor/common/guild1/info/FILES
 *
 * Original Rangers coded by Elessar
 * Recode by Gwyneth and Alto 2001-2002
 *
 * Modification log:
 *
 */
inherit "/cmd/std/command_driver";
inherit "/d/Genesis/lib/help.c";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <std.h>
#include <stdproperties.h>
#include <tasks.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "../rangers.h"

#include "admin.c"     // Council and general administration
#include "brawl.c"     // The Ranger brawl special
#include "consider.c"  // Ability to assess the alignment of others
#include "diagnose.c"  // Ability to diagnose poisons
#include "emotes.c"    // General Ranger emotes, including rlist, rintro
#include "forage.c"    // Ability to forage for food
#include "gather.c"    // Ability to gather firewood
#include "grsay.c"     // Ability to communicate with hand signals
#include "guard.c"     // Ability to guard a campfire
#include "mark.c"      // Ability to leave a secret mark
//#include "mentor.c"    // Ability to mentor an apprentice
#include "obscure.c"   // Ability to wipe away the tracks in a room
#include "rconfuse.c"  // Ability to make tracks appear different
#include "rhear.c"     // Ability to hear into a different room
#include "rintro.c"    // Ability to modify the Ranger title/introduction
#include "rknown.c"    // Ability to be visible or not in rlist to apprent.
#include "rlist.c"     // Ability to list active Rangers
#include "rtitles.c"   // Ability to list the Ranger titles
#include "sing.c"      // Ability to sing various Ranger songs
#include "stealth.c"   // The part of stealth held in the soul

public void
create()
{
    /* The help setup for the council commands can be found in
       obj/councilkey.c due to conflicts with two different
       helps in the same file. */

    /* This sets up the help commands and directory. */
    set_help_type(({ "ranger", "rangers" }));
    read_help_dir(RANGERS_HELP);
    FIX_EUID;
}

/*
 * Function name: get_soul_id
 * Description  : Give a name for this soul
 * Returns      : string - the soul's id
 */
public string
get_soul_id()
{
    return "ranger";
}

/*
 * Function name: query_cmd_soul
 * Description  : Identify this as a valid cmdsoul
 * Returns      : 1 always
 */
public int
query_cmd_soul()
{
    return 1;
}

/*
 * Function name: query_cmdlist
 * Description  : Get the commands available on this soul and their
 *                corresponding function names.
 * Returns      : mapping - a mapping that maps command names to
 *                function names
 */
public mapping
query_cmdlist()
{
    /* PLEASE keep these in alphabetical order !! */

    return ([ 
              /* Admin commands */
              "approve"    : "approve",
              "ban"        : "banish",
              "banish"     : "banish",
              "demote"     : "demote",
              "entrust"    : "entrust",
              "expel"      : "expel",
              "notorious"  : "notorious",
              "outlaw"     : "outlaw",
              "passage"    : "passage",
              "pardon"     : "pardon",
              "promote"    : "promote",
              "punish"     : "punish",
              "restrict"   : "restrict",
              "reward"     : "reward",
              "unban"      : "unbanish",
              "unbanish"   : "unbanish",
              "unexpel"    : "unexpel",
              "unpunish"   : "unpunish",
              /* End admin commands */
              "blind"      : "brawl",
              "brawl"      : "brawl",
              "disarm"     : "brawl",
              "grlist"     : "list_active_rangers",
              "knee"       : "knee",
              "rangerlist" : "list_active_rangers",
              "rassess"    : "rassess",
              "rbattle"    : "battle",
              "rbearing"   : "rbearing",
              "rbow"       : "rbow",
              "rbrush"     : "rbrush",
              "rburp"      : "rburp",
              "rcheck"     : "rcheck",
              "rcheek"     : "rcheek",
              "rcloak"     : "rcloak",
              "rconfuse"   : "rconfuse",
              "rconsider"  : "consider",
              "rcurtsey"   : "rcurtsey",
              "rdiagnose"  : "diagnose",
              "rdirt"      : "rdirt",
              "rembrace"   : "rembrace",
              "rforage"    : "forage",
              "rgather"    : "gather",
              "rgazefire"  : "rgazefire",
              "rgleam"     : "rgleam",
              "rgrim"      : "rgrim",
              "rgrip"      : "rgrip",
              "rguard"     : "rguard",
              "rhail"      : "hail",
              "rhear"      : "rhear",
              "rhome"      : "rhome",
              "rhush"      : "rhush",
              "rinspect"   : "rinspect",
              "rintro"     : "ranger_intro_type",
              "rkisshand"  : "kisshand",
              "rknee"      : "brawl",
              "rknown"     : "rknown",
              "rlaugh"     : "rlaugh",
              "rlist"      : "list_active_rangers",
              "rlisten"    : "rlisten",
              "rmark"      : "mark",
              "rnod"       : "rnod",
              "robscure"   : "obscure",
              "roffer"     : "offer",
              "rparley"    : "rparley",
              "rpatience"  : "rpatience",
              "rpick"      : "rpick",
              "rpoke"      : "rpoke",
              "rpray"      : "rpray",
              "rrecall"    : "rrecall",
              "rrelief"    : "rrelief",
              "rrest"      : "rrest",
              "rrub"       : "rrub",
              "rsignal"    : "use_hand_signal",
              "rsing"      : "sing",
              "rsit"       : "rsit",
              "rstealth"   : "stealth_mode",
              "rstone"     : "rstone",
              "rstop"      : "stop_brawl",
              "rstudy"     : "rstudy",
              "rsuspicious" : "suspicious",
              "rtear"      : "rtear",
              "rtitles"    : "rtitles",
              "rtrack"     : "rtrack",
              "rtrip"      : "brawl",
              "rtroubled"  : "rtroubled",
              "runcloak"   : "runcloak",
              "runguard"   : "runguard",
              "rwait"      : "rwait",
              "rwarm"      : "rwarm",
              "rwarmback"  : "rwarmback",
              "rweary"     : "rweary",
              "rwipe"      : "rwipe",
              "trip"       : "brawl",
            ]) + help_cmdlist();
}

