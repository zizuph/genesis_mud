/*
 *  /d/Gondor/guilds/morgulmage/morgul_spells.c
 *
 *  Command soul for the morgul mages, containing the various spells
 *  that are available to the players.
 *
 *  Created by Eowul, Oktober 6th, 2009
 */
 
#pragma strict_types

#include "morgulmage.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
public string
get_soul_id() 
{ 
    return GUILD_NAME + " Spells"; 
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
        "palanquendo"   : "do_ability",
        "mortirio"      : "do_ability",
        "ringurth"      : "do_ability",
        "narusse"       : "do_ability",
        "narkirisse"    : "do_ability",
        "dramalgos"     : "do_ability",
        "morthul"       : "do_ability",
        "faugoroth"     : "do_ability",
        "turniawath"    : "do_ability",
        "gostangwedh"   : "do_ability",
        "sulambar"      : "do_ability",
        "arhalgul"      : "do_ability",
        "artirith"      : "do_ability",
        "yalarochrama"  : "do_ability",
        "nifarist"      : "do_ability",
        "naro"          : "do_ability",
        "crabandir"     : "do_ability",
        "thunaur"       : "do_ability",
        "mordru"        : "do_ability",
     ]);
}


public mapping
query_ability_map()
{
    return ([
        "palanquendo"  : MORGUL_SPELL_DIR + "palanquendo",
        "narusse"      : MORGUL_SPELL_DIR + "narusse",
        "morthul"      : MORGUL_SPELL_DIR + "morthul",
        "dramalgos"    : MORGUL_SPELL_DIR + "dramalgos",
        "narkirisse"   : MORGUL_SPELL_DIR + "narkirisse",
        "ringurth"     : MORGUL_SPELL_DIR + "ringurth",
        "faugoroth"    : MORGUL_SPELL_DIR + "faugoroth",
        "turniawath"   : MORGUL_SPELL_DIR + "turniawath",
        "gostangwedh"  : MORGUL_SPELL_DIR + "gostangwedh",
        "sulambar"     : MORGUL_SPELL_DIR + "sulambar",
        "arhalgul"     : MORGUL_SPELL_DIR + "arhalgul",
        "artirith"     : MORGUL_SPELL_DIR + "artirith",
        "yalarochrama" : MORGUL_SPELL_DIR + "yalarochrama",
        "nifarist"     : MORGUL_SPELL_DIR + "nifarist",
        "naro"         : MORGUL_SPELL_DIR + "naro",
        "crabandir"    : MORGUL_SPELL_DIR + "crabandir",
        "mortirio"     : MORGUL_SPELL_DIR + "mortirio",
        "thunaur"      : MORGUL_SPELL_DIR + "thunaur",
        "mordru"       : MORGUL_SPELL_DIR + "mordru",
    ]);
}
