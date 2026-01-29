/*
 * Turn Undead Object - based on the Standard Blind Object
 *
 * This object gives the target a shadow that makes them
 * run away at the sight of the caster.
 *
 * Specific guild implementations can inherit this object and set it
 * it up to match their specific needs.
 *
 * Created by Jaacar, March 2017.
 */

#pragma strict_types

inherit "/d/Genesis/specials/new/magic/spells/objs/turn_undead_obj";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include "../../defs.h"

void 
create_spell_object()
{
    set_name("OotS_undead_turned_ob_");
    set_short("turn undead spell object");    
    set_long("This is the standard turn undead spell object. " +
             "It makes the target run away from the caster.\n");

    add_prop(OBJ_S_WIZINFO,"This is the spell object for the OotS, based on the Vekpos "+
        "spell of the Elemental Clerics guild. It is a turn" +
        " undead spell, and this object sets up a shadow in both the" +
        " target and caster, so the the target flees at the sight of" +
        " the caster for the duration.\n");
    set_spell_effect_desc("turn undead");
    
    set_dispel_time(200+random(60)); 
    
}

/*
 * Function:    hook_spell_effect_ended
 * Description: Override this to customize the message when this spell effect
 *              is dispelled.
 */
public void
hook_spell_effect_ended()
{
    object target = query_spell_effect_target();
    object caster = query_spell_effect_caster();

    if (objectp(caster))
    {
        target->catch_tell("Your fear of " + caster->query_the_name(target) +
            " subsides.\n");
        
        caster->catch_tell("You sense that the righteous intervention " +
            "against " + target->query_the_name(caster) +" is now gone.\n");
    
    } 

    setuid();
    seteuid(getuid());
            
    target->remove_turn_undead_shadow();
    caster->remove_turn_undead_caster_shadow();
}
