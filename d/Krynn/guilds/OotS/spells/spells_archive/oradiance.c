/*
 * Light spell for OotS
 *
 * Coded by Arman 2017.
 */
 
#pragma strict_types

inherit "/d/Genesis/specials/std/spells/light";

#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include <ss_types.h>
#include <files.h>
#include "../defs.h"
#include "/d/Krynn/common/defs.h"

#include "../oots_god_descs.h"


/*
 * Function:    config_light_spell
 * Description: Config function for light spells. Redefine this in your
 *              own light spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_light_spell()
{
    set_spell_name("oradiance");
    set_spell_desc("Radiance - a spell of divine illumination");

    // We set defaults for the spell element and form here. 
    // Each spell should customize these to their specific guild
    // skills.
    set_spell_element(SS_ELEMENT_LIFE,  20);
    set_spell_form(SS_FORM_TRANSMUTATION, 20);
    set_spell_task(TASK_ROUTINE);
    set_spell_fail("You fail in your efforts to invoke the prayer.\n");

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(0);
    set_spell_peaceful(0);
    set_spell_offensive(0);
    set_spell_can_be_renewed(1);
   
    set_spell_object(OOTS_SPELL_OBJS + "oradiance_obj");
}



/*
 * Function:    query_light_ingredients
 * Description: This function defines what components are required for
 *              this light spell.
 */
public string *
query_light_ingredients(object caster)
{
    return ({ });
}

/*
 * Function:    query_spell_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used 
 *              in messages to casters about what is actually required
 *              for this spell.
 */
public string
query_spell_ingredients_description()
{
    return "no prayer components";
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

    // Level 3 (Faithful) spell
    if(OOTS_LEVEL(player) < 1)
    {
        return 0;
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

        caster_message = "You raise your medallion of faith and call upon " 
              +oots_god_name(caster)+ " to disperse the darkness!\n";
        watcher_message = QCTNAME(caster) + " raises " +HIS(caster)+ 
              " medallion of faith and calls upon the " +
              oots_god_desc(caster)+ " " +oots_god_name(caster)+
              " to disperse the darkness!\n";

        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());  
}


public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
        return 0;

    if (caster->query_alignment() < 600)
    {
        caster->catch_tell("Your recent behaviours and actions do not " +
           "align with the teachings of " +oots_god_name(caster)+ 
           ". Your prayer goes unanswered.\n");
        return 0;
    }

    return 1;
}