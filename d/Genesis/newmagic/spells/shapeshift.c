/*
 *  /d/Genesis/newmagic/spells/shapeshift.c
 *
 *  Generic shape shifting spell. You can override the create_spell function
 *  to customize it to your needs. The only requirement is the call to the
 *  set_shapeshift_target function, which should be a file that resides in 
 *  the /d/Genesis/race/shapeshift directory, or the shapeshift will not be
 *  performed.
 *
 *  You can override the following functions to provide your own functionality:
 *
 *  hook_shapeshift_complete(object caster, object *targets) 
 *      Called after the shapeshift spell has been completed.
 *
 *  Created by Eowul, November 2008
 */ 
#pragma strict_types

#include <tasks.h>
#include <ss_types.h>

inherit "/d/Genesis/newmagic/spell";

// Variables
private string  shapeshift_target;

// Prototypes
public  void    set_shapeshift_target(string filename);
public  string  query_shapeshift_target();

/*
 * Function name: create_spell
 * Description:   Configure this spell.
 *
 * Note:          If you need to reset various spell settings on a per-casting
 *                basis (vary casting time based on the level of the caster,
 *                for instance), use config_spell().
 */
public void
create_spell()
{
    set_spell_name("shapeshift");
    set_spell_desc("Shapeshift into mouse form");
    set_spell_time(1);
    set_spell_mana(80);
    set_spell_task(TASK_ROUTINE);
    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_TRANSMUTATION, 10);
    set_spell_ingredients(({ }));
    set_spell_resist(spell_resist_beneficial);
    set_spell_target_verify(spell_verify_present);
    set_spell_target(spell_target_caster);
    set_shapeshift_target("/d/Genesis/race/shapeshift/mouse");
}

/*
 * Function name: set_shapeshift_target
 * Description  : Set the filename of the destination of the shapeshift
 * Arguments    : filename - the target filename
 */
public nomask void
set_shapeshift_target(string filename) 
{
    shapeshift_target = filename;
}

/*
 * Function name: query_shapeshift_target
 * Description  : Returns the filename of the shapeshift destination
 * Returns      : the filename
 */
public nomask string
query_shapeshift_target() 
{
    return shapeshift_target;
}

/*
 * Function name: hook_shapeshift_complete
 * Description  : Function called after the shapeshifting has been completed. 
 *              : Allows for messages to be written to the caster if he was
 *              : not the target of the shapeshift
 * Arguments    : caster - the caster
 *              : targets - the targets that got shapeshifted
 */
public void 
hook_shapeshift_complete(object caster, object *targets) 
{
}


/*
 * Function name: prepare_shapeshift
 * Description  : Setup the magic effect for the shapeshifting and let that do
 *              : it's work.
 * Arguments    : caster - the one casting the spell
 *              : target - the target of the spell
 *              : resist - the resistance to the spell
 *              : result - the success of the spell casting
 */
private nomask void
prepare_shapeshift(object caster, object spell_target, int resist, int result) 
{
    setuid();
    seteuid(getuid());

    object target = clone_object(shapeshift_target);
    if(!objectp(target)) {
        caster->catch_tell("There's a problem with the shapeshift target "
            + "for this spell. Please contact a wizard.\n");
        return;
    }    

    object effect = clone_object("/d/Genesis/newmagic/spells/shapeshift_obj");
    effect->set_player(spell_target);
    
    make_spell_effect_object(effect, caster, target, resist, result);  
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resists     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public nomask void
resolve_spell(object caster, object *targets, int *resists, int result)
{
    if(!stringp(shapeshift_target)) 
    {
        caster->catch_tell("Unable to find the target of the shapeshift, "
            + "notify a wizard.\n");
        return;
    }
    
    for(int i = 0; i < sizeof(targets); i++) {
        object target = targets[i];
        int resist = resists[i];
        
        prepare_shapeshift(caster, target, resist, result);
    }

    hook_shapeshift_complete(caster, targets);
}