/*
 * /d/Genesis/sepcials/new/magic/spells/obj/blind_effect_ob
 *
 * This is the actual effect object that causes the blind.  Its role
 * is to interact with the blind spell object, and send it messages
 * so that it may present the relevant text.
 *
 * July 2022, Zizuph: Initial version
 */
 
#include "/d/Genesis/specials/local.h"; 
inherit BLIND_OBJ_BASE;

#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

private object spell_effect_obj;

public object query_spell_effect_object()
{
    return spell_effect_obj;
}

public void set_spell_effect_object(object ob)
{
    spell_effect_obj = ob;
}

public void
hook_blind_begin(object actor, object target, object *effects)
{
    spell_effect_obj->hook_blind_begin(actor, target, effects);
} 

public void
hook_blind_ended(object actor, object target, object *effects)
{
    spell_effect_obj->hook_blind_ended(actor, target, effects);
} /* hook_blind_ended */

public void hook_blind_failed(object actor, object target)
{
    spell_effect_obj->hook_blind_failed(actor, target);
    spell_effect_obj->remove_object();
}

public int
remove_shadow_from_list(object obj)
{
    int result = ::remove_shadow_from_list(obj);
    spell_effect_obj->remove_spell_effect_object();
    return result;
}
