
/* Diarroae Object
 *
 * This is just to make sure players don't 'stack' slowness with this spell.
 * Conjured by the Diarroae (Slow) spell of the Windwalkers.
 *
 * Coded by Jaacar - May 22nd, 1998
 *
 */

#pragma strict_types

inherit "/d/Genesis/magic/spell_effect_object";
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>

varargs public int dispel_spell_effect(object dispeller);

void 
create_object()
{
    set_name("_diarroae_object_");
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
    set_spell_effect_desc("diarroae");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }
    spell_target->add_prop(LIVE_I_QUICKNESS,
        (int)spell_target->query_prop(LIVE_I_QUICKNESS) -100);

    set_alarm(60.0, 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->add_prop(LIVE_I_QUICKNESS,
        (int)spell_target->query_prop(LIVE_I_QUICKNESS) + 100);
    spell_target->catch_tell("Your muscles thaw to a point where "+
        "you can move again unhindered.\n");
    tell_room(environment(spell_target),QCTNAME(spell_target)+
        " appears to be moving normally again.\n",({spell_target}));

    remove_spell_effect_object();
    return 1;
}
