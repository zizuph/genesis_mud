/*
 */
#pragma strict_types

inherit "/d/Genesis/specials/std/effect_obj_base";

#include "../guild.h"

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <state_desc.h>
#include <cmdparse.h>
#include <files.h>
#include <ss_types.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Prototypes
public void     maintained_focus(object player);


// Global variables
static mapping  skill_list = ([]);
static string  *active_effects = ({});
static int      senses_alarm;

public int
is_archer_senses_object()
{
    return 1;
}

public status
handle_skill_list(object player)
{
    string  sense;
    int     value;
    
    if (!stringp(sense = calling_function()) ||
        member_array(sense, m_indexes(F_SKILLS)) < 0)
        return 0;
    
    value = player->query_skill(SS_FOCUS);
    foreach(int skill, int modifier: F_SKILLS[sense])
    {
        if (member_array(skill, m_indexes(skill_list)) < 0)
            skill_list[skill] = (((player->query_base_skill(skill) * value) /
            200) * modifier) / 100;
        else
            skill_list[skill] = -skill_list[skill];
        
        player->set_skill_extra(skill, player->query_skill_extra(skill)
        + skill_list[skill]);
        
        if (skill_list[skill] <= 0)
            m_delkey(skill_list, skill);
    }
    
    return 1;
}

public status
senses(object player)
{
    int     state = IN_ARRAY("senses", active_effects);
    string *list  = ({});
    
    if (handle_skill_list(player))
        list += ({ "senses" });
    
    foreach(string sense: FOCUS_LIST)
    {
        // Prevent non-synced senses
        if (state != IN_ARRAY(sense, active_effects))
            continue;
        
        if (sense != F_SENSES && (status) call_self(sense, player))
            list += ({ sense });
    }
    
    // Remove/Add effects from/to the effect list
    if (state)
    {
        active_effects -= list;
        
        player->catch_msg("Your senses dull as you release your maintained "
        + "focus, and relief washes over you as the mental strain fades.\n");
    }
    else
    {
        active_effects = FOCUS_LIST;
        
        player->catch_msg("You focus to maintain all your senses at a "
        + "heightened state, feeling the mental strain creeping upon you.\n");
    }
    
    return 1;
}

public status
sight(object player)
{
    int vision  = CAN_SEE_IN_ROOM(player),
        state   = IN_ARRAY("sight", active_effects);
        
    handle_skill_list(player);
    // Its a toggle function, so if its active, we remove it, otherwise we add.
    player->add_prop(LIVE_I_SEE_DARK, player->query_prop(LIVE_I_SEE_DARK)
    + (state ? -1 : 1));
    
    if (calling_function() != "senses")
    {
        if (state)
        {
            active_effects -= ({ "sight" });
            
            player->catch_msg("The shadows around you creep back into view as "
            + "your focus fades, painting the world in a darker shade.\n");
        }
        else
        {
            active_effects += ({ "sight" });
            
            player->catch_tell("As you strain yourself to focus your eyes, the "
            + "shadows begin to fade." + (!vision ? " The world around you is "
            + "left painted in a pallid grey. The surroundings previously "
            + "hidden in the dark is now clearly visible before you." : "")
            + "\n");
        }
    }
    
    return 1;
}

public status
hearing(object player)
{
    int state = IN_ARRAY("hearing", active_effects);
    
    handle_skill_list(player);
    
    if (state)
        player->remove_senses_shadow();
    else if (!player->has_senses_shadow())
        clone_object(SENSES_SH)->shadow_me(player);
    
    if (calling_function() != "senses")
    {
        if (state)
        {
            active_effects -= ({ "hearing" });
            
            player->catch_msg("The once distinct sounds around you fade into "
            + "muddled obscurity.\n");
        }
        else
        {
            active_effects += ({ "hearing" });
            
            player->catch_msg("You focus to discern the noises around you. "
            + "With every breath, rustle and footstep the sounds become "
            + "clearer.\n");
        }
    }

    return 1;
}

/*
 * Function name:   create_effect
 * Description:     Basic effect construct
 * Arguments:       None
 * Returns:         Nothing
 */
private void
create_effect()
{
    set_name("archer_senses_object");
    set_short("hidden archer senses object");
    set_long("Players should not see this object.\n");

    set_no_show();
    
    setuid();
    seteuid(getuid());
} /* create_effect */

/*
 * Function name:   start
 * Description:     Start up the senses effect.
 * Arguments:       (string) senses - the sense which we wish to start
 * Returns:         (int) 1/0 - effect started/not started
 */
public int
start_sense(string senses)
{
    int     result;
    object  player;
    status  s_call;
    
    result = ::start();
    if (result && objectp(player = environment(this_object())) &&
        IS_LIVING_OBJECT(player))
        s_call = (status) call_self(senses, player);
    
    if (!senses_alarm)
        senses_alarm = set_alarm(0.0, 5.0, &maintained_focus(player));
    
    return result;
} /* start*/

/*
 * Function name: dispel_effect
 * Description:   Cause this effect to be dispelled.
 *                If the effect is removed, 1 should be returned,
 *                else 0.  Returning 0 should be a rare occurance,
 *                since there generally should not be spell effects
 *                that cannot be dispelled.
 * Arguments:     object dispeler - the person responsible for dispelling
 *                                  the effect.
 * Returns:       1/0 - effect dispelled/not dispelled
 */
varargs public int
dispel_effect(object dispeler)
{
    object  player;
    int     visual;
    
    if (objectp(player = query_effect_target()))
    {
        foreach(string sense: active_effects)
        {
            if (member_array(sense, active_effects) > -1)
                (status) call_self(sense, player);
        }
    }
    
    remove_alarm(senses_alarm);
    set_alarm(0.0, 0.0, &remove_object());
    return 1;
} /* dispel_effect */

public void
maintained_focus(object player)
{
    int relaxed, cost, value, level;
    
    if (!sizeof(active_effects - ({ F_SENSES })))
        dispel_effect(player);
    
    relaxed = player->query_relaxed_from_combat();
    value   = player->query_focus_level();
    
    /*
     * We regenerate 1 focus every second, and drain focus based on the amount
     * of abilities we have active. The drain triggers every 5 seconds.
     * 
     * We shouldn't be able to maintain all three effects without incurring
     * a loss
     */
    foreach(string sense: active_effects)
    {
        switch(sense)
        {
            case F_SIGHT:
            cost += ((value / 9) + 2) / (1 + relaxed);
                break;
            case F_HEARING:
            cost += ((value / 15) + 1) / (1 + relaxed);
                break;
            default:
            cost += ((value / 25) + 1) / (1 + relaxed);
                break;
        }
    }
    
    // We randomize it to make it less linear.
    level = player->add_focus_level(-random(cost));
    
    if (level <= 0)
        dispel_effect(player);
}