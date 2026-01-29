/*
 * Shadow Veil Spell for SOHM
 *
 * Coded by Arman 2017.
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/shadow";

#define ACTIVE_ENCHANTMENT "_sohm_shadow_veil_active"
#define PROT_SPELL_OBJ(x, y)  (SOHM_SPELLS + "protect_" + x)->has_spell_object(y)

/*
 * Function:    config_shadow_spell
 * Description: Config function for shadow spells. Redefine this in your
 *              own shadow spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_shadow_spell()
{
    set_spell_name("sjachbuala");
    set_spell_desc("Shadow veil - an illusionary cloak of shadows " +
        "enhancing skills of stealth");

    set_spell_element(SS_ELEMENT_AIR,  40);
    set_spell_form(SS_FORM_ILLUSION, 40);
    set_spell_mana(30);
    set_spell_task(TASK_DIFFICULT);

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);

    // Can only cast on self
    set_spell_target(spell_target_caster);
   
    set_shadow_filename(SOHM_SPELL_OBJS + "shadow_veil_sh");
}


/*
 * Function:    resolve_shadow_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_shadow_spell(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
}

/*
 * Function:    query_shadow_ingredients
 * Description: This function defines what components are required for
 *              this shadow spell.
 */
public string *
query_shadow_ingredients(object caster)
{
    return ({ "shard_onyx", "brown slime" });
}


/*
 * Function:    query_spell_can_be_learned
 * Description: Place restrictions on whether this spell can be used
 *              by the guild member.
 */
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
    return SOHM_MANAGER->query_memorised_spell(player,"sjachbuala_memorised");
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
    object target = targets[0];

    caster_message = "You begin reciting magical words of shadows and " +
        "illusion, 'Sjach Buala!'\n";
    watcher_message = QCTNAME(caster) + " begins reciting shadowy " +
        "words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

   object tar = targets[0];

    if(PROT_SPELL_OBJ("fire", tar) || PROT_SPELL_OBJ("lightning", tar) || 
       PROT_SPELL_OBJ("poison", tar) || PROT_SPELL_OBJ("acid", tar) || 
       PROT_SPELL_OBJ("cold", tar))
    {
        caster->catch_tell("An elemental protection spell interferes " +
            "with your shadow illusion, causing it to fail.\n");
	return 0; 
    }
  
    return 1;
}