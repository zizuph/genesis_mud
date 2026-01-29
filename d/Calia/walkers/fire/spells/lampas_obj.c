/* 
Spell object for the Firewalker spell, Lampas.
Coded by Bishop, June 21st, 1999.
*/

#pragma strict_types

inherit "/d/Genesis/magic/spell_effect_object";
inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>

varargs public int dispel_spell_effect(object dispeller);
public void lampas_remove_stun();

public int
start()
{
    int task, duration;

    duration = 40;

    duration += (spell_caster->resolve_task(TASK_ROUTINE + 100, ({SKILL_WEIGHT, 
        25, TS_WIS, SKILL_END, SKILL_WEIGHT, 75, TS_OCC, SKILL_END, SKILL_AVG, 
        SS_ELEMENT_FIRE, SS_FORM_CONJURATION, SKILL_END})) * duration) / 100;
    duration = min(max(duration, 20), 60);

    set_spell_effect_desc("blindness");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    spell_target->add_prop(LIVE_I_SEE_DARK,
        (int)spell_target->query_prop(LIVE_I_SEE_DARK) -10);
    spell_target->add_stun();

    set_alarm(itof(duration), 0.0, dispel_spell_effect);
    set_alarm(itof(duration/2), 0.0, &lampas_remove_stun());

    return 1;
}

void 
create_object()
{
    set_name("_lampas_obj_");
    set_no_show();
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);

    add_prop(OBJ_M_NO_DROP, 1); 
    add_prop(OBJ_M_NO_GIVE, 1); 
}

public void 
lampas_remove_stun()
{
    spell_target->remove_stun();
    spell_target->catch_msg("You recover from the shock of the flash of" +
        " light and are able to move again.\n");
}

varargs public int
dispel_spell_effect(object dispeller)
{
    if (objectp(spell_target)) 
    { 
        spell_target->add_prop(LIVE_I_SEE_DARK,
            (int)spell_target->query_prop(LIVE_I_SEE_DARK) + 10);
        spell_target->remove_stun();
        spell_target->catch_msg("You fully recover from the effects of the" +
            " flash of light, and regain your sight.\n");
    } 

    remove_spell_effect_object();

    return 1;
}
