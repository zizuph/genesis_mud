/*
 * Vampire Guild soul
 *
 * Modifications:
 *   - removed swallow command since constrict has been removed.
 *       Petros, July 2009
 *   - added vmorning command to allow Vampires to determine the
 *     coming dawn.
 *       Petros, November 2009
 */
 
#pragma strict_types

#include "../guild.h";

inherit SOUL_DIR+"soul";
inherit SOUL_DIR+"sniff";
inherit SOUL_DIR+"focus";
inherit SOUL_DIR+"vsay";
inherit SOUL_DIR+"options";
inherit SOUL_DIR+"sun";
inherit SOUL_DIR+"vamps";
inherit SOUL_DIR+"idea";
inherit SOUL_DIR+"emotes";
inherit SOUL_DIR+"desiccate";
inherit SOUL_DIR+"drink";
inherit SOUL_DIR+"bloodguard";
inherit SOUL_DIR+"help";
inherit SOUL_DIR+"vision";
inherit SOUL_DIR+"embrace";
inherit SOUL_DIR+"vleave";
inherit SOUL_DIR+"incognito";
inherit SOUL_DIR+"compel";
inherit SOUL_DIR+"assess";
inherit SOUL_DIR+"sense";
inherit SOUL_DIR+"cling";

#include <wa_types.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>
#include <options.h>
#include <files.h>

public void create()
{
    set_help_type(({ "vampyr", "vampire" }));
    read_help_dir(HELP_DIR);
    read_help_dir(HELP_DIR,"vhelp");
}



/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
string
get_soul_id() 
{ 
    return OCC_GUILD_NAME + " Soul"; 
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
                "burp"       : "burp",
                "fart"       : "fart",
                "stop"	     : "do_stop",
                "valign"     : "valign",
                "vaccept"    : "accept",
                "vamplist"   : "vamps",
                "vamps"      : "vamps",
                "vassess"    : "assess",
                "vbeam"      : "vbeam",
                "vblink"     : "vblink",
                "vblood"     : "vblood",
                "vbow"       : "vbow",
                "vbreathe"   : "vbreathe",
                "vbrush"     : "vbrush",
                "vburn"      : "vburn",
                "vcaress"    : "vcaress",
                "vcelerity"  : "do_ability",
                "vchuckle"   : "vchuckle",
                "vclench"    : "vclench",  
                "vcling"     : "cling",  
                "vclose"     : "vclose",
                "vcompel"    : "compel",    
                "vconsider"  : "vconsider",
                "vcurtsey"   : "vcurtsey",      
                "vdance"     : "vdance",
                "vdash"      : "do_ability",
                "vdesiccate" : "desiccate",
                "vdelve"     : "do_ability",
                "vdisguise"  : "disguise",
                "vdismiss"   : "vdismiss",
                "vdistant"   : "vdistant",
                "vdoll"      : "do_ability",
                "vdominate"  : "do_ability",
                "vdrink"     : "drink",
                "vecstacy"   : "vecstacy",
                "vembrace"   : "embrace",
                "ventrance"  : "ventrance",
                "vfang"      : "vfang",
                "vfocus"     : "focus",
                "vflicker"   : "do_ability",
                "vflurry"    : "do_ability",
                "vfly"       : "do_ability",
                "vfrown"     : "vfrown",
                "vgaze"      : "vgaze",
                "vglance"    : "vglance",
                "vglare"     : "vglare",
                "vglower"    : "vglower",
                "vgrin"      : "vgrin",
                "vgust"      : "vgust",
                "vhiss"      : "vhiss",
                "vhug"       : "vhug",
                "videa"      : "videa",
                "vincognito" : "do_ability",
                "vkiss"      : "vkiss",
                "vlaugh"     : "vlaugh",
                "vleave"     : "vleave",
                "vlick"      : "vlick",
                "vlong"      : "vlong",
                "vlook"      : "vlook",
                "vmeld"      : "do_ability",
                "vobfuscate" : "do_ability",
                "vmelancholy": "vmelancholy",
                "vmesmerize" : "do_ability",
                "vmorning"   : "detect_dawn",
                "vnarrow"    : "vnarrow",
                "vnod"       : "vnod",
                "voffer"     : "offer",
                "voptions"   : "voptions",
                "vpast"      : "vpast",
                "vpensive"   : "vpensive",
                "vpierce"    : "vpierce",
                "vpity"      : "vpity",
                "vpower"     : "vpower",
                "vrecall"    : "vrecall",
                "vreject"    : "reject",
                "vrelease"   : "vrelease",
                "vrevel"     : "vrevel",
                "vrevere"    : "vrevere",
                "vrise"      : "vrise",
                "vroar"      : "vroar",
                "vsadness"   : "vsadness",
                "vsavage"      : "do_ability",
                "vsay"       : "vsay",
                "vscratch"   : "vscratch",
                "vscream"    : "vscream",
                "vscry"      : "do_ability",
                "vsense"     : "sense",
                "vshadow"    : "vshadow",
                "vshine"     : "vshine",
                "vsight"     : "do_ability",
                "vsmile"     : "vsmile",
                "vsmirk"     : "vsmirk",
                "vsniff"     : "sniff",
                "vstudy"     : "study",
                "vsummon"    : "do_ability",
                "vsun"       : "sun",
                "vsweat"     : "vsweat",
                "vtaste"     : "vtaste",
                "vtear"      : "vtear",
                "vtelepath"  : "do_ability",
                "vthoughtful": "vthoughtful",
                "vtouched"   : "vtouched",
                "vth"        : "thirst",
                "vthirst"    : "thirst",
                "vthroat"    : "vthroat",
                "vtpath"     : "do_ability",
                "vtrace"     : "vtrace",
                "vturn"      : "vturn",
                "vvision"    : "vision",
                "vyawn"      : "vyawn",
      
    ]) + help_cmdlist();
}


public mapping
query_ability_map()
{
    return ([
    "vcelerity"  : SPELL_DIR+"celerity",
    "vdash"      : SPELL_DIR+"dash",
    "vdoll"      : SPELL_DIR+"doll",
    "vdelve"     : SPELL_DIR+"delve",
    "vdominate"  : SPELL_DIR+"dominate",
    "vflicker"   : SPELL_DIR+"flicker",
    "vfly"       : SPELL_DIR+"fly",
    "vflurry"    : ABILITY_DIR+"flurry",
    "vincognito" : SPELL_DIR+"incognito",
    "vmeld"      : ABILITY_DIR+"meld",
    "vmesmerize" : SPELL_DIR+"mesmerize",
    "vobfuscate" : SPELL_DIR+"obfuscate",
    "vsavage"    : ABILITY_DIR+"bite",
    "vsight"     : SPELL_DIR+"sight",
    "vscry"      : SPELL_DIR+"scry",
    "vsummon"    : SPELL_DIR+"summon",
    "vtelepath"  : SPELL_DIR+"telepath",
    "vtpath"     : SPELL_DIR+"telepath",
     ]);
}



int do_stop(string arg)
{
    if (::do_stop(arg))
    {
        return 1;
    }
    
    if (!stringp(arg))
    {
        return 0;
    }

    switch (lower_case(arg))
    {
        case "cling":
            return stop_cling(TP);
            break;
        case "drain":
        case "drink":
        case "vdrink":
            if (TP->query_vamp_drain())
            {
                TP->release_vamp_drainee();
                return 1;       
            }
            break;            
        case "dominate":
            if (!sizeof(TP->query_dominated()))
            {
                return 0;
            }
            foreach (object shadow : TP->query_dominated())
            {
                shadow->dispel_spell_effect(0);
            }
            return 1;
    }
    return 0;
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
