/*
 * The soul of the Morgul mages.
 * /d/Gondor/common/guild2/morgul_soul.c
 *
 * Created: Soermo
 *
 * Modification log:
 * 06-jan-1994: recoded by Olorin
 *              added mtitles, moved emotes to lib/morgul_emotes.h
 * Dec 1999   : Morbeche
 *              Split rasp and hiss into rasp/mrasp and hiss/mhiss 
 * Feb 2006   : Altrus
 *              Added in the command for 'msay', to speak in the 
 *              dialect of the orc and uruk race guilds
 * Apr 2009   : Eowul
 *              Moved to the new guild directory and cleaned up.
 */
 
#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver.c";

#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <macros.h>
#include <options.h>
#include <stdproperties.h>

#include "morgulmage.h"

#include "soul/support.c"
#include "soul/emotes.c"
#include "soul/emotes_songs.c"
#include "soul/communication.c"
#include "soul/general.c"
#include "soul/nazgul.c"
#include "soul/narusse.c"
#include "soul/horse.c"

public string get_soul_id()
{
    return GUILD_NAME;
}

public int query_cmd_soul()
{
    return 1;
}

void
create()
{
    setuid();
    seteuid( getuid() );
}

public mapping
query_cmdlist()
{
    return ([
        // Emotions
        "approve"    : "approve",
        "aware"      : "aware",
        "battlesong" : "battlesong",
        "chant"      : "recite",
        "damn"       : "damn",
        "exalt"      : "exalt",
        "fog"        : "fog",
        "gaze"       : "gaze",
        "hail"       : "hail",
        "mhail"      : "hail",
        "hgaze"      : "hgaze",
        "leer"       : "leer",
        "loom"       : "loom",
        "marm"       : "marm",
        "mamuse"     : "mamuse",
        "manger"     : "manger",
        "mbeckon"    : "mbeckon",
        "mbrood"     : "mbrood",
        "mcall"      : "mcall",
        "mcurse"     : "curse",
        "mdismiss"   : "mdismiss",
        "minspect"   : "minspect",
        "mgaze"      : "mgaze",
        "mglare"     : "mglare",
        "mgrab"      : "mgrab",
        "mhiss"      : "hiss_emote",
        "mhood"      : "mhood",
        "mlaugh"     : "mlaugh",
        "mleer"      : "leer",
        "mlook"      : "mlook",
        "mnarrow"    : "mnarrow",
        "mordor"     : "mordor",
        "mrasp"      : "rasp_emote",
        "mrecite"    : "recite",
        "mremember"  : "mage_remember",
        "mreveal"    : "mreveal",
        "mscoff"     : "mage_scoff",
        "msmile"     : "mage_smile",
        "mslap"      : "mslap",
        "msniff"     : "do_msniff",
        "msneer"     : "msneer",
        "msummon"    : "msummon",
        "mturn"      : "mturn",
        "mwail"      : "mwail",
        "tempt"      : "tempt",
        "torture"    : "torture",
        "withdraw"   : "withdraw",
        "wrath"      : "wrath",

        // General commands
        "designate"  : "designate_ingredient",
        "help"       : "help",
        "mhelp"      : "help",
        "magelist"   : "list_active_mages",
        "mlist"      : "list_active_mages",
        "mtitles"    : "morgul_titles",
        "list"       : "list_spells",
        "moptions"   : "moptions",
        
        // Nazgul commands
        "expel"      : "nazgul_expel",
        "mopine"     : "mopine",
        "punish"     : "nazgul_punish",
        "regard"     : "regard",
        "reward"     : "nazgul_reward",

        // Communications
        "hiss"       : "mhiss",        
        "mssay"      : "slave_speak",
	    "ms"         : "slave_speak",
        "rasp"       : "rasp_say",        
        "shriek"     : "shriek",
        
        // Narusse commands
        "ignite"     : "narusse_ignite",
        "nignite"    : "narusse_ignite",
        "extinguish" : "narusse_extinguish",
        "nextinguish" : "narusse_extinguish",
        "nthreaten"  : "narusse_threaten",
        
        // Horse commands
        "msteed"    : "msteed"
    ]);
}
