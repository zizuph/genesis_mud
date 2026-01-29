/*
 * NOTE:  See /cmd/std/soul_cmd.c for more examples of coding emotes.
 */

#pragma strict_types
#include "/d/Shire/common/defs.h"

/* Inherit this for guild souls */
inherit "/cmd/std/command_driver";

#include "guild.h"

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <cmdparse.h>

#include "emotes.h"

string
get_soul_id() 
{ 
    return GUILD_NAME + " soul"; 
}

int 
query_cmd_soul() 
{ 
    return 1; 
}

mapping
query_cmdlist()
{
    return emote_cmdlist();
}

