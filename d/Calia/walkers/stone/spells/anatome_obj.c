
/* Anatome Object
 *
 * This is just to make sure players don't 'stack' resistance with this spell.
 * The actual resistance is done with a "/std/resistance" object.
 * Conjured by the Anatome (Earth Resistance) spell of the Stonewalkers.
 *
 * Coded by Jaacar - November 7th, 1998
 *
 */

#pragma strict_types

inherit "/d/Genesis/magic/spell_effect_object";
inherit "/std/object";

#include <stdproperties.h>

varargs public int dispel_spell_effect(object dispeller);

void 
create_object()
{
    set_name("_anatome_object_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
}

public int
start()
{
    set_spell_effect_desc("anatome");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    set_alarm(180.0, 0.0, dispel_spell_effect);
    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    remove_spell_effect_object();
    return 1;
}
