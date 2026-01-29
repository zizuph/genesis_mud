/*
 * Centralized Base Spell
 *
 * Include this file in a centralized spell. By using this, it allows the 
 * AoB team to tweak things like mana easily and have the effects be global.
 *
 * Created by Petros, February 2009
 *
 * Modified how resistance is checked to take into account negative values
 * of resistance (i.e. vulnerability).  Arman October 2017
 *
 * Modified how mana cost was calculated for at-will harm spells, changing
 * it to take into account both int and wis, rather than just int.
 * (resulted in weird scenarios where someone with 300 int/ 150 wis could
 * spam at-will spells twice as long as a 300 int/ 300 wis caster.
 *
 * Changed back to just take into account wisdom... for now. The formula
 * seems really weird. 
 * - Arman Kharas - December 2018
 *
 * Added the function query_spell_weapon_class_stat_influencer() to allow
 * for alternative stats to be used in determining spell_weapon_class beyond
 * intelligence.
 * - Arman Kharas - August 2019
 * 
 * Fixed cloning of spell objects into the void.
 * - Cotillion, Oct 2020
 *
 * Added the ability to apply white-hit aid when the combat aid is being
 * set.  Zizuph Feb 2022
 *
 * Turn one-handed spell enhancers into two if the other hand is free.
 * Zizuph Feb 2022
 *
 * Delegate spell object moving to the spell object itself.
 * Zizuph July 2022
 *
 * For white-hit boosted spells, move them automatically into a different
 * ability group.
 * Zizuph Aug 2022
 *
 *
 * Add new function to easily apply set_ability_skill based on element
 * and form where the trainable level may be less than 100.
 * Zizuph Dec 2022
 *
 */

#pragma strict_types

#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
#include <tasks.h>

#include "defs.h"

#define SPELL_DEFAULT_WHITEHIT_BOOSTED_GROUP  "spell_default_boosted_group"


inherit SPELL_LIB;

// Defines
#define     MINIMUM_SPELL_TIME          4
#define     AT_WILL_SPELL_TIME          15
#define     LIVE_O_MAINTAINED_EFFECTS   "_live_o_maintained_effects"
// At will spells use a certain amount of mana based on the regen rate
// The cost factor is from 1.0-100.0, and will be a fraction of the
// max at will mana. The reason to set it lower is to allow mana
// regeneration even during at will grinding.
#define     AT_WILL_MANA_COST_FACTOR    75.0

// Global Variables
private mixed       Time_factor = 1.0;
private int         At_will_spell = 0;
private int         Pre_modification_combat_aid = 0;
private int         Can_be_renewed = 0;
private int         maintained_combat_aid = 0;
private float       spell_component_factor = COMPONENT_AID_NONE;
private status      Can_be_resisted = 0;
private status      Apply_whitehit_combat_aid = 0;

public object
get_best_spellpower_enhancer(object actor)
{
    object* tools = ({ actor->query_tool(W_LEFT), 
                       actor->query_tool(W_RIGHT) });
    int highest_power = 0;
    object best_tool;
    foreach (object tool : tools)
    {
        if (!tool->query_spellpower_enhancer())
            continue;
        if (!tool->query_spellpower_elements())
            continue;
        if (member_array(query_spell_element_skill(),
            tool->query_spellpower_elements()) < 0)
            continue;
        if (tool->query_magic_spellpower() > highest_power)
        {
            best_tool = tool;
            highest_power = tool->query_magic_spellpower();            
        }
    }
    return best_tool;
}


public int get_spellpower(object actor, object enhancer)
{
    int power;
    if (enhancer)
    {
        power = enhancer->query_magic_spellpower();
        int hand_free = !actor->query_tool(W_LEFT)
                       || !actor->query_tool(W_RIGHT);

        if (hand_free)
        {
            //Treat the enhancer like it is two handed.
            power = power * 6 / 5;
        }
    }
    return max(power, get_natural_spellpower(actor));
}


/*
 * Function name:   convert_stats_to_pen
 * Description:     
 * Arguments:       (object) actor 
 * Returns:         (int) 
 */
public int
convert_stats_to_pen(object actor)
{
    object enhancer = get_best_spellpower_enhancer(actor);
    return get_spellpower(actor, enhancer);
} /* convert_stats_to_pen */

/*
 * Function name:   convert_stats_to_hit
 * Description:     
 * Arguments:       (object) actor 
 * Returns:         (int) 
 */
public int
convert_stats_to_hit(object actor)
{
    object enhancer = get_best_spellpower_enhancer(actor);
    return get_spellpower(actor, enhancer);
} /* convert_stats_to_hit */

/*
 * Function:    set_spell_can_be_renewed
 * Description: Sets whether a spell is a renewable maintained effect. 
 *              When set to true, a spell doesn't need to be dispelled
 *              before it can be cast again. This doesn't actually change
 *              the behavior without the actual spell querying and
 *              using the behavior properly. Not all spells support
 *              this property.
 */
public nomask void
set_spell_can_be_renewed(int bRenewable)
{
    Can_be_renewed = bRenewable;
}

/*
 * Function:    query_spell_can_be_renewed
 * Description: Gives a hint to the spell whether this spell can
 *              be renewed. If so, the spell object does not need to be
 *              dispelled first. The duration merely needs to get extended.
 */
public int
query_spell_can_be_renewed()
{
    return Can_be_renewed;
}

/*
 * Function name:   query_spell_can_be_resisted
 * Description:     Returns whether the spell is resistible or not.
 * Arguments:       None
 * Returns:         (status) - 1/0 Can be resisted / Cant be resisted
 */
public status
query_spell_can_be_resisted()
{
    return Can_be_resisted;
} /* query_spell_can_be_resisted */

/*
 * Function name:   set_spell_can_be_resisted
 * Description:     This can be set to make a spell resistible, this function
 *                  manifests itself by failing to apply the spell object if
 *                  the resist value is higher than random 100.
 * Arguments:       (status) - 1/0 Can be resisted / Cant be resisted
 * Returns:         Nothing
 */
public void
set_spell_can_be_resisted(status res)
{
    Can_be_resisted = res;
} /* set_spell_can_be_resisted */

/*
 * Function name:   query_spell_apply_whitehit_aid
 * Description:     Whether to add whitehit aid to total combat aid
 * Arguments:       None
 * Returns:         (status) - 1/0 White aid will be added/not.
 */
public status
query_spell_apply_whitehit_aid()
{
    return Apply_whitehit_combat_aid;
} /* query_spell_apply_whitehit_aid */

/*
 * Function name:   set_spell_apply_whitehit_aid
 * Description:     Specify whether to add whitehit aid to the caid.
 *                  
 *                  
 * Arguments:       (status) - 1/0 apply whitehit aid or not
 * Returns:         Nothing
 */
public void
set_spell_apply_whitehit_aid(status res)
{
    Apply_whitehit_combat_aid = res;
    if (res)
    {
        set_ability_group(SPELL_DEFAULT_WHITEHIT_BOOSTED_GROUP);
    }
    else
    {
        set_ability_group(SPELL_DEFAULT_GROUP);
    }
} /* set_spell_apply_whitehit_aid */


/*
 * Function:    set_spell_at_will
 * Description: This allows a spell to have its base mana cost based on the
 *              regen rate of the caster.
 */
public nomask void
set_spell_at_will(int bAtWill)
{
    At_will_spell = bAtWill;
}

/* 
 * Function:    query_spell_at_will
 * Description: Call this function to determine whether the spell
 *              doesn't set a base cost, but instead is based on
 *              the mana regen rate of the caster.
 */
public nomask int
query_spell_at_will()
{
    return At_will_spell;
}

/*
 * Function:    get_at_will_spell_mana
 * Description: This returns the at-will mana usage for this player
 *              which is based on the wisdom stat and the spellcraft
 *              skill (regen rate)
 */
public nomask int
get_at_will_spell_mana()
{
    int mana;
    float factor;
    
    object caster = this_player();
    if (query_spell_at_will() && living(caster))
    {
        // An at will spell has a spell cost based on the mana regen of
        // the caster. We use the base regen formula and adjust it according
        // to the at will spell time.
        int wisdom = caster->query_stat(SS_WIS);
        int intel = caster->query_stat(SS_INT);
        int spellcasting = caster->query_skill(SS_SPELLCRAFT);
        int avg_mentals = (wisdom + intel) / 2;   
            
        mana = (1 + 100 * wisdom * spellcasting / 50000) * 
            AT_WILL_SPELL_TIME / F_INTERVAL_BETWEEN_MANA_HEALING;

/*  Changed back to original formula.. only takes into account wis
        mana = (1 + 100 * avg_mentals * spellcasting / 50000) * 
            AT_WILL_SPELL_TIME / F_INTERVAL_BETWEEN_MANA_HEALING;
*/
        mana = ftoi(itof(mana + 1) * AT_WILL_MANA_COST_FACTOR / 100.0);
    }
    else
    {
        // Not an At Will Spell
        return 0;
    }
    
    factor = query_spell_mana_factor();
    
    // Mana cost can never be 0, so keep it at minimum 1.
    return max(1, ftoi(itof(mana) * factor));
}

/*
 * Function:    get_spell_mana
 * Description: Returns what the mana should be for this spell, based on
 *              the mana and factor set. Used for regular (non-at-will)
 *              spells
 */
public nomask int
get_spell_mana()
{
    int mana;
    
    if (query_spell_at_will())
    {
        mana = get_at_will_spell_mana();
    }
    else
    {    
        int base_mana = ::get_spell_mana();
        float factor = query_spell_mana_factor();
        
        // Mana cost can never be 0, so keep it at minimum 1.
        mana = max(1, ftoi(itof(base_mana) * factor));
    }
    
    send_debug_message("debug_spell_mana", "Using "
        + mana + " mana.");
    return mana;
}

/*
 * Function:    set_spell_time_factor
 * Description: This function sets a factor that this spell will cast
 *              relative to the base cost.
 * Arguments:   factor - a floating number. 1.0 means it is the same as
 *                       the base cost. 0.5 means it costs half the amt
 *                       and 1.5 means that it costs 50% more.
 *                       Note: factor can be a function pointer that returns
 *                             a float.
 */
public nomask void
set_spell_time_factor(mixed factor)
{
    Time_factor = factor;
}

/*
 * Function:    query_spell_time_factor
 * Description: Returns what the spell factor set by this spell is
 */
public nomask float
query_spell_time_factor()
{
    if (functionp(Time_factor))
    {
        function f = Time_factor;
        return f();
    }
    
    return Time_factor;
}

/*
 * Function:    query_ability_prep_time
 * Description: This function is the one called by timed_ability to
 *              actually set the alarm. We mask it here so that we
 *              can set up the factor.
 */
// TODO - Need to set this to nomask once all dependent spells don't need it anymore.
public int
query_ability_prep_time()
{
    int base_time = MINIMUM_SPELL_TIME; // minimum spell time is 4

    mixed factor = query_spell_time_factor();
    int prep_time = base_time;
    if (floatp(factor))
    {
        prep_time = max(1, ftoi(itof(base_time) * factor));
    }
    else if (intp(factor))
    {
        prep_time = max(1, base_time * factor);
    }
    
    return prep_time;
}

public int
query_white_hit_combat_aid()
{
    int spell_time = query_ability_prep_time() + query_ability_cooldown_time();
    return query_ability_prep_time() * 100 / spell_time;
}

/*
 * Function:    query_ability_cooldown_time
 * Description: Returns the cooldown time for spells. By default, spells
 *              do not have cooldown times. However, for at will spells,
 *              it has a default of AT_WILL_SPELL_TIME - MINIMUM_SPELL_TIME
 */
public int
query_ability_cooldown_time()
{
    if (!query_spell_at_will())
    {
        return 0; // non at-will spells always have no cooldown
    }

    int cooldown_time = AT_WILL_SPELL_TIME - MINIMUM_SPELL_TIME;
    // We multiply things by the time factor
    mixed factor = query_spell_time_factor();
    if (floatp(factor))
    {
        cooldown_time = max(0, ftoi(itof(cooldown_time) * factor));
    }
    else if (intp(factor))
    {
        cooldown_time = max(0, cooldown_time * factor);
    }
    
    return cooldown_time;
}

/*
 * Function:    set_spell_combat_aid
 * Description: This function sets the combat aid that this spell should
 *              provide.
 * Arguments:   aid - the combat aid max this spell provides
 */
public nomask void
set_spell_combat_aid(mixed aid)
{
    if (floatp(aid))
        aid = ftoi(aid);
    
    if (!intp(aid))
        aid = 0;

    // Store this value, in case the component factor is set
    // after the combat aid is set.
    Pre_modification_combat_aid = aid;
    
    if (query_spell_apply_whitehit_aid())
    {
        aid += query_white_hit_combat_aid();
    }

    aid = ftoi(itof(aid) * spell_component_factor);
    set_ability_combat_aid(aid);
}

/*
 * Function:    set_spell_expected_skill_levels
 * Description: This function sets what the required average skill
                level is needed to get full effect.
 * Arguments:   level - the skill level at maximum training of
                the caster's (form + element) / 2
 */
public nomask void
set_spell_expected_skill_levels(int level)
{
    set_ability_skills(({ SKILL_WEIGHT, 10000 / level, SKILL_AVG, 
      query_spell_form_skill(), query_spell_element_skill(), 
      SKILL_END}));
}

/*
 * Function:    query_spell_maintained_combat_aid
 * Description: Set how much maintained spells should cost
 *              in mana, in terms of combat aid.  This only
 *              applies if the spell does not have combat aid
 *              set.
 */
public void
set_spell_maintained_combat_aid(mixed aid)
{
    if (floatp(aid))
        aid = ftoi(aid);
    
    if (!intp(aid))
        aid = 0;
    maintained_combat_aid = aid;
}

/*
 * Function:    query_spell_maintained_combat_aid
 * Description: Returns how much maintained spells should cost
 *              in mana, in terms of combat aid.  This only
 *              applies if the spell does not have combat aid
 *              set.
 */
public int
query_spell_maintained_combat_aid()
{
    return maintained_combat_aid;
}


/*
 * Function:    query_spell_component_factor
 * Description: Returns how much more combat aid should be
 *              given to a spell to compensate for time to gather
 *              component costs.
 */
public float query_spell_component_factor()
{
    return spell_component_factor;
}

/*
 * Function:    query_spell_component_factor
 * Description: Set how much more combat aid should be
 *              given to a spell to compensate for time to gather
 *              component costs.  Any override of this value
 *              must be approved by the AOB team.
 */
public void set_spell_component_factor(float factor)
{
    spell_component_factor = factor;

    // We recompute this, in case the spell factor set
    // set after the combat aid.    
    set_spell_combat_aid(Pre_modification_combat_aid);
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    int modifier = ::query_ability_combat_aid_modifier();
    
    return itof(modifier);
}

/*
 * Function name:   query_ability_combat_aid_modifier
 * Description:     Calculates the percentage of the maximum combat aid
 *                  that applies to the current situation
 * Arguments:       (object) actor - player executing special
 * Returns:         (int) number between 1 and 100
 */
public int
query_ability_combat_aid_modifier()
{
    // Masked so that query_spell_combat_aid_modifier to work as intended
    return ftoi(query_spell_combat_aid_modifier());
} /* query_ability_combat_aid_modifier */

/*
 * Function:    query_spell_combat_aid
 * Description: Returns what the spell's max combat aid should be
 */
public nomask float
query_spell_combat_aid()
{
    // Combat aid is modified by the modifier function.
    int modifier = query_ability_combat_aid();
    
    return itof(modifier);
}

/*
 * Function:    query_spell_guild_strength
 * Description: This should be overridden by each implementation of
 *              the spell to use elements like guild stat as part of
 *              the guild strength calculation.
 * Returns:     0-100 - scale of the person's strength in the guild.
 *                      Should not exceed 100.
 */
public int
query_spell_guild_strength()
{
    return 100;
}

/*
 * Function name:   query_guildstat_modifier_helper
 * Description:     This is the helper function for calc_guild_stat_modifier
 *                  It takes in the values and does a standard set of
 *                  calculations to determine the modifier for the special.
 * Arguments:       (object) player - the player executing the special
 *                  (int) res - the current pen value to be modified
 * Returns:         (int) res modified by guildstat
 */
public varargs nomask int
query_guildstat_modifier(object player, int res, int gstat_type = 0,
    int gstat_min_pct = 0, int gstat_cap = 0)
{
    if (!query_guild_stat_type(player))
    {
        // Masked to allow for query_spell_guild_strength
        return res * min(query_spell_guild_strength(), 100) / 100;
    }
    
    return ::query_guildstat_modifier(player, res, gstat_type, gstat_min_pct,
            gstat_cap);
} /* query_guildstat_modifier */

/*
 * Function:    query_spell_power
 * Description: A generic power calculation function that takes into
 *              account skills, stats, and guild strength
 */
public int
query_spell_power()
{
    return max(1, query_ability_power(this_player()));
}

/*
 * Function name: make_spell_object
 * Description:   Create, default configure, and move spell objects
 *                to the targets.
 * Arguments:     1. (object)   The spell effect object
 *                   (string)   The filename of the spell effect (to be cloned)
 *                   (function) A function that returns a spell effect
 *                2. (object)   The caster
 *                3. (object)   The target
 *                   (object *) An array of targets
 *                4. (int)      Resistance value for single target
 *                   (int *)    Resistance values corresponding to each target
 *                5. (int)      The casting success, as given by
 *                              query_casting_success()
 *                6. (mixed)    Any input that the spell wants to pass along to
 *                              the spell object
 * Returns:       (object *) An array of spell effect objects, one element for
 *                           each target
 *                (object)   A single spell effect object if target was
 *                           specified as a single object.
 */
public mixed
make_spell_object(mixed obj, object caster, mixed targets, 
                  mixed resist, int result, mixed input = 0)
{
    int i;
    object spell, *obs;
    function f;
    object *target_arr,
           *targets_resisted = ({});
    int *resist_arr;

    target_arr = (pointerp(targets) ? targets : ({ targets }));
    resist_arr = (pointerp(resist)  ? resist  : ({ resist }));
    i = sizeof(target_arr);
    obs = allocate(i);

    setuid();
    seteuid(getuid());
    while (i--)
    {
        if (Can_be_resisted && resist_arr[i] > random(100))
        {
            targets_resisted += ({ target_arr[i] });
            continue;
        }
 
        if (functionp(obj))
        {
            f = obj;
            spell = f(caster, targets);
        }
        else if (stringp(obj))
        {
            spell = clone_object(obj);
        }
        else
        {
            spell = obj;
        }

        obs[i] = spell;

        spell->set_spell_effect_name(query_ability_name());
        spell->set_spell_effect_desc(query_spell_desc());
        spell->set_spell_effect_element(Element_skill);
        spell->set_spell_effect_form(Form_skill);
        spell->set_spell_effect_class(get_spell_class());
        spell->set_spell_effect_caster(caster);
        spell->set_spell_effect_target(target_arr[i]);
        spell->set_spell_effect_power(query_spell_power());
        spell->set_spell_effect_input(input);
        spell->set_spell_combat_aid(query_spell_combat_aid());
        spell->set_spell_maintained_combat_aid(
            itof(query_spell_maintained_combat_aid()));
        spell->set_spell_task(get_spell_task());
        spell->set_spell_stats(query_ability_stats());
        spell->set_spell_skills(query_ability_skills());
        
        if (!spell->setup_spell_effect())
        {
            spell->remove_object();
            obs[i] = 0;
        }
        
        if (objectp(obs[i]))
        {
            // The spell effect object moves itself to the target, or
            // the caster (is the target is not a container) in 
            // setup_spell_effect.
            //obs[i]->move(target_arr[i], 1);
            
            // We add the effect to the caster's prop so that he can see
            // what effects he is maintaining
            object * effects = caster->query_prop(LIVE_O_MAINTAINED_EFFECTS);
            if (!pointerp(effects))
            {
                effects = ({ obs[i] });
            }
            else
            {
                effects += ({ obs[i] });
            }
            effects -= ({ 0 }); // clear deleted effects
            caster->add_prop(LIVE_O_MAINTAINED_EFFECTS, effects);
        }
    }
    
    if (sizeof(targets_resisted))
        hook_resist_spell_object(obs, caster, targets_resisted);
    
    if (pointerp(targets))
    {
        return obs;
    }

    return obs[0];
}

/* 
 * Function:    get_existing_spell_objects
 * Description: Spells sometimes need to check if the target already
 *              has an existing spell object for the spell. This is
 *              to either prevent another from being cast, or to remove
 *              the existing ones, and renew the effect.
 */
public object *
get_existing_spell_objects(object target)
{
    // query_spell_obj, even though is coded to return functcions and object
    // instances, we will for the magic system only use strings.
    mixed spell_object_file = query_spell_object();
    if (!stringp(spell_object_file))
    {
        return 0;
    }
    
    mixed effects = filter(target->query_magic_effects(),
                        &wildmatch(spell_object_file + "#*") @ file_name);
    if (sizeof(effects))    
    {   
        return effects;
    }
    
    return 0;
}

/*
 * Function name: has_spell_object
 * Description:   Checks to see if the target already has the spell object
 */
public int 
has_spell_object(object target)
{
    object * effects = get_existing_spell_objects(target);
    if (sizeof(effects))    
    {   
        return 1;
    }
    
    return 0;
}

/*
 * Function name: has_spell_object
 * Description:   Checks to see if the target already has the spell object
 */
public int 
has_caster_spell_object(object caster, object target)
{
    object * effects = get_existing_spell_objects(target);
    foreach (object effect : effects)
    {
        if (effect->query_effect_caster() == caster)
        {
            return 1;
        }
    }
    return 0;
}


// AUTOMATION FUNCTIONS

/*
 * Function:    notify_npc_preparation_complete
 * Description: This is called by prepare_ability when the ability has 
 *              actually finished its preparation, and executed the special.
 *              It will primarily be used to help the test rooms to
 *              coordinate the next ability to use for the npcs. This
 *              is NOT called for normal players.
 */
public void
notify_npc_preparation_complete(object player, string arg)
{
    player->notify_spell_complete(this_object(), arg);
}

/*
 * Function:    notify_npc_cooldown_complete
 * Description: This is called by cooldown_ability when the ability has 
 *              actually finished its cooldown.
 *              It will primarily be used to help the test rooms to
 *              coordinate the next ability to use for the npcs. This
 *              is NOT called for normal players.
 */
public void
notify_npc_cooldown_complete(object player, string arg)
{
    player->notify_spell_cooldown_complete(this_object(), arg);
}
