#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";

#include "../rangers.h"
#include "/d/Gondor/guilds/rangers/soul/stealth.c"   // The part of stealth held in the soul

public mapping
query_ability_map(void)
{
    return ([
	"rambush": RANGERS_SPECIAL + "ambush",
	"rblind": RANGERS_SPECIAL + "blind",
	"rtrip": RANGERS_SPECIAL + "trip",
	"rdisarm": RANGERS_SPECIAL + "disarm",
	"rdistract": RANGERS_SPECIAL + "distract",
	"cleanse": RANGERS_SPELL + "virtue_cleanse",
	"heal": RANGERS_SPELL + "virtue_heal",
	"rest": RANGERS_SPELL + "virtue_rest",
	"whistle": RANGERS_SPELL + "virtue_whistle",
    ]);
}

/* Commands */
public mapping
query_cmdlist(void)
{
    return ([
        "rambush" : "do_ability",
        "rblind" : "do_ability",
        "rtrip" : "do_ability",
        "rdisarm" : "do_ability",
        "rdistract" : "do_ability",
        "rstealth"   : "stealth_mode",
    ]);
}

/* Id and autoload */
public nomask string
get_soul_id(void)	{ return "Ranger_Test"; }

/* It is a real command soul */
public nomask int
query_cmd_soul(void)	{ return 1; }
