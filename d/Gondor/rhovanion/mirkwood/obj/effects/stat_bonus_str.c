#pragma strict_types;

#include <stdproperties.h>
#include <macros.h>
#include "../../defs.h"
#include <ss_types.h>

inherit MIRKWOOD_OBJ_DIR + "effects/stat_bonus";

void create_object()
{
    ::create_object();
    set_bonus_stat(SS_STR);
}

void notify_effect_applied(object player, object source) 
{   
    player->catch_msg("You feel somewhat stronger.\n"); 
}

void notify_effect_removed(object player, object source)
{    
    player->catch_msg("You feel somewhat weaker.\n");
}

void notify_effect_expired(object player, object source)
{
    player->catch_msg("You feel not only mentally weaker, but "
        + "also physically.\n");
}