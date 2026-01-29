/*
 * Consume - Sacrificial spell for Warlocks
 * By Nerull, 2018
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <tasks.h>
#include "../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "harm";


/*
* Function:    config_harm_spell
* Description: Config function for harm spells. Redefine this in your
*              own harm spells to override the defaults.
* Arguments:   Same as config_spell
* Returns:     Same as config spell
*/
public void
config_harm_spell()
{
    set_spell_name("yogshara");
    set_spell_desc(" - Consume: Consume the flesh and blood from a "
    +"baby/child/infants");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_1);

    set_spell_vocal(0);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(1);
    set_spell_combat_aid(240.0);
    set_spell_task(TASK_ROUTINE);

    set_spell_time_factor(1.0);

    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_CONJURATION, 30);
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
* Function:    query_harm_ingredients
* Description: This function defines what components are required for
*              this harm spell.
*/
public string *
query_harm_ingredients(object caster)
{
    return ({ });
}


public int
query_spell_can_be_learned(object player)
{
    setuid();
    seteuid(getuid());

    if (!objectp(player))
    {
        return 0;
    }

    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    // Testing access
    if (present("_nerullian_object_", this_player()))
    {
        return 1;
    }
    
    // If we are testing spells regardless of rank and selection.
    if (SPELLTESTING == 1)
    {
        return 1;
    }

    if (WARLOCK_MASTER->is_lay_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
        >= FULL_WARLOCK_UNLOCK)
        {
            if (WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
            {
                return 1;
            }
            
            return 0;
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(this_player()->query_name()))
    {
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name())
        >= FULL_WARLOCK_UNLOCK)
        {
            if (WARLOCK_MASTER->is_patr3_warlock(this_player()->query_name()))
            {
                return 1;
            }
            
            return 0;
        }
    }

    return 0;
}


public int
check_valid_action(object caster, mixed * targets, string arg, 
int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }
    
    object target = targets[0];
    
    if (present("sacrifice_cooldwn", caster))
    {
        caster->catch_tell("Too soon. This gift can't be used "
        +"yet. Be patient.\n");
        
        return 0;
    }

    if ((target->id("child")) || (target->id("baby")) || (target->id("infant")))
    {
    
        if (target->query_npc() == 0)
        {
            caster->catch_tell("You can only use this spell on non-sentient "
            +"beings.\n");
               
            return 0;
        }
        
        if (target->query_stat(SS_CON) > 31)
        {
            caster->catch_tell("The "+target->query_name()+" is too large "
            +"for this spell.\n");
            
            return 0;
        }
        
        return 1;
    }
    
    caster->catch_tell("You can only use this spell on "
    +"children, infants and babies.\n");
    
    return 0;
}


// HOOKS TO BE DEFINED


/*
* Function name: concentrate_msg
* Description:   Give messages indicating that spell concentration has begun
* Arguments:     1. (object)   The caster
*                2. (mixed *) The targets
*                3. (string)   The arguments passed to the "cast" command
*/
public void
concentrate_msg(object caster, mixed * targets, string arg)
{
    string caster_message, watcher_message;

    caster_message = "You gather shadows around you, drawing arcane "+
        "power from them as you prepare to Consume your victim!\n";
    
    watcher_message = "Flickering shadows gather around "+QTNAME(caster)+
        " as "+targets[0]->query_pronoun()+" seems to concentrate deeply.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}


/*
* Function name: desc_harm_damage
* Description:   Write out some text describing the damage done.  This can
*                be redefined for custom messages.
* Arguments:     object caster - the caster
*                object target - the target
*                mixed *result - return value from harm's hit_me.
*/
public void
desc_harm_damage(object caster, object target, mixed *result)
{
    string caster_message, target_message, watcher_message;    


    caster->catch_msg("You enter a frenzied bloodlust and violently tear "
    +"into the body of "+QTNAME(target)+" with your bare hands! You "
    +"greedily consume both flesh and blood in large "
    +"quantities!\n"+QTNAME(target)+" screams in "
    +"terrible agony when being eaten alive by you!\n");
    
    target->tell_watcher(QCTNAME(caster)+" suddenly enter a frenzied "
    +"bloodlust and violently tear into the body of "+QTNAME(target)+" "
    +caster->query_possessive()+" bare hands and greedily starts "
    +"consuming both flesh and blood from "+QTNAME(target)+"!\n"
    +QCTNAME(target)+" screams in terrible agony as "
    +target->query_pronoun()+" is being eaten alive!\n\nFor performing "
    +"this hideous act, your "
    +"alignment drops slightly!\n", 
    target, ({ caster, target }));
    
    target->set_hp(0);
    target->do_die();
    
    caster->eat_food(300);
    caster->set_alignment((caster->query_alignment() - 50));
    
    if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= SPELL_END)
    {
        clone_object(WARLOCK_GUILDDIR 
        + "obj/sacrifice_cooldwn_obj")->move(caster, 1);
            
        return;
    }
    
    // Warlock is already primed. We just destroy the object
    if (WARLOCK_MAPPINGS->query_desecration_primer(this_player()->query_name()) == 0)
    {
       // We prime the warlock, and destroy the object.
        WARLOCK_MAPPINGS->set_desecration_primer(this_player()->query_name(), 1);
        
        caster->catch_tell("\n\nYou feel that you are "
        +"now primed for a new ritual!\n\n");
        
        clone_object(WARLOCK_GUILDDIR 
        + "obj/sacrifice_cooldwn_obj")->move(caster, 1);
        
        return;
    }
    
    clone_object(WARLOCK_GUILDDIR 
    + "obj/sacrifice_cooldwn_obj")->move(caster, 1);
}


/*
* Function name: desc_harm_cast
* Description:   Describe casting of the spell, not including damage messages.
*                This can be redefined for custom messages.
* Arguments:     object caster - the caster
*                object target - the target
*/
public void
desc_harm_cast(object caster, object * targets)
{
    string caster_message, target_message, watcher_message;
    object target;

    target = targets[0];


    caster_message = "You greedily start focusing at "
    +QTNAME(target)+"!\n";

    target_message = QCTNAME(caster)+" .\n";

    watcher_message = QTNAME(caster)+" greedily starts focusing on "
    +QTNAME(target)+"!\n";

    caster->catch_msg(caster_message);
    target->catch_msg(target_message);
    caster->tell_watcher(watcher_message, targets, ({ caster }) + targets);
}


/*
* Function:    resolve_harm_spell
* Description: Called at the beginning of resolve_spell in order to perform
*              spell specific actions.
* Arguments:   Same as resolve_spell
*/
public void
resolve_harm_spell(object caster, object *targets, int *resist, int result)
{
}


/*
* Function name: hook_no_ingredients_fail
* Description:   Return the message that should be printed when the caster
*                doesn't have the right ingredients
* Returns:       The message to print.
*/
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You lack the necessary preparations to cast this spell!\n");
}
