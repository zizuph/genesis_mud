/*
 *
 * 
 */

#include <ss_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include <tasks.h>
#include <composite.h>
#include "../guild.h"

inherit "/d/Genesis/specials/std/spells/unfinished/aura";

/*
 * Function name:   calculate_dispel_time
 * Description:     Calculate the duration of the aura.
 * Arguments:       (object) spell_object - the spell object in question
 * Returns:         (int) - The duration of the spell effect
 */
public int
calculate_dispel_time(object spell_object)
{
    int d_time = 300;
    send_debug_message("aura_spell","Calculate the dispel time");
    return d_time; 
} /* calculate_dispel_time */


/*
 * Function name:   enter_environment
 * Description:     This function is called each time the shadowed enters a new
 *                  environment.
 * Arguments:       (object) spell_object - The spell object
 *                  (object) dest - the destination we are entering.
 *                  (object) old  - the location we came from. This can be 0.
 * Returns:         Nothing
 */
public void
enter_environment(object spell_object, object dest, object old)
{
    send_debug_message("aura_spell","Entered an Environment");
} /* enter_environment */


/*
 * Function name:   leave_environment
 * Description:     This function is called each time the shadowed leaves an
old
 *                  environment.
 * Arguments:       (object) spell_object - The spell object
 *                  (object) old  - the location we are leaving.
 *                  (object) dest - the destination we are going to. Can be 0.
 * Returns:         Nothing
 */
public void
leave_environment(object spell_object, object old, object dest)
{
    send_debug_message("aura_spell","Left an Environment");
} /* leave_environment */


/*
 * Function name:   meet_living
 * Description:     Tells us of new living entities in our vicinity.
 * Arguments:       (object) spell_object - The spell object
 *                  (object) met - The living met in the room
 *                  (object) affected - The one affected by the shadow
 * Returns:         Nothing
 */ 
public void
meet_living(object spell_object, object met, object affected)
{
    send_debug_message("aura_spell","Meet Living");
} /* meet_living */


/*
 * Function:    config_propchange_spell
 * Description: Config function for propchange spell. Redefine this in your
 *              own propchange spells to override the defaults.
 */
public void
config_aura_spell()
{
    set_spell_name("utest1");
    set_spell_desc(" - Aura1: Test aura 1");

    set_spell_element(SS_ELEMENT_AIR, 10);
    set_spell_form(SS_FORM_ABJURATION, 10);

    set_spell_vocal(1);
    set_spell_visual(0);
    set_spell_stationary(1);
    set_spell_peaceful(0);
    set_spell_offensive(0);

    set_spell_task(TASK_ROUTINE);

    set_spell_target(spell_target_caster);

    set_spell_can_be_renewed(1);
   
    // Not going to work.
    //set_shadow_filename(WARLOCK_SPELLOB_DIR + "auratest_sh");
}


/*
 * Function:    query_protect_dragonfear_ingredients
 * Description: This function defines what components are required for
 *              this spell.
 */
public string *
query_aura_ingredients(object caster)
{
    // If we are testing spells, no components
    /*if (SPELLTESTING_NOCOMPS == 1)
    {
        return ({ });
    }
    
    // Testing access
    if (present("_nerullian_object_", this_player()))
    {
        return ({ });
    }*/
    
    return ({ });
    
    //return ({ "_ascendstep_charge" });
}


/* 
 * Function:    set_input_parameters
 * Description: This function should be overridden by the spell to set
 *              the input parameters that should be passed to the shadow
 *              object.
 */
public void
set_input_parameters(object caster, mixed * targets, int * resist, int result,
mapping spell_input)
{
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
    
    if (WARLOCK_MASTER->is_lay_warlock(player->query_name()))
    {
        if (player->query_guild_level_lay() >= ASCENDSTEP_UNLOCK)
        {
            if (player->query_name() >= "nerjr")
            {
                return 1;
            }
            
            //return 0;
        }
    }

    /*if (WARLOCK_MASTER->is_lay_warlock(player->query_name()))
    {
        if (player->query_guild_level_lay() >= ASCENDSTEP_UNLOCK)
        {
            return 1;
        }
    }
    
    if (WARLOCK_MASTER->is_occ_warlock(player->query_name()))
    {
        if (player->query_guild_level_occ() >= ASCENDSTEP_UNLOCK)
        {
            return 1;
        }
    }*/

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
    
    return 1;
}


public void
hook_describe_cast_aura(object caster, object* targets)
{
    //caster->catch_tell("You cast a prop changeeee spell upon " +
      //                 COMPOSITE_LIVE(targets) + ".\n");
    //caster->tell_watcher(QCTNAME(caster) 
    //+ " casts a prop changeeee spell.\n", ({}) );
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

    caster_message = "As you surreptitiously whisper the long "
    +"forgotten words, the sounds reverberates in increasing "
    +"intensity, only to fade as you draw arcane powers from the "
    +"shadows!\n";
    
    watcher_message = "A chorus of eerie whispers permeate the area in "
    +"increasing intensity, only to fade again as "+QCTNAME(caster)
    +" turns inwards.\n";

    caster->catch_tell(caster_message);
    tell_room(environment(caster), watcher_message, ({ caster }), caster);

    setuid();
    seteuid(getuid());
}


/*
 * Function:    hook_already_has_spell_object
 * Description: Function that gets called to tell the caster that the spell is
 *              already in effect on the target and cannot be stacked.
 */
public void
hook_already_has_spell_object(object caster, object target)
{
    write("You are under the effect of Auratest already.\n");
}

/*
 * Function name:   hook_spell_effect_started
 * Description:     Override this to customize the message when this spell
 *                  effect is added to th target.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_spell_effect_started(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Your testaura of Doom starts.\n");
        
        tell_room(environment(target), QCTNAME(target) 
        + " starts radiating the testaura of Doom.\n", ({ target }));
    }
} /* hook_spell_effect_started */

/*
 * Function name:   hook_spell_effect_ended
 * Description:     Override this to customize the message when this spell
 *                  effect is dispelled.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_spell_effect_ended(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("Your testaura of Doom ends.\n");
        
        tell_room(environment(target), QCTNAME(target) 
        + " stops radiating the testaura of Doom.\n", ({ target }));
    }
} /* hook_spell_effect_ended */

/*
 * Function name:   hook_spell_effect_warn_fading
 * Description:     Override this to customize the message for when the effect
 *                  has only a minute left.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_spell_effect_warn_fading(object spell_object)
{
    object target = spell_object->query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("You sense your testaura of Doom "
        +"begins to fade.\n");
    }
} /* hook_spell_effect_warn_fading */

/* 
 * Function name:   hook_spell_effect_not_maintained
 * Description:     Override this to describe the effect when the caster cannot
 *                  maintain the effect.
 * Arguments:       (object) spell_object - The spell object
 * Returns:         Nothing
 */
public void
hook_spell_effect_not_maintained(object spell_object)
{
    object caster = spell_object->query_effect_caster();

    if (objectp(caster))
    {
        caster->catch_tell("You are mentally unable to maintain "
        + "the testaura of Doom.\n");
    }
} /* hook_spell_effect_not_maintained */