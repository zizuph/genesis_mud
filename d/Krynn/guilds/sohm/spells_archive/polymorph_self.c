/*
 * Greater magic shield for WoHS, based on the stoneskin spell 
 *
 * Coded by Arman 2016.
 */
 
#pragma strict_types

#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <stdproperties.h>
#include <flags.h>
#include "defs.h"
#include "/d/Krynn/common/defs.h"
#include CLOCKH

inherit "/d/Genesis/specials/std/spells/shapeshift";

public mapping  polymorph_mapping = ([
    "bear" : "/d/Genesis/race/shapeshift/wohs_polymorph_self_bear", 
    "cooshee" : "/d/Genesis/race/shapeshift/wohs_polymorph_self_cooshee",
    "stag" : "/d/Genesis/race/shapeshift/wohs_polymorph_self_stag",
    "dragon" : "/d/Genesis/race/shapeshift/wohs_polymorph_self_dragon",
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
    set_spell_name("thirkusio");
    set_spell_desc("Polymorph self - Assume the form of a powerful creature");

    set_spell_vocal(1);
    set_spell_visual(1);
    set_spell_stationary(1);
    set_spell_peaceful(1);
    set_spell_offensive(0);
    set_spell_fail("You attempt to polymorph yourself, but are unable to harness " +
        "the powers of transmutation adequately and the spell fails.\n");
    set_spell_element(SS_ELEMENT_EARTH, 50);
    set_spell_form(SS_FORM_TRANSMUTATION, 60);
    set_spell_task(TASK_HARD);    

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
    return ({ "shard_diamond", "grey willow" });
}


public int 
check_valid_action(object caster, mixed * targets, string arg, int execute = 0)
{
    if (!::check_valid_action(caster, targets, arg, execute))
    {
        return 0;
    }

    if(arg == "dragon" && (caster->query_guild_level_occ() < 4))
    {
        caster->catch_tell("You must be a wizard ranking of the Sixth " +
         "Circle before you can polymorph yourself into a dragon!\n");
       return 0;
    }

    if(arg == "cooshee")
    {
      if(caster->query_race() != "elf" && 
         caster->query_race_name() != "half-elf")
       {
          caster->catch_tell("Only elves and half-elves are able to polymorph " +
             "themselves into cooshee hounds.\n");
          return 0;
       }
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
    return SOHM_MANAGER->query_memorised_spell(player,"thirkusio_memorised");
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

    if(E(caster)->query_prop(ROOM_IN_AIR))
    {
        caster_message = "You extend yourself horizontally in the air, arms extended, " +
            "and utter powerful words of transformation, 'Thirku Sio!'\n";
        watcher_message = QCTNAME(caster) + " extends " + HIM(caster) + "self horizontally " +
           "in the air, arms extended, while uttering mystical words of magic.\n";
    }
    else
    {
        caster_message = "You lower yourself to one knee and utter powerful words of " +
            "transformation, 'Thirku Sio!'\n";
        watcher_message = QCTNAME(caster) + " lowers " + HIM(caster) + "self to one knee " +
           "while uttering mystical words of magic.\n";
    }
        
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

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed * ingredients_needed)
{
    write("You are missing a component to call upon the polymorph self transmutation!\n");
}

