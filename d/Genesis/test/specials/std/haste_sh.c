/*
 * /d/Genesis/specials/std/haste_sh.c
 *
 * Testing the possibility of using a shadow to add and decrease
 * live_i_quickness 
 *
 * Created by Petros
 */

inherit "/std/shadow";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <files.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define LIVE_I_QUICKNESS_MODIFIED "_live_i_quickness_modified"
#define LIVE_I_QUICKNESS_FLOAT "_live_i_quickness_float"

public float
calculate_haste_percentage(int quickness)
{
    return (itof(quickness) * 100.0) / (500.0 - itof(quickness));
}

public int
calculate_quickness(float percentage)
{
    return ftoi(((500.0 * percentage) / (100.0 + percentage)) + 0.1);
}

private void
add_haste(int old_value, int new_value)
{
    int diff, new_quickness;
    float add_percent, cur_percent;
    
    diff = new_value - old_value;
    if (!shadow_who->query_prop(LIVE_I_QUICKNESS_FLOAT)
        || old_value == 0)
    {
        cur_percent = 0.0;
    }
    else
    {
        cur_percent = shadow_who->query_prop(LIVE_I_QUICKNESS_FLOAT);
    }
    add_percent = calculate_haste_percentage(diff);
    send_debug_message("haste_sh", "Percentage was " + ftoi(cur_percent)
                     + " and increasing by " + ftoi(add_percent));    
    cur_percent = cur_percent + add_percent;
    shadow_who->add_prop(LIVE_I_QUICKNESS_FLOAT, cur_percent);
    new_quickness = calculate_quickness(cur_percent);
    if (new_quickness > 300)
    {
        // Cap the amount at 300
        new_quickness = 300;
    }
    shadow_who->add_prop(LIVE_I_QUICKNESS_MODIFIED, 1);
    shadow_who->add_prop(LIVE_I_QUICKNESS, new_quickness);
    send_debug_message("haste_sh", "Setting new quickness value of "
                     + new_quickness);
}

private void
remove_haste(int old_value, int new_value)
{
    int diff, new_quickness;
    float sub_percent, cur_percent;
    
    diff = old_value - new_value;
    if (!shadow_who->query_prop(LIVE_I_QUICKNESS_FLOAT)
        || old_value == 0)
    {
        cur_percent = 0.0;
    }
    else
    {
        cur_percent = shadow_who->query_prop(LIVE_I_QUICKNESS_FLOAT);
    }
    sub_percent = calculate_haste_percentage(diff);
    send_debug_message("haste_sh", "Percentage was " + ftoi(cur_percent)
                     + " and decreasing by " + ftoi(sub_percent));
    cur_percent = cur_percent - sub_percent;
    shadow_who->add_prop(LIVE_I_QUICKNESS_FLOAT, cur_percent);
    new_quickness = calculate_quickness(cur_percent);
    if (new_quickness < 0)
    {
        new_quickness = 0;
        shadow_who->remove_prop(LIVE_I_QUICKNESS_FLOAT);
    }
    else
    {
        shadow_who->add_prop(LIVE_I_QUICKNESS_MODIFIED, 1);
    }
    shadow_who->add_prop(LIVE_I_QUICKNESS, new_quickness);
    send_debug_message("haste_sh", "Setting new quickness value of "
                     + new_quickness);    
}

public int
add_prop_live_i_quickness(mixed val)
{
    int value, old_value;
    
    if (!intp(val))
    {
        // Can only handle integer values.
        return shadow_who->add_prop_live_i_quickness(val);
    }
    
    if (shadow_who->query_prop(LIVE_I_QUICKNESS_MODIFIED))
    {
        // Don't do anything if this property is set. Otherwise
        // could end up with infinite loop.
        send_debug_message("haste_sh", "Removing modified flag");
        shadow_who->remove_prop(LIVE_I_QUICKNESS_MODIFIED);
        return shadow_who->add_prop_live_i_quickness(val);
    }
    
    value = val;
    old_value = shadow_who->query_prop(LIVE_I_QUICKNESS);
    if (value > old_value)
    {
        add_haste(old_value, value);
    }
    else if (value < old_value)
    {
        remove_haste(old_value, value);
    }
    
    // We return 1 to allow our own functions to set the haste.
    return 1;
}
