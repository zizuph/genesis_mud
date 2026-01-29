/*
 * Ckrik - Initial commit 7/7/2020
 *
 */
#pragma no_clone
#pragma save_binary
#pragma strict_types

#include <ss_types.h>
#include <tasks.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define BASE ("/d/Ansalon/guild/society/")

public string *
query_guild_shadows_society()
{
    return ({ BASE + "kender_shadow" });
}

public string *
query_guild_souls_society()
{
    return ({ BASE + "kender_soul" });
}

public mapping
query_guild_skills_society()
{
    return ([ 
            143010          : 100,
            143011          : 100,
            SS_HIDE         : 100,    
            SS_SNEAK        : 100,
            SS_AWARENESS    : 100,
            SS_OPEN_LOCK    :  90,
            SS_PICK_POCKET  :  90,
            SS_WEP_POLEARM  :  85,
            SS_WEP_KNIFE    :  75,
            SS_DEFENCE      :  75,
            SS_PARRY        :  55,
            SS_ACROBAT      :  90,
            SS_CLIMB        :  75,
            SS_FR_TRAP      :  85,
        ]);              
}

public int
start_guild_society(object player)
{
    return 1;
}

public int
stop_guild_society(object player)
{
    return 1;
}
