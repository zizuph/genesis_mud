/*
 * Haste Spell for SoHM
 *
 * Coded by Arman 2016.
 * 
 */
 
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

inherit "/d/Genesis/specials/std/spells/haste";

/*
 * Function:    config_haste_spell
 * Description: Config function for haste spells. Redefine this in your
 *              own haste spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */

public void
config_haste_spell()
{
    set_spell_name("temep");
    set_spell_desc("Haste - greatly increased movement speed in combat");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0); 
    set_spell_can_be_renewed(1);

    set_spell_combat_aid(45.0);
    set_spell_fail("Your attempt to cast haste fails, fizzling harmlessly.\n");
    set_spell_element(SS_ELEMENT_AIR, 50);
    set_spell_form(SS_FORM_ILLUSION, 60);
    set_spell_task(TASK_HARD);    

    // Can only cast haste on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_spell_object(SOHM_SPELL_OBJS + "haste_obj");
}

/*
 * Function:    query_haste_ingredients
 * Description: This function defines what components are required for
 *              this haste spell.
 */
public string *
query_haste_ingredients(object caster)
{
    return ({ "shard_topaz", "smooth camas" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(SOHM_MANAGER->too_many_spells_memorised(caster))
    {
        caster->catch_tell("You have more spells memorised than you are capable of " +
            "mentally handling. You need to balance your memorised spell list before " +
            "you can cast spells again.\n");
        return 0;
    }

    if (targets[0] != caster
        || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
        caster->catch_tell("You can only cast haste on yourself!\n");
        return 0;
    }

    /*Can't cast spell if using another 45 caid greater spell - gravity, dominate, and curse */

    object *target;

    if (sizeof(target = filter(targets[0]->query_stun_effects(),
        &operator(==)(, caster->query_real_name()) @ &->query_sohm_dominate())))
    {   
        if (target[0]->query_sohm_active())
        {
           caster->catch_tell("A domination enchantment interferes with your spell, " +
            "causing it to fail.\n");
            return 0;
        }
    }

    object tar = targets[0];

    if(tar->query_has_sohm_curse_shadow())
    {
        caster->catch_tell("A curse of uncertainty interferes with your spell, " +
            "causing it to fail.\n");
        return 0;
    }

    if("/d/Krynn/guilds/sohm/spells/gravity"->has_spell_object(tar))
    {
        caster->catch_tell("A burdening transmutation interferes with your spell, " +
            "causing it to fail.\n");
	return 0; 
    }
        
    return 1;
}

public int
query_spell_can_be_learned(object player)
{
    if (!objectp(player))
    {
        return 0;
    }
    
    if (player->query_npc())
    {
        // npcs can always learn the spell.
        return 1;
    }
    
    setuid();
    seteuid(getuid());
    return SOHM_MANAGER->query_memorised_spell(player,"temep_memorised");
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

        caster_message = "You close your eyes and whisper words of magic and " +
           "deception... the incantation increasing in speed with the beat of your heart.\n";
        watcher_message = QCTNAME(caster) + " closes " +HIS(caster)+ " eyes " +
           "and whispers spidery words of magic that gradually increases in speed.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}

/*
 * Function:    resolve_haste_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_haste_spell(object caster, mixed * targets, int * resist, int result)
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
    write("You are missing an ingredient to cast the haste spell.\n");
}

