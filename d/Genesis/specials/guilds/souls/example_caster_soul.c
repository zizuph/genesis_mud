/*
 * Example Caster Guild Command Soul
 *
 * This is a sample command soul that a caster should have. It demonstrates
 * how spell objects are added to the soul and can be used.
 *
 * Created by Petros, Februrary 2010
 */

#pragma strict_types

#include <macros.h>

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#define SPELLS_DIR   "/d/Genesis/specials/std/spells/"

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
public string
get_soul_id() 
{ 
    return "Example Caster Soul"; 
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
public int 
query_cmd_soul() 
{ 
    return 1; 
}
  
public mapping
query_cmdlist()
{
    return ([
        /* Command name : Function name */
        "ealignment"    : "do_ability",
        "eatwill"       : "do_ability",
        "eblind"        : "do_ability",
        "eblink"        : "do_ability",
        "ecalm"         : "do_ability",
        "ecleanse"      : "do_ability",
        "edarkvision"   : "do_ability",
        "edelayedtrigger": "do_ability",
        "edetect"       : "do_ability",
        "edetectresist" : "do_ability",
        "eevade"        : "do_ability",
        "efartell"      : "do_ability",
        "efatigue"      : "do_ability",
        "efeatherweight": "do_ability",
        "eharm"         : "do_ability",
        "ehaste"        : "do_ability",
        "eheal"         : "do_ability",
        "eidentify"     : "do_ability",
        "eillfortunate" : "do_ability",
        "einvisibility" : "do_ability",
        "elight"        : "do_ability",
        "emassharm"     : "do_ability",
        "eparanoia"     : "do_ability",
        "eplant"        : "do_ability",
        "eprotectfear"  : "do_ability",
        "ereflect"      : "do_ability",
        "erefresh"      : "do_ability",
        "eregeneration" : "do_ability",
        "eresistance"   : "do_ability",
        "escry"         : "do_ability",
        "eshadow"       : "do_ability",
        "eshapeshift"   : "do_ability",
        "eshatter"      : "do_ability",
        "eslow"         : "do_ability",
        "estatboost"    : "do_ability",
        "estoneskin"    : "do_ability",
        "estun"         : "do_ability",
        "esummon"       : "do_ability",
        "eteleport"     : "do_ability",
        "etruesight"    : "do_ability",
    ]);
}

public mapping
query_ability_map()
{
    return ([
        "ealignment"    : SPELLS_DIR + "alignment",
        "eatwill"       : SPELLS_DIR + "at_will_harm",
        "eblind"        : SPELLS_DIR + "blind",
        "eblink"        : SPELLS_DIR + "blink",
        "ecalm"         : SPELLS_DIR + "calm",
        "ecleanse"      : SPELLS_DIR + "cleanse",
        "edarkvision"   : SPELLS_DIR + "darkvision",
        "edelayedtrigger": SPELLS_DIR + "delayedtrigger",
        "edetect"       : SPELLS_DIR + "detect_magic",
        "edetectresist" : SPELLS_DIR + "detect_resistance",
        "eevade"        : SPELLS_DIR + "evade",
        "efartell"      : SPELLS_DIR + "fartell",
        "efatigue"      : SPELLS_DIR + "fatigue",
        "efeatherweight": SPELLS_DIR + "featherweight",
        "eharm"         : SPELLS_DIR + "harm",
        "ehaste"        : SPELLS_DIR + "haste",
        "eheal"         : SPELLS_DIR + "heal",
        "eidentify"     : SPELLS_DIR + "identify",
        "eillfortunate" : SPELLS_DIR + "illfortunate",
        "einvisibility" : SPELLS_DIR + "invisibility",
        "elight"        : SPELLS_DIR + "light",
        "emassharm"     : SPELLS_DIR + "mass_harm",
        "eparanoia"     : SPELLS_DIR + "paranoia",
        "eplant"        : SPELLS_DIR + "plant",
        "eprotectfear"  : SPELLS_DIR + "protect_dragonfear",
        "ereflect"      : SPELLS_DIR + "reflect",
        "erefresh"      : SPELLS_DIR + "refresh",
        "eregeneration" : SPELLS_DIR + "regeneration",
        "eresistance"   : SPELLS_DIR + "resistance",
        "escry"         : SPELLS_DIR + "scry",
        "eshadow"       : SPELLS_DIR + "shadow",
        "eshapeshift"   : SPELLS_DIR + "shapeshift",
        "eshatter"      : SPELLS_DIR + "shatter",
        "eslow"         : SPELLS_DIR + "slow",
        "estatboost"    : SPELLS_DIR + "statboost",
        "estoneskin"    : SPELLS_DIR + "stoneskin",
        "estun"         : SPELLS_DIR + "stun",
        "esummon"       : SPELLS_DIR + "summon",
        "eteleport"     : SPELLS_DIR + "teleport",
        "etruesight"    : SPELLS_DIR + "truesight",
    ]);
}
