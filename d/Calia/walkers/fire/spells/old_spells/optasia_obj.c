
/* Night Vision Object

   Conjured by the Night Vision spell of the Firewalkers.

   Coded by Jaacar 

*/

inherit "/std/object";
inherit "/d/Genesis/magic/spell_effect_object";

#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "defs.h"
#include FIRE_HEADER

varargs public int dispel_spell_effect(object dispeller);

void 
create_object()
{
    set_name("vision_obj");
    add_name(NVISION_OBJ);
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
    set_spell_effect_desc("darkvision");

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }

    spell_target->add_prop(LIVE_I_SEE_DARK, 
        (int)spell_target->query_prop(LIVE_I_SEE_DARK) + 2);

    set_alarm(600.0, 0.0, dispel_spell_effect);

    return 1;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->add_prop(LIVE_I_SEE_DARK,
        (int)spell_target->query_prop(LIVE_I_SEE_DARK) - 2);
    spell_target->catch_msg("Your eyes return to normal.\n");
    tell_room(environment(spell_target),QCTNAME(spell_target)+
            "'s eyes return to normal.\n",({ spell_target }));
    remove_spell_effect_object();

    return 1;
}
