/*
 * Flaming fist spell for SoHM
 *
 * Coded by Arman 2016.
 * 
 * Based on code by Petros, September 2009
 */
 
#pragma strict_types

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <formulas.h>
#include <wa_types.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Genesis/specials/std/spells/reflect";

/*
 * Function:    config_reflect_spell
 * Description: Config function for reflect spells. Redefine this in your
 *              own reflect spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_reflect_spell()
{
    set_spell_name("ixenchasid");
    set_spell_desc("Flaming fist - engulf your hands in burning fire");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_fail("Your attempt to cast the spell fails, fizzling harmlessly.\n");
    set_spell_element(SS_ELEMENT_FIRE, 50);
    set_spell_form(SS_FORM_TRANSMUTATION, 50);
    set_spell_task(TASK_HARD);    

    // Can only cast reflect on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_shadow_filename(SOHM_SPELL_OBJS + "flaming_fist_sh");

    // Configure the spell parameters
    set_allow_specials(1);
    set_allow_magic_attacks(0);
    set_excluded_target_hit_locations( ({ }) );

    // 40 caid 
    set_reflect_damage_combat_aid(40);
    set_reflect_damage_type(MAGIC_DT);
    // 50 chance of damage reflected
    set_reflect_damage_likelihood(50);
}

/*
 * Function:    query_reflect_ingredients
 * Description: This function defines what components are required for
 *              this reflect spell.
 */

public string *
query_reflect_ingredients(object caster)
{
    return ({ "fireweed" });
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if (targets[0] != caster
        || (strlen(arg) && lower_case(arg) != caster->query_real_name()))
    {
        caster->catch_tell("You can only cast flaming fist on yourself!\n");
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
    return SOHM_MANAGER->query_memorised_spell(player,"ixenchasid_memorised");
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

        caster_message = "You raise your hands before you and clench them into fists " +
           "while chanting 'ixen chasid'!\n";
        watcher_message = QCTNAME(caster) + " raises " +HIS(caster)+ " hands before " +
           HIM(caster)+ " and clenches them into fists while chanting words of magic.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are currently maintaining a spell that conflicts with the flaming fist " +
          "spell.\n");
}
