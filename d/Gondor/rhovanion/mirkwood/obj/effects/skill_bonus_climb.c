#pragma strict_types;

#include <stdproperties.h>
#include <macros.h>
#include "../../defs.h"
#include <ss_types.h>

inherit MIRKWOOD_OBJ_DIR + "effects/skill_bonus";

void create_object()
{
    ::create_object();
    set_bonus_skill(SS_CLIMB);
}

void notify_effect_applied(object player, object source) 
{   
    player->catch_msg("You feel more like a climber.\n"); 
}

void notify_effect_removed(object player, object source)
{    
    player->catch_msg("You feel less of a climber.\n");
}

void notify_effect_expired(object player, object source)
{
    player->catch_msg("You are so mentally drained, you no longer feel "
        + "more skilled in climbing.\n");
}