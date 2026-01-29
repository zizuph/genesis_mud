/*
 * Quickness effect for the phoenix_axe.c
 *
 * Coded by Arman 2021.
 */
 
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "/d/Krynn/common/defs.h"

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
    set_spell_name("windspeed");
    set_spell_desc("Phoenix blessings - the speed of the wind");

    set_spell_element(SS_ELEMENT_AIR,  0);
    set_spell_form(SS_FORM_TRANSMUTATION, 0);
    set_spell_task(TASK_SIMPLE);

    set_spell_fail("Your praise goes unheard.\n");

    set_spell_time_factor(0.5);
    set_spell_mana_factor(5.0);

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
    set_spell_combat_aid(15.0);

    // Can only cast haste on themself
    set_spell_target(spell_target_caster);

    // Spell effect object
    set_spell_object("/d/Krynn/turbidus_ocean/spells/phoenix_axe_haste_obj");
}

/*
 * Function:    query_haste_ingredients
 * Description: This function defines what components are required for
 *              this haste spell.
 */
public string *
query_haste_ingredients(object caster)
{
    return ({ });
}


/* 
 * Function:    set_input_parameters
 * Description: This function should be overridden by the spell to set
 *              the input parameters that should be passed to the shadow
 *              object.
 */
public void
set_input_parameters(object caster, mixed * targets, int * resist, int result, mapping spell_input)
{
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

    return 1;
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

    caster_message = "You praise the Blue Phoenix, Habbakuk, and your " +
        "phoenix-bladed axe glows a brilliant blue!\n";
    watcher_message = QCTPNAME(caster) + " phoenix-bladed axe suddenly " + 
        "glows a brilliant blue.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}

int
filter_tool(object obj)
{
      if (obj->id("_blue_phoenix_axe"))
        return 1;
      else 
        return 0;
}

public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    object *weapon;

    if(caster->query_tool(-1))
      weapon = filter(caster->query_tool(-1), filter_tool);  

    if(!sizeof(weapon))
    {
        caster->catch_tell("You need to wield the phoenix-bladed axe to " +
            "activate it.\n");
        return 0;
    }

    if(!weapon[0]->query_wielded())
    {
        caster->catch_tell("You have to be wielding the phoenix-bladed axe to " +
            "activate it.\n");
        return 0;
    }

    if(caster->query_skill(SS_SPELLCRAFT) < 20)
    {
        caster->catch_tell("You try and persuade the phoenix-bladed axe to " +
            "do something by praising the Blue Phoenix, but nothing seems to happen. " +
            "You likely need more spellcraft skill to be able to activate the " +
            "enchantment of this weapon.\n");
        return 0;
    }
  
    return 1;
}
