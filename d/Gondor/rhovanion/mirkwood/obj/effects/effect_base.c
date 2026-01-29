/*
 *  /d/Gondor/rhovanion/mirkwood/obj/effects/effect_base.c
 *
 *  Base file for all Rhovanion magical effects that exist upon items.
 *
 *  set_average_range(int average, int max_average)
 *
 *      Determine the stat range of the effect, up to [average] the full 
 *      effect will be applied. From [average] to [max_average] the effect
 *      gets reduced linearly. After [max_average] there will be no magical
 *      effect.
 *
 *  set_level(int level)
 *
 *      Determines the strength of this effect.
 *
 *  Created by Eowul, November 15th, 2015
 */

inherit "/std/object";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

private int _level = 1;
private int _average = 1;
private int _max_average = 500;
private int _effect_active = 0;

void notify_effect_applied(object player, object source) 
{   
    player->catch_msg("You feel a tingling sensation but are unable to "
        + "discover it's effect.\n"); 
}

void notify_effect_removed(object player, object source)
{    
    player->catch_msg("You feel more normal.\n");
}

void notify_effect_expired(object player, object source)
{
    player->catch_msg("Mentally drained, you feel more normal.\n");
}

void apply_effect(float multiplier, object player, object source, int level) 
{
}

void remove_effect(object player, object source) 
{
}

public nomask void
set_level(int level)
{    
    _level = min(2, max(1, level));
}


public nomask void
set_average_range(int average, int max_average)
{    
    _average = average;
    _max_average = max_average;
}

private float calculate_multiplier(object player) 
{
    int avg = player->query_average_stat();
    float multiplier = 1.0;

    if (avg > _average) 
    {
        send_debug_message("effect_base", "Player avg higher than " 
            + _average + ", correcting bonus");

        int additional_avg = min(_max_average, avg) - _average;
        int avg_range = max(1, (_max_average - _average));
        
        send_debug_message("effect_base", sprintf("Player avg: %d, min %d, "
            + "max %d", avg, _average, _max_average)); 
        send_debug_message("effect_base", sprintf("Additional: %d, range %d", 
            additional_avg, avg_range));

        multiplier = max(min(1.0, itof(avg_range - additional_avg) / itof(avg_range)), 0.0);
    }

    return multiplier;
}

public nomask void 
activate_effect(object player, object source)
{
    if (!_effect_active) {
        float multiplier = calculate_multiplier(player);
        if (multiplier > 0.0) 
        {
            send_debug_message("effect_base", "Applying magical effect");
            _effect_active = 1;
            apply_effect(multiplier, player, source, _level);
            notify_effect_applied(player, source);
        } else {
            send_debug_message("effect_base", "Zero multiplier, no effect applied");
        }
    } else {
        send_debug_message("effect_base", "Magical effect already applied");
    }
}

public nomask void
deactivate_effect(object player, object source)
{
    if (_effect_active) {
        send_debug_message("effect_base", "Deactivating magical effect");
        _effect_active = 0;
        notify_effect_removed(player, source);
        remove_effect(player, source);
    } else {
        send_debug_message("effect_base", "Magical effect already deactivated");
    }
}