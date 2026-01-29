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
 */

#pragma strict_types

#include <formulas.h>
#include <ss_types.h>
#include <tasks.h>

#include "defs.h"

inherit "/d/Genesis/specials/spell";

// Defines
#define     MINIMUM_SPELL_TIME          4
#define     AT_WILL_SPELL_TIME          15
// Normal attacks for 40 tohit is about 37% hit rate. Multiply this
// by a standard 43% armour reduction (40ac) and you get about
// 21%. We give spells a boost of 21% combat aid to their declared
// aid amounts.
#define     LOST_CAID_BOOST             21.0
#define     LIVE_O_MAINTAINED_EFFECTS   "_live_o_maintained_effects"
// At will spells use a certain amount of mana based on the regen rate
// The cost factor is from 1.0-100.0, and will be a fraction of the
// max at will mana. The reason to set it lower is to allow mana
// regeneration even during at will grinding.
#define     AT_WILL_MANA_COST_FACTOR    75.0

// Global Variables
private mixed       Mana_factor = 1.0;
private mixed       Time_factor = 1.0;
private float       Combat_aid  = 0.0;
private int         At_will_spell = 0;
private int         Can_be_renewed = 0;
private status      Can_be_resisted = 0;

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
 * Function:    set_spell_mana_factor
 * Description: This function sets a factor that this spell will cast
 *              relative to the base cost.
 * Arguments:   factor - a floating number. 1.0 means it is the same as
 *                       the base cost. 0.5 means it costs half the amt
 *                       and 1.5 means that it costs 50% more.
 *                       Note: factor can be a function pointer.
 */
public nomask void
set_spell_mana_factor(mixed factor)
{
    Mana_factor = factor;
}

/*
 * Function:    query_spell_mana_factor
 * Description: Returns what the spell factor set by this spell is
 */
public nomask float
query_spell_mana_factor()
{
    if (functionp(Mana_factor))
    {
        function f = Mana_factor;
        return f();
    }
    
    return Mana_factor;
}

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
    if (intp(aid))
    {
        Combat_aid = itof(aid);
    }
    else if (floatp(aid))
    {
        Combat_aid = aid;
    }
    else
    {
        Combat_aid = 0;
    }
}

/*
 * Function:    query_spell_combat_aid_modifier
 * Description: Value between 1.0 and 100.0 that will modify
 *              the maximum combat aid granted by this spell.
 */
public float
query_spell_combat_aid_modifier()
{
    return 100.0;    
}

/*
 * Function:    query_spell_combat_aid
 * Description: Returns what the spell's max combat aid should be
 */
public nomask float
query_spell_combat_aid()
{
    // Combat aid is modified by the modifier function.
    float modifier = query_spell_combat_aid_modifier();
    modifier = max(1.0, min(100.0, modifier));
    
    return Combat_aid * modifier / 100.0;
}

/*
 * Function:    query_spell_weapon_class_stat_influencer
 * Description: Allows for the customisation of the stat or stats
 *              that influence the strength of spells. This function
 *              should not be masked without approval by the AoB,
 *              and the use of multiple stats as influencer need to
 *              be averaged as if it were a single stat.
 */
public int
query_spell_weapon_class_stat_influencer()
{
   object caster = this_player();
   int stat_influencer = caster->query_stat(SS_INT);

   return stat_influencer;
}

/*
 * Function:    query_spell_weapon_class
 * Description: A spell's weapon class makes up the first argument
 *              of F_PENMOD when calculating spell strength.
 */
public nomask int
query_spell_weapon_class()
{
    int spell_wc = 0;
    // A Spell's WC (weapon class) is based on either skills and stats or
    // just the mana used. We use a logarithmic scale to "cap" the growth
    if (query_spell_at_will())
    {
        // At Will spells use the mana regen rate, which is based on
        // spellcasting and wisdom.
        int at_will_mana = get_at_will_spell_mana();
        int input_total = ftoi(13.0 * itof(at_will_mana) * 100.0 / AT_WILL_MANA_COST_FACTOR);
        send_debug_message("debug_spell_pen", "Spell weapon class total: " + input_total 
            + " calculated from at will mana usage " + at_will_mana + ".\n");
        spell_wc = ftoi(10.0 
            * log(itof(max(1, input_total))));
    }
    else
    {
        // Regular Spells use Skills and Stats.
        // From 0-250, use the log function multiplied by 7.246. 
        // So that at 250, the WC should be 40.
        // from 250-550+, each 15 points gives one WC point. 
        // So that at 550, the WC should be 60.
        object caster = this_player();

        // 1.5x intelligence used in standard calculation
        int intelligence = query_spell_weapon_class_stat_influencer() * 150 / 100; 
        int form_skill = caster->query_skill(Form_skill);
        int element_skill = caster->query_skill(Element_skill);
        int spellcraft_skill = caster->query_skill(SS_SPELLCRAFT);
        int input_total = (intelligence + form_skill + element_skill) * 
            min(60, spellcraft_skill) / 60;

        send_debug_message("debug_spell_pen", 
                               "Spell weapon class total: " + input_total 
            + " consists of " + intelligence + " (int*1.5) " + form_skill
            + " (form) " + element_skill + " (element), scaled by " + spellcraft_skill
            + " (spellcraft).\n");

        switch (input_total)
        {
            case 0..250:
                spell_wc = max(0, ftoi(log(itof(max(1, input_total))) * 7.246));
                break;            
            default:
                spell_wc = max(40, 40 + ftoi(itof(input_total - 250) / 15.0));
                break;
        }
    }
    
    /* There should be a cap to a reaasonable value here. But as the other scaling
     * values are wrong we disable the cap for now. */ 
    return min(80, spell_wc);
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

public nomask int
get_success_factor()
{
    // Pen calculations are adjusted according to the difficulty of
    // the cast. Using a resolve_task calculations, these are
    // the success rate for an average 200 modifier
    // TASK_EASY        - 100%
    // TASK_ROUTINE     - 97%
    // TASK_HARD        - 85%
    // TASK_DIFFICULT   - 65%
    // We cap increases at TASK_DIFFICULT.
    int task = get_spell_task();
    if (task >= TASK_DIFFICULT)
    {
        return 75; // success is 65%, we give 33% boost to power
    }
    else if (task >= TASK_HARD)
    {
        return 87; // success is 85%, we give 15% boost to power
    }
    else if (task >= TASK_ROUTINE)
    {
        return 95; // success is 97%, we give 3% boost to power
    }
    
    return 100;
}

/*
 * Function:    calc_stat_modifier
 * Description: Uses a caster's wisdom to return a valid modified
 *              to be used in F_STR_FACTOR calculations for spell
 *              pen.
 */
public nomask int 
calc_stat_modifier()
{
    object caster = this_player();
    // For spells, we allow them to scale 10% up/down depending on wisdom
    // maximum (F_STR_FACTOR(127) == 110). 
    int result = min(127, max(90, caster->find_drm( ({ TS_WIS }) ) / 2));
    return result;
}

/* 
 * Function:    calculate_pen
 * Description: Adjusts the pen according to the time it takes to
 *              cast and the combat aid and resistance specified.
 */
public nomask int
calculate_pen(int resist, int bAddLostCombatAid = 1)
{
    int weapon_class = query_spell_weapon_class();
    send_debug_message("debug_spell_pen", 
                           "Spell weapon class: " + weapon_class + ".\n");

    int guild_strength = min(100, query_spell_guild_strength());
    send_debug_message("debug_spell_pen", 
                           "Spell guild strength: " + guild_strength + ".\n");
    
    // Get the base pen for the spell's power rating.
    int result = F_PENMOD(weapon_class, guild_strength);
    send_debug_message("debug_spell_pen", 
                           "Base pen: " + result + ".\n");

    int stat_modifier = calc_stat_modifier();
    result = result * F_STR_FACTOR(stat_modifier) / 100;
    send_debug_message("debug_spell_pen", 
                           "Result after stat modifier applied: " + result + ".\n");
    
    // Modify pen by specified combat aid
    float caid = query_spell_combat_aid();    
    if (bAddLostCombatAid)
    {
        // When casting spells, you lose all normal attacks.
        float lost_caid = LOST_CAID_BOOST;

        if (query_spell_at_will())
        {
            // At will spells lose normal attacks during the 4 second prep time.
            // We add the extra combat aid here.
            lost_caid = LOST_CAID_BOOST * itof(MINIMUM_SPELL_TIME) / 
                itof(AT_WILL_SPELL_TIME);
        }

        send_debug_message("debug_spell_pen", sprintf("Adding %f lost CAID\n", lost_caid));
        caid += lost_caid;
    }
    
    result = ftoi(itof(result) * caid / 100.0);
    send_debug_message("debug_spell_pen", 
            "Result after " + ftoi(caid) + " CAID applied: " + result + ".\n");
    
/*
    // Modify pen by time for the spell
    int time_factor = MINIMUM_SPELL_TIME; // minimum spell time is 4
    if (query_spell_at_will())
    {
        time_factor = AT_WILL_SPELL_TIME; // at will spells are 15 seconds
    }
    // Modify by query_spell_time_factor
    mixed time_multiplier = query_spell_time_factor();
    if (floatp(time_multiplier))
    {
        time_factor = max(1, ftoi(itof(time_factor) * time_multiplier));
    }
    else if (intp(time_multiplier))
    {
        time_factor = max(1, time_factor * time_multiplier);
    }
*/  
    int time_factor = query_ability_prep_time() + query_ability_cooldown_time();
    result = (result * time_factor) / 5;
    send_debug_message("debug_spell_pen", 
                           "Result after time_factor " + time_factor + " applied: " + result + ".\n");
    
    // Modify pen by the difficulty of the spell
    result = result * 100 / get_success_factor();
    send_debug_message("debug_spell_pen", 
                            "Result after difficulty applied: " + result + ".\n");
    
    /**************************************************************************
     * Calculation has been moved to the resist file, function named:
     *          'spell_resist_modify_value'
     *
     * 2017-11-12: Carnak
     **************************************************************************
     * Modify pen by the resistance
     */
    result = spell_resist_modify_value(result, resist);

    send_debug_message("debug_spell_pen", 
                            "Result after resistance " + resist + " applied: " + result + ".\n");

    /**************************************************************************
     * Statement has been moved to the resist file and added to the function:
     *          'spell_resist_modify_value'
     *
     * 2017-11-12: Carnak
     **************************************************************************
     * One final modification to pen is to match non-magic calculation inside
     * of cb_hit_me, using F_NEW_DAMAGE formula. We multiply the resistance by 80%
     * make make that the chance that the pen goes to 0
     *
     * if (random(100) < (resist * 80 / 100))
     * {
     *     result = 0;
     * }
     * send_debug_message("debug_spell_pen", 
     *                    "Result after checking whether resistance cancels damage : " + result + ".\n");
     */
    return result;
}

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
 * Function:    query_spell_power
 * Description: A generic power calculation function that takes into
 *              account skills, stats, and guild strength
 */
public int
query_spell_power()
{
    int weapon_class = query_spell_weapon_class();
    int guild_strength = min(100, query_spell_guild_strength());
    
    return F_PENMOD(weapon_class, guild_strength);
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
        spell->set_spell_effect_element(Element_skill);
        spell->set_spell_effect_form(Form_skill);
        spell->set_spell_effect_caster(caster);
        spell->set_spell_effect_target(target_arr[i]);
        spell->set_spell_effect_power(query_spell_power());
        spell->set_spell_effect_input(input);
        
        if (!spell->setup_spell_effect())
        {
            spell->remove_object();
            obs[i] = 0;
        }
        
        if (objectp(obs[i]))
        {
            // Move the spell object to the target
            obs[i]->move(target_arr[i], 1);
            
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

// DEBUG FUNCTIONS

public float
test_resolve_task_percentage(int task, object player = this_player())
{
    int iterations = 1000;
    int successes = 0;
    
    for (int i = 0; i < iterations; ++i)
    {
        if (player->resolve_task(task, ({ SKILL_VALUE, 200 }) ) > 0)
        {
            ++successes;
        }
    }
    
    return itof(successes) / itof(iterations);
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

/*
 * Function:    set_ability_time
 * Description: This function should never get called directly.
 */
private nomask void
set_ability_time(int seconds)
{
    ::set_ability_time(seconds);
}

/*
 * Function:    set_ability_time
 * Description: This function should never get called directly.
 */
private void
set_ability_prep_time(int seconds)
{
    ::set_ability_prep_time(seconds);
}

/*
 * Function:    set_ability_time
 * Description: This function should never get called directly.
 */
private void
set_ability_cooldown_time(int seconds)
{
    ::set_ability_cooldown_time(seconds);
}
