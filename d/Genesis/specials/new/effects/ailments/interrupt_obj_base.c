/*
 * Interrupt Effect Object
 * 
 * This is the base interrupt effect object that handles interruption of
 * abilities in conjunction with the interrupt shadow.
 *
 * To use the interrupt object, simply clone it, set its values and start the
 * object, if the interrupt is successful the start will return positive.
 * 
 * Example:
 * 
 *  object test = clone_object(INTERRUPT_BASE_OBJ);
 *  test->set_interrupt_combat_aid(15);
 *  test->set_interrupt_chance(70);
 *  test->set_interrupt_special(1);
 *  test->set_interrupt_spell(1);
 *  test->move(targets[0], 1);
 *  
 *  if (!test->start())
 *      set_alarm(0.0, 0.0, &stop_ability(actor));
 *
 * Keep in mind, any value not set, will be taken from the ability from which
 * you create the interrupt object. In the above example, set_interrupt_cooldown
 * has not been set, and is therefore taken from the special executing it.
 *
 * This has been implemented for the thieves at:
 *    /d/Krynn/solamn/thief/guild/specials/cheapshot.c
 *
 * Created by Carnak, Januari 2018
 *   (Adaptation of the effect object)
 */
 
#pragma strict_types

#include "defs.h"

inherit EFFECT_BASE_OBJ;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>

// Prototypes
public void         set_interrupt_combat_aid(int caid);
public void         set_interrupt_chance(int chance);
public int          query_interrupt_combat_aid(object player);

public void         hook_ability_unavailable();
public void         hook_ability_already_disabled();
public void         hook_ability_enabled();
public void         hook_ability_disabled();
public void         hook_ability_failed();
public void         hook_unable_to_start();

// Global Variables
static int          m_interruptChance = 100;
static int          m_interruptCooldown;
static int          m_expirationDate;
static status       m_interruptSpecial;
static status       m_interruptSpell;
static object       m_interruptAbility;
static object       m_interruptSpecial;
static string       m_interruptTarget;

/*
 * Function name:   safely_load_master_file
 * Description:     This safely loads the master file if it hasn't already
 *                  been loaded. Otherwise, it just returns the existing
 *                  master file. If the file is not loadable, then it
 *                  simply returns 0
 * Argument:        (string) filename - Filename of the file to load
 * Returns:         (object) : Loaded master file
 */
public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
} /* safely_load_master_file */


/*
 * Function name:   query_ability_name
 * Description:     Added to handle masking of NPC special_attack function if
 *                  an NPC doesn't have a real special attack.
 * Arguments:       None
 * Returns:         (string) - "special attack"
 */
public string
query_ability_name()
{
    return "special attack";
} /* query_ability_name */

/*
 * Function name:   query_active_abilities
 * Description:     Returns the active abilities on the target
 * Arguments:       (object) target - The target of the interrupt.
 * Returns:         (mapping) - A mapping of arrays of active abilities
 */
public mapping
query_active_abilities(object target)
{
    object *active_abilities = ({ }),
           *abilities = ({ });
    
    object temporary_player = this_player();
    set_this_player(target);
    
    foreach (string soul : target->query_cmdsoul_list())
    {
        foreach(string index, string value: soul->query_ability_map())
        {
            object ability = safely_load_master_file(value);
            
            if (!objectp(ability))
                continue;
            
            if (!ability->query_spell_combat_aid() &&
                !ability->query_combat_aid())
                continue;
            
            if (ability->query_ability_preparing(target))
                active_abilities += ({ ability });
            else
                abilities += ({ ability });
        }
    }
    
    set_this_player(temporary_player);
    return ([ "abilities" : abilities, "active" : active_abilities ]);
} /* query_active_abilities */

/*
 * Function name:   query_interrupt_ability
 * Description:     Returns the interrupt ability target
 * Arguments:       None
 * Returns:         (object) - The interrupted ability
 */
public object
query_interrupted_ability()
{
    return m_interruptAbility;
} /* query_interrupted_ability */

/*
 * Function name:   set_interrupt_target
 * Description:     Sets the target ability to interrupt, either name or file of
 *                  the ability.
 * Arguments:       (string) target - The interrupt ability target
 * Returns:         Nothing
 */
public void
set_interrupt_target(string target)
{
    m_interruptTarget = target;
} /* set_interrupt_target */

/*
 * Function name:   query_expiration_date
 * Description:     Returns the expiration timestamp for the ability interrupt
 * Arguments:       None
 * Returns:         (int) - The interrupt ability timestamp
 */
public int
query_expiration_date()
{
    return m_expirationDate;
} /* query_expiration_date */

/*
 * Function name:   set_expiration_date
 * Description:     Sets the expiration timestamp for the ability interrupt
 * Arguments:       (int) timestamp - The interrupt ability timestamp
 * Returns:         Nothing
 */
public void
set_expiration_date(int timestamp)
{
    m_expirationDate = timestamp;
} /* set_expiration_date */

/*
 * Function name:   query_interrupt_cooldown
 * Description:     Returns the interrupt ability cooldown.
 * Arguments:       None
 * Returns:         (int) - The interrupt cooldown time
 */
public int
query_interrupt_cooldown()
{
    return m_interruptCooldown;
} /* query_interrupt_cooldown */

/*
 * Function name:   set_interrupt_cooldown
 * Description:     Sets the interrupt ability cooldown.
 * Arguments:       (int) cooldown - The interrupt ability cooldown time
 * Returns:         Nothing
 */
public void
set_interrupt_cooldown(int cooldown)
{
    m_interruptCooldown = cooldown;
} /* set_interrupt_cooldown */

/*
 * Function name:   query_interrupt_special
 * Description:     Returns whether the interrupt can affect specials.
 * Arguments:       None
 * Returns:         (status) - The state of interrupting specials
 */
public status
query_interrupt_special()
{
    return m_interruptSpecial;
} /* query_interrupt_special */

/*
 * Function name:   set_interrupt_special
 * Description:     Determines whether the interrupt can affect specials.
 * Arguments:       (status) special - The status of interrupting specials
 * Returns:         Nothing
 */
public void
set_interrupt_special(status special)
{
    m_interruptSpecial = special;
} /* set_interrupt_special */

/*
 * Function name:   query_interrupt_spell
 * Description:     Returns whether the interrupt can affect spells.
 * Arguments:       None
 * Returns:         (status) - The state of interrupting spells
 */
public status
query_interrupt_spell()
{
    return m_interruptSpell;
} /* query_interrupt_spell */

/*
 * Function name:   set_interrupt_spell
 * Description:     Determines whether the interrupt can affect spells.
 * Arguments:       (status) spell - The status of interrupting spell
 * Returns:         Nothing
 */
public void
set_interrupt_spell(status spell)
{
    m_interruptSpell = spell;
} /* set_interrupt_spell */

/*
 * Function name:   create_interrupt_effect
 * Description:     The create function called for objects that inherit this
 * Arguments:       None
 * Returns:         Nothing
 */
public void
create_effect()
{
    setuid();
    seteuid(getuid());
    
    set_name("_base_interrupt_object_");
    add_name( ({"base_interrupt_obj" }) );
    set_short("hidden base interrupt object");    
    set_long("A basic interrupt object. One should not be able to see it "
           + "in their inventory.\n");
} /* create_effect */

/*
 * Function name:   set_interrupt_chance
 * Description:     Sets the chance that the interrupt will have effect.
 * Arguments:       (int) chance - The percentage between 0 and 100
 * Returns:         Nothing
 */
public nomask void
set_interrupt_chance(int chance)
{
    m_interruptChance = min(100, chance);
} /* set_interrupt_chance */

/*
 * Function name:   query_interrupt_chance
 * Description:     Returns the chance that the interrupt will succeed
 * Arguments:       (object) player - the player who is receiving combat aid
 * Returns:         (int) - combat aid number
 */
public nomask int
query_interrupt_chance(object player)
{
    int modifier;
    
    /* We need to modify the chance based on how long the cooldown is, so we
     * cant have a 1sec cooldown spammable ability interrupting everything.
     *
     * We base the minimum ability cooldown to 45 seconds before the chance
     * starts reducing.
     */
    modifier = min(m_interruptChance, (query_interrupt_cooldown() *
               m_interruptChance) / 45);
    
    /* Now we need to min max it so we keep it in check */
    return max(0, modifier);
} /* query_interrupt_chance */

/*
 * Function name:   set_interrupt_combat_aid
 * Description:     Sets the interrupt combat aid which is used to determine
 *                  the interrupt percentage
 * Arguments:       (int) caid - combat aid number
 * Returns:         Nothing
 */
public nomask void
set_interrupt_combat_aid(int caid)
{
    set_effect_combat_aid(caid);
} /* set_interrupt_combat_aid */

/*
 * Function name:   query_interrupt_combat_aid
 * Description:     Returns the interrupt combat aid for player
 * Arguments:       (object) player - the player who is receiving combat aid
 * Returns:         (int) combat aid number
 */
public nomask int
query_interrupt_combat_aid(object player)
{
    int percentage, chance;
    
    // The actual interrupt combat aid is modified by the interrupt chance
    percentage = ::query_effect_combat_aid(player);
    chance = query_interrupt_chance(player);
    
    if (chance > 0)
        percentage = percentage * 100 / chance;
    
    return percentage;
} /* query_interrupt_combat_aid */

/*
 * Function name:   query_effect_combat_aid
 * Description:     Returns the effect combat aid for player
 * Arguments:       (object) player - the player who is receiving combat aid
 * Returns:         (int) combat aid number
 */
public int
query_effect_combat_aid(object player)
{
    return query_interrupt_combat_aid(player);
} /* query_effect_combat_aid */

/*
 * Function name:   query_interrupt_valid
 * Description:     Validation function to see whether this interrupt object is
 *                  valid in the current situation
 * Arguments:       (object) player - player who is being attacked
 * Returns:         (int) 0/1 - invalid/valid
 */
public int
query_interrupt_valid(object player)
{
    return 1;
} /* query_interrupt_valid */

/*
 * Function name:   remove_interrupt_effect
 * Description:     Remove this interrupt from a target, also removing the
 *                  interrupt shadow as needed
 * Arguments:       (object) target - the one affected by the interrupt
 * Returns:         (int) 1/0 - effect dispelled/not dispelled
 */
varargs public int
remove_interrupt_effect(object target)
{
    if (!target)
    {
        // We only care if the environment is a living person.
        // Master objects will simply be removed.
        return 0;
    }
    
    // Remove the effect from the shadow
    target->remove_interrupt_effect(this_object());
    if (!sizeof(target->query_interrupt_effects())
        && target->has_interrupt_shadow())
    {
        target->remove_interrupt_shadow();
    }
    
    if (!target->query_ghost())
        hook_ability_enabled();
    
    return 1;
} /* remove_interrupt_effect */


/*
 * Function name: remove_object
 * Description:   Called upon object destruction. This will need to
 *                be done so that the shadow can be properly removed
 *                when there are no more effects.
 * Arguments:     none
 * Returns:       nothing
 */
public void
remove_object()
{
    foreach(object shadowobj: query_shadow_list())
    {
        remove_interrupt_effect(shadowobj->query_shadow_who());
    }
    
    ::remove_object();
}

/*
 * Function name:   dispel_effect
 * Description:     Cause this effect to be dispelled. If the effect is removed,
 *                  1 should be returned, else 0.  Returning 0 should be a rare
 *                  occurance, since there generally should not be spell effects
 *                  that cannot be dispelled.
 * Arguments:       (object) dispeler - the person responsible for dispelling
 *                  the effect.
 * Returns:         (int) 1/0 - effect dispelled/not dispelled
 */
varargs public int
dispel_effect(object dispeler)
{
    return !!remove_object();
} /* dispel_effect */

/*
 * Function name:   add_interrupt_effect
 * Description;     Add this effect to a target
 * Arguments:       (object) target
 * Returns:         (int) 1/0 - effect added/not added
 */
public int
add_interrupt_effect(object target)
{
    mapping ability_list = query_active_abilities(target);
    object  shadow_ob, *spells = ({}), *specials = ({}),
           *abilities = ability_list["abilities"],
           *active = ability_list["active"];
    query_effect_caster()->catch_msg("Add 0\n");    
    
    if (!objectp(m_interruptAbility))
    {
        if (query_interrupt_spell())
            spells = filter(active, &operator(!=)(,0) @ &->query_spell());
        
        if (query_interrupt_special())
            specials = filter(active, &operator(!=)(,1) @ &->query_spell());
        
        if (sizeof(specials) || sizeof(spells))
        {
            m_interruptAbility = one_of_list(spells + specials);
        }
        
        if (!objectp(m_interruptAbility))
        {
            if (!target->query_npc())
            {
                // There was no active ability to interrupt
                query_effect_caster()->catch_msg("Nothing to int?\n");    
                query_effect_target()->catch_msg("I am set too\n");    
                hook_ability_unavailable();
                remove_object();
                return 0;
            } else
                m_interruptAbility = this_object();
            
        }
    }
    query_effect_caster()->catch_msg("Add 1\n");    
    if (sizeof(abilities) > 1)
    {
        // Temporarily removing: m_interruptAbility == this_object() ||
        if ((!query_interrupt_spell() && m_interruptAbility->query_spell()) ||
            (!query_interrupt_special() && !m_interruptAbility->query_spell()))
        {
            hook_ability_unavailable();
            remove_object();
            return 0;
        }
    }
    query_effect_caster()->catch_msg("Add 2\n");    
    
    if (random(100) >= query_interrupt_chance(target))
    {
        // The interrupt chance did not succeed.
        hook_ability_failed();
        remove_object();
        return -1;
    }
    query_effect_caster()->catch_msg("Add 3\n");    
    
    if (target && living(target))
    {
        if (!target->has_interrupt_shadow())
        {
            if (!objectp(safely_load_master_file(INTERRUPT_SH)) ||
                !objectp(shadow_ob = clone_object(INTERRUPT_SH)) ||
                !shadow_ob->shadow_me(target))
            {
                remove_object();
                return 0;
            }
        }
        
        return target->add_interrupt_effect(this_object());
    }
    query_effect_caster()->catch_msg("Add 4\n");        
    return 0;
} /* add_interrupt_effect */

/*
 * Function name:   hook_ability_locked
 * Description;     This is called when an ability is locked.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_ability_locked()
{
    query_effect_target()->catch_msg("You have yet to recover from having your "
    + m_interruptAbility->query_ability_name() + " interrupted.\n");
} /* hook_ability_locked */

/*
 * Function name:   hook_ability_unavailable
 * Description;     There are no abilities available for interruption.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_ability_unavailable()
{
    query_effect_caster()->catch_msg(QCTNAME(query_effect_target()) + " is "
    + "not preparing any interruptible abilities.\n");
} /* hook_ability_unavailable */

/*
 * Function name:   hook_ability_already_disabled
 * Description;     The target ability is already disabled.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_ability_already_disabled()
{
    query_effect_caster()->catch_msg("The "
    + m_interruptAbility->query_ability_name()
    + " has already been disabled.\n");
} /* hook_ability_already_disabled */

/*
 * Function name:   hook_ability_enabled
 * Description;     This is called once the ability is enabled again.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_ability_enabled()
{
    object ability, player;
    
    player = this_player();
    set_this_player(query_effect_target());
    
    ability = query_interrupted_ability();
    ability->hook_special_complete();
    set_this_player(player);
} /* hook_ability_enabled */

/*
 * Function name:   hook_ability_disabled
 * Description;     This is called when the interrupt successfully disabled the
 *                  ability.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_ability_disabled()
{
    query_effect_caster()->catch_msg("You successfully interrupt "
    + QTNAME(query_effect_target()) + " from executing "
    + LANG_ADDART(m_interruptAbility->query_ability_name()) + ".\n");
    
    query_effect_target()->catch_msg("Your "
    + m_interruptAbility->query_ability_name()
    + " has been interrupted.\n");
} /* hook_ability_disabled */

/*
 * Function name:   hook_ability_failed
 * Description;     This is called when this fails to interrupt an ability.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_ability_failed()
{
    query_effect_caster()->catch_msg("You failed to interrupt "
    + QTNAME(query_effect_target()) + " from executing "
    + LANG_ADDART(m_interruptAbility->query_ability_name()) + ".\n");
    
    query_effect_target()->catch_msg(QCTNAME(query_effect_caster())
    + " attempted to interrupt your " + m_interruptAbility->query_ability_name()
    + ", but failed.\n");
} /* hook_ability_failed */

/*
 * Function name:   hook_unable_to_start
 * Description;     This is called when the start is unable to execute, this
 *                  could happen if values are missing, but most likely due to
 *                  the player writing the wrong target.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
hook_unable_to_start()
{
    query_effect_caster()->catch_msg("You seem unable to interrupt "
    + m_interruptTarget + ".\n");
} /* hook_unable_to_start */

/*
 * Function name:   start
 * Description;     Start up the spell effect. This should be redefined to
 *                  provide specific behaviour for a given spell effect.
 * Arguments:       None
 * Returns:         (int) -1: Ability failed.
 *                  (int)  0: Not able to execute.
 *                  (int)  1: Effect started.
 */
public nomask int
start()
{
    object  ability, *a_filter;
    mapping abilities;
    int     timed, value;
    
    /* Check if the calling ability is a timed ability */
    timed = member_array(TIMED_ABILITY_LIB + ".c",
            inherit_list(previous_object()));
    
    query_effect_caster()->catch_msg("Start 1.\n");
    if (!query_effect_target())
    {
        query_effect_caster()->catch_msg("Missing target??.\n");
    }
    
    /* Make sure that cooldown is set, or take the value from calling ability */
    if (!m_interruptCooldown)
    {
        if (timed < 0)
        {
            hook_unable_to_start();
            return !!remove_object();
        }
        
        if ((value = previous_object()->query_ability_time()) < 1)
        {
            hook_unable_to_start();
            return !!remove_object();
        }
        
        m_interruptCooldown = value;
    }
    query_effect_caster()->catch_msg("Start 2.\n");
        
    if (strlen(m_interruptTarget))
    {
        if (!objectp(ability = safely_load_master_file(m_interruptTarget)))
        {
            abilities = query_active_abilities(query_effect_target())["abilities"];
            
            if (!sizeof(a_filter = filter(abilities,
                &operator(==)(,m_interruptTarget) @ &->query_ability_name())) ||
                !objectp(ability = a_filter[0]))
            {
                hook_unable_to_start();
                return !!remove_object();
            }
        }
        
        m_interruptAbility = ability;
    }
    query_effect_caster()->catch_msg("Start 4.\n");
    
    return add_interrupt_effect(query_effect_target());
} /* start */