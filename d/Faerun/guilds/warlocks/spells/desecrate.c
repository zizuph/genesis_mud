/*
 * Desecrate - Sacrificial spell for Warlocks
 * By Nerull, 2018
 * 
 * Updated to inherit from /d/Genesis/specials/new/magic/
 * Arman (AoB) December 2021
 */

#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include "../guild.h"

#include "/d/Genesis/specials/local.h"
inherit SPELL_DIR + "centralized_spell";

#include "/d/Genesis/specials/new/magic/spells/centralized_spell_restrictions.h"

// Prototypes
public void resolve_desecration_spell(object caster, mixed * targets, int *
resist, int result);
 
public string *
query_desecration_ingredients(object caster)
{
    return ({ });
}

public nomask void
config_spell()
{
    ::config_spell();
    
    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    set_spell_stationary(1);

    set_spell_name("ngzaench");
    set_spell_desc(" - Desecrate: Destroys a magical armor/weapon for its "
    +"magical energy");

    set_ability_stats(STAT_WEIGHTING);
    set_spell_class(SPELL_CLASS_1);

    set_spell_task(TASK_SIMPLE);
    set_spell_time(4);
    set_spell_target(spell_target_one_present_non_living);
    set_spell_ingredients(query_desecration_ingredients);
    
    set_ability_target_verify(spell_verify_present);
   
    set_spell_element(SS_ELEMENT_AIR, 30);
    set_spell_form(SS_FORM_ENCHANTMENT, 30);
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
            if (WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name()))
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
            if (WARLOCK_MASTER->is_patr2_warlock(this_player()->query_name()))
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
    
    if (IS_LIVING_OBJECT(target))
    {
        caster->catch_tell("You can only use this spell on magical pieces of "
        +"armor, and not living creatures.\n");
        
        return 0;
    }
    
    return 1;
}


/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                mixed *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, mixed * targets, int * resist, int result)
{
    resolve_desecration_spell(caster, targets, resist, result);
    
    setuid();
    seteuid(getuid());
    
    object target = targets[0];
    
    if (target->query_prop(OBJ_I_IS_MAGIC_ARMOUR) 
        || target->query_prop(OBJ_I_IS_MAGIC_WEAPON))
    {
    
        caster->catch_msg("You stretch out your arms at the "
        +target->query_short()+" and start to "
        +"extract the magical energies with the powers of your "
        +"patron! The magical energies pours into "
        +"your mind and body like a torrent. The "
        +target->query_short()+" withers and "
        +"erodes away into nothingness!\n");
        
        tell_room(environment(caster), QCTNAME(caster) + " stretches out "
        +caster->query_possessive()+" hands at the "+target->query_short()+", "
        +"which immediately withers away into "
        +"nothingness!\nThe mad eyes of "+QCTNAME(caster)+" flare "
        +"with magical energies.\n", caster);
        
        target->remove_object();
        
        if (WARLOCK_MAPPINGS->query_desecration_power(this_player()->query_name()) >= SPELL_END)
        {
            clone_object(WARLOCK_GUILDDIR 
            + "obj/sacrifice_cooldwn_obj")->move(caster, 1);
            
            return;
        }
        
        // Warlock is already primed. We just destroy the object
        if (WARLOCK_MAPPINGS->query_desecration_primer(caster->query_name()) == 0)
        {
           // We prime the warlock, and destroy the object.
            WARLOCK_MAPPINGS->set_desecration_primer(caster->query_name(), 1);
            
            caster->catch_tell("\n\nYou feel that you are "
            +"now primed for a new ritual!\n\n");
            
            clone_object(WARLOCK_GUILDDIR 
            + "obj/sacrifice_cooldwn_obj")->move(caster, 1);
            
            return;
        }
        
        clone_object(WARLOCK_GUILDDIR 
        + "obj/sacrifice_cooldwn_obj")->move(caster, 1);
        
        return;
    }
    
    caster->catch_msg("You stretch out your arms at the "
    +target->query_short()+" and try to "
    +"extract the magical energies with the powers of your "
    +"patron, except that there are none to be found!\nYou "
    +"are rather disappointed.\n");
        
    tell_room(environment(caster), QCTNAME(caster) + " stretches out "
    +caster->query_possessive()+" hands at the "+target->query_short()+", "
    +"but nothing happens.\nThe mad eyes of "+QCTNAME(caster)+" looks "
    +"rather disappointed.\n", caster);
        
    return;
}


// HOOKS TO BE DEFINED
/*
 * Function:    resolve_sanctify_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_desecration_spell(object caster, mixed * targets, int * resist, int
result)
{
}


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
        "power from them as you prepare to Desecrate.\n";
    
    watcher_message = "Flickering shadows gather around "+QTNAME(caster)+
        " as "+targets[0]->query_pronoun()+" seems to concentrate deeply.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}
