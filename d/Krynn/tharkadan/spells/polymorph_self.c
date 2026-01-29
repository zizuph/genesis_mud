/*
 * Polymorph to dragon hatchling 
 *
 * Coded by Arman 2017.
 */
 
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include "/d/Krynn/guilds/sohm/defs.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

inherit "/d/Genesis/specials/std/spells/shapeshift";

public mapping  polymorph_mapping = ([
    "drake" : "/d/Genesis/race/shapeshift/thark_polymorph_self_hatchling",
]);

/*
 * Function:    config_shapeshift_spell
 * Description: Config function for shapeshift spells. Redefine this in your
 *              own shapeshift spells to override the defaults.
 * Arguments:   Same as config_spell
 * Returns:     Same as config spell
 */
public void
config_shapeshift_spell()
{
    set_spell_name("drakeform");
    set_spell_desc("Drakeform - assume the form of an juvenile drake");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    set_spell_element(SS_ELEMENT_EARTH, 0);
    set_spell_form(SS_FORM_TRANSMUTATION, 0);
    set_spell_task(TASK_ROUTINE);    

    set_shape_mapping(polymorph_mapping);

    // Spell effect object
    set_spell_object(SOHM_SPELL_OBJS + "polymorph_self_obj");
}

/*
 * Function:    query_shapeshift_ingredients
 * Description: This function defines what components are required for
 *              this shapeshift spell.
 */
public string *
query_shapeshift_ingredients(object caster)
{
    return ({  });
}


public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
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
    return 1;
}

// HOOKS TO BE DEFINED

/*
 * Function:    resolve_shapeshift_spell
 * Description: Called at the beginning of resolve_spell in order to perform
 *              spell specific actions.
 * Arguments:   Same as resolve_spell
 */
public void
resolve_shapeshift_spell(object caster, mixed * targets, int * resist, int result)
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

        caster_message = "You inhale the vapours exhaled from the maw " +
            "of the serpent figurine.\n";
        watcher_message = QCTNAME(caster) + " inhales vapours from " +
            "the maw of a serpent figurine.\n";
        
    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());    
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You have already changed forms!\n");
}

/*
 * Function:    hook_invalid_shape_specified
 * Description: Called when the user specifies an invalid shape name. The
 *              shapes should be specified in the shape_mapping.
 */
public void 
hook_invalid_shape_specified(object actor, string str) 
{
    if (!strlen(str))
    {
        actor->catch_tell("You need to specify a form that you wish to "
            + "polymorph into.\n");
        return;
    }
    actor->catch_tell("You cannot polymorph into a " + str + ".\n");
}


