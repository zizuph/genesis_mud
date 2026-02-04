
#pragma strict_types

#include "../guild.h";

inherit SOUL_DIR+"soul";
inherit SOUL_DIR+"focus";
inherit SOUL_DIR+"options";
inherit SOUL_DIR+"idea";
inherit SOUL_DIR+"emotes";
inherit SOUL_DIR+"bloodguard";
inherit SOUL_DIR+"help";
inherit SOUL_DIR+"assess";
inherit SOUL_DIR+"vamps";

#include <wa_types.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>
#include <options.h>
#include <files.h>

public void create()
{
    set_help_type(({ "bloodguard", "bg" }));
    read_help_dir(HELP_DIR,"bghelp");
    read_help_dir(HELP_DIR,"help");
}


/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
string
get_soul_id() 
{ 
    return LAY_GUILD_NAME + " Soul"; 
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
int 
query_cmd_soul() 
{ 
    return 1; 
}

mapping
query_cmdlist()
{
    return ([
      /* Command name : Function name */
                //Block removed until Knights have playtested it
                //"block"      : "do_ability",
                "stop"	     : "do_stop",
                "bgblood"    : "vblood",
                "bgbreathe"  : "vbreathe",
                "bgbrush"    : "vbrush",
                "bgcaress"   : "vcaress",
                "bgchuckle"  : "vchuckle",
                "bgclench"   : "vclench",      
                "bgconsider" : "vconsider",      
                "bgfang"     : "vfang",
                "bgfocus"    : "focus",
                "bgglower"   : "vglower",
                "bggrin"     : "vgrin",
                "bghiss"     : "vhiss",
                "bghug"      : "vhug",
                "bgidea"     : "videa",
                "bgkiss"     : "vkiss",
                "bglick"     : "vlick",
                "bglist"     : "vamps",
                "bglong"     : "vlong",
                "bglook"     : "vlook",
                "bgnarrow"   : "vnarrow",
                "bgnod"      : "vnod",
                "bgoffer"    : "offer",
                "bgoptions"  : "voptions",
                "bgrevere"   : "vrevere",
                "bgroar"     : "vroar",
                "bgsavage"   : "do_ability",
                "bgscratch"  : "vscratch",
                "bgscream"   : "vscream",
                "bgsmile"    : "vsmile",
                "bgsmirk"    : "vsmirk",
                "bgth"       : "thirst",
                "bgthirst"   : "thirst",
                "bgthroat"   : "vthroat",
                "bgturn"     : "vturn",
                "bgyawn"     : "vyawn",
    ]) + help_cmdlist();
}

public mapping
query_ability_map()
{
    return ([
    "block"       : CORELIB_DIR+"std/block",
    "bgsavage"    : ABILITY_DIR+"bite",
     ]);
}



string *
parse_adverb_with_space(string str, string def_adv, int trail)
{
    string *adv = ::parse_adverb_with_space(str, def_adv, trail);

    if (adv[1] == " ")
    {
        adv[1] = "";
    }

    return adv;
}
