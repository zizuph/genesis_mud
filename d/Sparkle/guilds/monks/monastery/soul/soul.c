/*******************************************************************\
| SOUL.C                                                            |
\*******************************************************************/

/*
 * 07/06/03 Arandir     Added the mdisdain and mhumble emotes
 * 07/05/22 Arandir     Depose changed to impeach
 * 07/05/19 Arandir     Added the mdepose command
 * 06/08/16 Arandir     Changed mfocus to be an emote
 * 03/12/21 Arandir     Added the sign speech
 * 03/09/20 Arandir     Added the mbicker, mpoke, mhonor and mrespect
 *                      emotes suggested by Ekkehard
 * 03/09/14 Arandir     Added the mbreathe, mregret, mstep, mscout
 *                      and mwipe emotes suggested by Ekkehard
 * 03/09/10 Arandir     Added support for recalling telioys
 * 03/09/09 Arandir     Added the councillist and elderlist commands
 * 03/07/13 Arandir     Removed the idiotic nested help system
 * 03/06/24 Arandir     Minor changes to compile in the new area
 * 02/05/01 Arandir	Ported to new area without rewrite
 * 99/01/29 Lilith	Miscelaneous additions
 * 98/04/14 Cirion	Created
 *
 */

#include <files.h>
#include <tasks.h>
#include <macros.h>
#include <adverbs.h>
#include <cmdparse.h>
#include <language.h>
#include <ss_types.h>
#include <wa_types.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include </std/combat/combat.h>

#include "../defs.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/lib/help";

inherit DG_OBJ_LIBS;
inherit DG_TEXT_LIBS;
inherit M_TOKEN_LIBS;
inherit M_PLAYER_LIBS;
inherit M_VOTING_LIBS;

//-------------------------------------------------------------------

#define M_SOULDESC(x)   this_player ()->add_prop (LIVE_S_SOULEXTRA, (x))
//-------------------------------------------------------------------

/*******************************************************************\
| Help related functions                                            |
\*******************************************************************/

void m_help_clear ()
{
  help_map = ([ ]);
}


/*
 * Function name : _help
 * Description   : This overrides the standard help command to check
 *                 for council membership.
 *
 */
int _help (string sArgs)
{
  object oHim = this_player ();
  string sHelp;

  // Set the sortiment of help files depending on the guild position.

  m_help_clear ();
  read_help_dir (M_HELP_MONK);
  if (m_is_council_member (oHim))
  {
    read_help_dir (M_HELP_ELDER);
    read_help_dir (M_HELP_COUNCIL);
  }
  else if (m_is_elder_member (oHim))
  {
    read_help_dir (M_HELP_ELDER);
  }

  // Now just do the help command ...

  return (::_help (sArgs));
}
//-------------------------------------------------------------------

#include "soul_idea.h"
#include "soul_forms.h"
#include "soul_general.h"
#include "soul_signing.h"
#include "soul_appraise.h"

#include "soul_emotes_a_h.h"
#include "soul_emotes_i_p.h"
#include "soul_emotes_q_z.h"

#include "soul_plexus.h"
#include "soul_strike.h"

#include "soul_elder.h"
#include "soul_council.h"

//-------------------------------------------------------------------

string get_soul_id ()
{
  return (M_NAME_LONG);
}


int query_cmd_soul ()
{
  return (TRUE);
}

/*
 * We wrap do_ability in do_plexus to check for OCC membership
 */
int do_plexus(string sArgs)
{
    object oWho = this_player();
    if (query_interactive(oWho) && !m_is_monk (oWho, SS_OCCUP))
    {
        return 0;
    }
    return do_ability(sArgs);
}

/*
 * We wrap do_ability in do_strike to check for OCC membership
 */
int do_strike(string sArgs)
{
    return do_ability(sArgs);
}

public mapping
query_ability_map()
{
    object oWho = this_player();
    if (!query_interactive(oWho) || m_is_monk(oWho, SS_OCCUP))
    {
        return ([
            "mstrike" : M_PATH_SPECIALS + "/strike_occ",
            "mplexus" : M_PATH_SPECIALS + "/plexus",
        ]);
    }
    else
    {
        return ([
            "mstrike" : M_PATH_SPECIALS + "/strike_lay"
        ]);
    }
}

mapping query_cmdlist ()
{
  DG_FIXUID;

  return (([ "mk"           : "m_mk",

             "mappraise"    : "m_action_appraise",

             "mbicker"      : "m_action_bicker",
             "mbless"       : "m_action_bless",
             "mbow"         : "m_action_bow",
             "mbreathe"     : "m_action_breathe",

             "mcenter"      : "m_action_center",
             "mchant"       : "m_action_chant",
             "mchastise"    : "m_action_chastise",
             "mcontrol"     : "m_action_control",

             "mdedicate"    : "m_action_dedicate",
             "mdefend"      : "m_action_defend",
             "mdisdain"     : "m_action_disdain",
             "mdisplay"     : "m_action_display",
             "mdrop"        : "m_action_drop",

             "mfist"        : "m_action_fist",
             "mfocus"       : "m_action_focus",
             "mform"        : "m_action_form",

             "mgaze"        : "m_action_gaze",
             "mgreet"       : "m_action_greet",
             "mgrowl"       : "m_action_growl",

             "mhand"        : "m_action_hand",
             "mhonor"       : "m_action_honor",
             "mhumble"      : "m_action_humble",

             "minspired"    : "m_action_inspired",
             "mkarma"       : "m_action_karma",
                
             "mkiai"        : "m_action_kiai",
             "mkill"        : "m_action_kill",
             "mkin"         : "m_action_kin",
             "mknuckles"    : "m_action_knuckles",

             "mlook"        : "m_action_look",

             "mpray"        : "m_action_pray",
             "mpity"        : "m_action_pity",
             "mpoke"        : "m_action_poke",

             "mrecall"      : "m_action_recall",
             "mrefuse"      : "m_action_refuse",
             "mregret"      : "m_action_regret",
             "mrelax"       : "m_action_relax",
             "mrespect"     : "m_action_respect",
             "mroar"        : "m_action_roar",

             "mscout"       : "m_action_scout",
             "mshun"        : "m_action_shun",
             "msign"        : "m_action_sign",
             "msignal"      : "m_action_signal",
             "msketch"      : "m_action_sketch",
             "mslice"       : "m_action_slice",
             "mstep"        : "m_action_step",
             "mstop"        : "m_action_stop",

             "mvictory"     : "m_action_victory",

             "mwarn"        : "m_action_warn",
             "mwing"        : "m_action_wing",
             "mwipe"        : "m_action_wipe",

             "mplexus"      : "do_plexus",
             "mstrike"      : "do_strike",

             "mcouncillist" : "m_action_councillist",
             "melderlist"   : "m_action_elderlist",
             "mimpeach"     : "m_action_impeach",

             "melderadd"    : "m_action_elderadd",
             "melderremove" : "m_action_elderremove",
             "mpunish"      : "m_action_punish",
             "mpunishlist"  : "m_action_punishlist",
             "mreprieve"    : "m_action_reprieve",
             "mresign"      : "m_action_resign",
             "mtitle"       : "m_action_title",
             "mtoken"       : "m_action_token",
             "mtokenadd"    : "m_action_tokenadd",
             "mtokenremove" : "m_action_tokenremove",

             "mbug"         : "m_action_bug",
             "midea"        : "m_action_idea",
             "mtypo"        : "m_action_typo"

           ]) + help_cmdlist ());
}

//-------------------------------------------------------------------

void create ()
{
  DG_FIXUID;

  set_help_type (({ "monk", "monks" }));
}

//-------------------------------------------------------------------

/*
 * Function name : m_mk
 * Description   : By prefixing "mk" to all commands, monks can
 *                 always execute the guild commands, even when
 *                 their name collides with those from other
 *                 guilds.
 *
 */

int m_mk (string sArgs)
{
  string sCommand;
  string *asWords;

  notify_fail ("Syntax: mk <command> [<arguments>]\n");

  if (!strlen (sArgs)) return (FALSE);

  asWords = explode (sArgs, " ");
  sCommand = implode (asWords [1 ..], " ");

  switch (asWords [0])
  {
    case "appraise"    : return (m_action_appraise (sCommand));

    case "bicker"      : return (m_action_bicker (sCommand));
    case "bless"       : return (m_action_bless (sCommand));
    case "bow"         : return (m_action_bow (sCommand));
    case "breathe"     : return (m_action_breathe (sCommand));

    case "center"      : return (m_action_center (sCommand));
    case "chant"       : return (m_action_chant (sCommand));
    case "chastise"    : return (m_action_chastise (sCommand));
    case "control"     : return (m_action_control (sCommand));

    case "dedicate"    : return (m_action_dedicate (sCommand));
    case "defend"      : return (m_action_defend (sCommand));
    case "disdain"     : return (m_action_disdain (sCommand));
    case "display"     : return (m_action_display (sCommand));
    case "drop"        : return (m_action_drop (sCommand));

    case "fist"        : return (m_action_fist (sCommand));
    case "focus"       : return (m_action_focus (sCommand));
    case "form"        : return (m_action_form (sCommand));

    case "gaze"        : return (m_action_gaze (sCommand));
    case "greet"       : return (m_action_greet (sCommand));
    case "growl"       : return (m_action_growl (sCommand));

    case "hand"        : return (m_action_hand (sCommand));
    case "honor"       : return (m_action_honor (sCommand));
    case "humble"      : return (m_action_humble (sCommand));

    case "inspired"    : return (m_action_inspired (sCommand));

    case "kiai"        : return (m_action_kiai (sCommand));
    case "kill"        : return (m_action_kill (sCommand));
    case "kin"         : return (m_action_kin (sCommand));
    case "knuckles"    : return (m_action_knuckles (sCommand));

    case "look"        : return (m_action_look (sCommand));

    case "pray"        : return (m_action_pray (sCommand));
    case "pity"        : return (m_action_pity (sCommand));
    case "poke"        : return (m_action_poke (sCommand));

    case "recall"      : return (m_action_recall (sCommand));
    case "refuse"      : return (m_action_refuse (sCommand));
    case "regret"      : return (m_action_regret (sCommand));
    case "relax"       : return (m_action_relax (sCommand));
    case "respect"     : return (m_action_respect (sCommand));
    case "roar"        : return (m_action_roar (sCommand));

    case "scout"       : return (m_action_scout (sCommand));
    case "shun"        : return (m_action_shun (sCommand));
    case "sign"        : return (m_action_sign (sCommand));
    case "signal"      : return (m_action_signal (sCommand));
    case "sketch"      : return (m_action_sketch (sCommand));
    case "slice"       : return (m_action_slice (sCommand));
    case "step"        : return (m_action_step (sCommand));
    case "stop"        : return (m_action_stop (sCommand));

    case "victory"     : return (m_action_victory (sCommand));

    case "warn"        : return (m_action_warn (sCommand));
    case "wing"        : return (m_action_wing (sCommand));
    case "wipe"        : return (m_action_wipe (sCommand));

    case "plexus"      : return (do_plexus (sCommand));
    case "strike"      : return (do_strike (sCommand));

    case "councillist" : return (m_action_councillist (sCommand));
    case "elderlist"   : return (m_action_elderlist (sCommand));
    case "impeach"     : return (m_action_impeach (sCommand));

    case "elderadd"    : return (m_action_elderadd (sCommand));
    case "elderremove" : return (m_action_elderremove (sCommand));
    case "punish"      : return (m_action_punish (sCommand));
    case "punishlist"  : return (m_action_punishlist (sCommand));
    case "reprieve"    : return (m_action_reprieve (sCommand));
    case "resign"      : return (m_action_resign (sCommand));
    case "title"       : return (m_action_title (sCommand));
    case "token"       : return (m_action_token (sCommand));
    case "tokenadd"    : return (m_action_tokenadd (sCommand));
    case "tokenremove" : return (m_action_tokenremove (sCommand));

    case "bug"         : return (m_action_bug (sCommand));
    case "idea"        : return (m_action_idea (sCommand));
    case "typo"        : return (m_action_typo (sCommand));
  }

  return (FALSE);
}

//-------------------------------------------------------------------

