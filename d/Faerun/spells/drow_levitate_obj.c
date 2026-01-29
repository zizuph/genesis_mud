/*
 *  faerun/spells/drow_levitate_obj.c
 *
 *  This is the object which is cloned when the drow has successfully cast
 *  it's levitating spell
 *
 *  Created by Wully, 20-2-2004
 */

inherit "/d/Genesis/newmagic/spell_effect_object";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"
#include "defs.h"

varargs public int dispel_spell_effect(object dispeller);

/*
 * Function name: start
 * Description  : Start the spell effect
 */
public int start()
{
    // Start the effect
    set_spell_effect_desc("levitation");
    spell_target->set_drow_levitating(1);

    // Set an alarm to dispell it
    set_alarm(itof((120 * query_spell_effect_power()) / 100), 0.0, 
        dispel_spell_effect);

    return 1;
}

/*
 * Function name: dispell_spell_effect
 * Description  : Stop the effect
 */
varargs public int dispel_spell_effect(object dispeller)
{
    // Stop the drow from levitating
    if(objectp(spell_target))
    {
        spell_target->set_drow_levitating(0);
        tell_room(environment(spell_target),
            "\n" + QCTNAME(spell_target) + " floats back to the ground.\n\n", 
            spell_target);
        spell_target->catch_msg("You float back to the ground.\n\n");
    }

    remove_spell_effect_object();
    return 1;
}
