/*
 * Priests of Takhisis Blind Object.
 *
 * Created by Navarre, March 2010.
 */
#pragma strict_types
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

inherit "/d/Genesis/specials/std/spells/obj/blind_obj";

/*
 * Function:    create_spell_object
 * Description: Override this to customize properties for the spell object
 */
public void 
create_spell_object()
{
    set_name("_pot_blind_object_");
    set_short("pot blind spell object");    
    set_long("This is the pot blind spell object. " +
             "It blinds the target.\n");

    add_prop(OBJ_S_WIZINFO, "This is a spell object " +
                            "created by the pot blind spell.\n");
    set_spell_effect_desc("blind");
    
    set_dispel_time(300);
}

/*
 * Function:    hook_spell_effect_started
 * Description: Override this to customize the message when this spell effect
 *              is added to th target.
 */
public void
hook_spell_effect_started()
{
    object target = query_effect_target();

    if (objectp(target))
    {
      target->catch_tell("You feel a sharp pain in your eyes.\nYou have been blinded!\n");
    }    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_effect_target();

    if (objectp(target))
    {
        target->catch_tell("The pain in your eyes subside.\n");
    }
}
