/*
 * Navarre, September 19th 2006.
 *
 * The object behind the Scop Elefrinisi spell.
 * (Relieve Burden)
 *
 */
inherit "/std/object";
inherit "/d/Genesis/newmagic/spell_effect_object";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Krynn/common/defs.h"

function orig_weight_function;

// Defines
#define FEATHERWEIGHT_FUNC_PROP     "_featherweight_functions"

// Global Variables
public mixed   original_weight_function = 0;
public int     Weight_factor = 140;

void
create_object()
{
    ::create_object();
    set_name("_scop_elefrinisi_obj");
    set_no_show();

    add_prop(OBJ_I_NO_STEAL, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(MAGIC_AM_MAGIC, ({"enchantment", 100}));
    add_prop(OBJ_S_WIZINFO, "The object behind the " +
                            "Scop confuse spell.\n");
}

/*
 * Function:    set_weight_factor
 * Description: Sets the weight factor to be used in granting more carrying capacity
 */
public void
set_weight_factor(int factor)
{
    Weight_factor = factor;
}

/*
 * Function:    query_weight_factor
 * Description: Returns the specified weight factor for this shadow
 */
public int
query_weight_factor()
{
    return Weight_factor;
}

public object
query_effect_target()
{
    return spell_target;
}

/*
 * Function:    query_original_weight_function
 * Description: Constructs the default max weight function that every
 *              living object has. This is the base from which we
 *              will build the additional weight calculations from.
 */
public function
query_original_weight_function() 
{
    object target = query_effect_target();
    if (!objectp(target)) 
    {
        return 0;
    }
    return mkfunction("max_weight", target);
}

/*
 * Function:    query_adjusted_max_weight
 * Description: Function that uses the original weight function
 *              and adds the weight factor on top of it.
 */           
public int
query_adjusted_max_weight()
{
    function f = query_original_weight_function();
    object target = query_effect_target();
    object * featherweight_objects = target->query_prop(FEATHERWEIGHT_FUNC_PROP);
    int adjusted_max_weight = f();
    if (!pointerp(featherweight_objects)) 
    {
        return adjusted_max_weight;
    }
    foreach (object featherweight_object : featherweight_objects)
    {
        if (!objectp(featherweight_object)) 
        {
            continue;
        }
        int weight_factor = featherweight_object->query_weight_factor();
        if (weight_factor != 0)
        {
            adjusted_max_weight = (adjusted_max_weight * weight_factor) / 100;
        }
    }
    return adjusted_max_weight;
}

varargs public int
dispel_spell_effect(object dispeller)
{
    spell_target->catch_tell("You feel the spirits retreat and " +
                             "you are once again alone to carry " +
                             "your burden.\n");
    tell_room(environment(spell_target), QCTNAME(spell_target) +
              " looks as if something is weighing " + 
              HIM(spell_target) + " down.\n", spell_target);

    object target = query_effect_target();
    // Look for any other featherweight objects to point the weight function at
    object * featherweight_objects = target->query_prop(FEATHERWEIGHT_FUNC_PROP);
    if (!pointerp(featherweight_objects))
    {
        target->add_prop(CONT_I_MAX_WEIGHT, query_original_weight_function());
        target->remove_prop(FEATHERWEIGHT_FUNC_PROP);
        remove_spell_effect_object();
        return 1;
    }

    featherweight_objects -= ({ this_object() });
    featherweight_objects -= ({ 0 });
    if (sizeof(featherweight_objects) == 0) 
    {
        target->add_prop(CONT_I_MAX_WEIGHT, query_original_weight_function());
        target->remove_prop(FEATHERWEIGHT_FUNC_PROP);
        remove_spell_effect_object();
        return 1;
    } 

    function f = mkfunction("query_adjusted_max_weight", featherweight_objects[0]);
    target->add_prop(CONT_I_MAX_WEIGHT, f);
    target->add_prop(FEATHERWEIGHT_FUNC_PROP, featherweight_objects);

    remove_spell_effect_object();
}


public int
start()
{
    int gstat, wis, bonus_weight;

    if (!::start())
    {
        remove_spell_effect_object();
        return 0;
    }
    spell_target->catch_msg("You feel as if a heavy burden has " +
                            "been lifted off your shoulders.\n");
    tell_room(environment(spell_target), QCTNAME(spell_target) +
             " looks as if a heavy burden has been lifted off " +
             HIS(spell_target) + " shoulder.\n", spell_target);

    // Now do the actual setting of the prop
    object target = query_effect_target();
    function f = &query_adjusted_max_weight();
    target->add_prop(CONT_I_MAX_WEIGHT, f);

    // Add this spell object to the list of featherweight objects
    object * featherweight_objects = target->query_prop(FEATHERWEIGHT_FUNC_PROP);
    if (!pointerp(featherweight_objects))
    {
        featherweight_objects = ({ });
    }
    featherweight_objects += ({ this_object() });
    target->add_prop(FEATHERWEIGHT_FUNC_PROP, featherweight_objects);
 
    gstat = spell_caster->query_stat(SS_OCCUP);
    wis = spell_caster->query_stat(SS_WIS);

    set_alarm(itof(900+3*(gstat+wis)), 0.0,
              &dispel_spell_effect(spell_target));

    return 1;
}
