/*
 * Damage Modifier Shadow
 * 
 * This is a default shadow that allows damage mod objects to be added
 * to it in order to support multiple stacking damage mod effects
 *
 * Please see dam_mod_obj_base.c for functions defined.
 *
 * When damage is applied, the valid damage modifier effects will be
 * categorized based on their additivity into groups.  The group with the
 * highest damage modification will be used.
 *
 * Absorbtion and Amplification are calculated separately, and then combined
 * to give the final modification to the wpen.
 *
 * For implementation details, please see the function:
 * hit_me(int wcpen, int dt, object attacker, int attack_id, int target_hitloc = -1)
 * defined in this shadow.
 *
 * Created by Louie Oct 2008 
 *    Based heavily on evade shadow by Petros May 2008
 *
 * Modified on 2021-03-06 by Carnak:
 * - An attempt to fix the stacking and scaling of defensive abilities.
 */
 
#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include "defs.h"
inherit EFFECT_BASE_SH;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

/*
 * Function name:   query_effect_type
 * Description:     Returns the effect type with which we force this object
 *                  to stack.
 * Arguments:       None
 * Returns:         (string) The effect type
 */
public string
query_effect_type()
{
    return "defensive";
} /* query_effect_type */

private mixed
query_dam_mod_category(object effect)
{
    if (effect->query_dam_mod_exclusive())
        return file_name(effect);
    
    if (!effect->query_dam_mod_additive())
        return effect->query_name();
    
    return "additive";
} /* query_dam_mod_category */

private mapping
resolve_applicable_damage_modifications(mapping mod, object effect)
{
    mixed category = query_dam_mod_category(effect);
    
    if (member_array(category, m_indexes(mod)) < 0 ||
        !mappingp(mod[category]))
        mod[category] = ([]);
            
    object  target = effect->query_effect_target();
    int     incr = effect->query_effect_modified_combat_aid(target);
    
    if (member_array("effects", m_indexes(mod[category])) < 0 ||
        !pointerp(mod[category]["effects"]))
        mod[category]["effects"] = ({});
    
    mod[category]["effects"] += ({ effect });

    int perc = effect->query_effect_percentage(target);
    perc = perc < 0 ? 0 : perc;
    perc = perc > 99 ? 99 : perc;
    incr = (perc * 100) / (100 - perc) + (perc > 0 ? 1 : 0);
    
    if (!effect->query_dam_mod_absorb())
        incr -= incr * 2;
    
    mod[category]["total"] += incr;
    if (!mod["total_tally"] || abs(mod["total_tally"]) < abs(mod[category]["total"]))
    {
        mod["total_tally"] = mod[category]["total"];
        mod["tally"] = category;
    }
    
    return mod;
} /* resolve_applicable_damage_modifications */

private mapping
query_applicable_damage_modifications(object * effects)
{
    mapping absorb = ([]), amplify = ([]);
    
    foreach(object effect: effects)
    {
        if (effect->query_dam_mod_absorb())
            absorb = resolve_applicable_damage_modifications(absorb, effect);
        else
            amplify = resolve_applicable_damage_modifications(amplify, effect);
    }
    
    mapping applicable_dam_mod = ([
        "absorb" : ([]),
        "amplify" : ([])
    ]);
    
    if (absorb["total_tally"])
        applicable_dam_mod["absorb"] = absorb[absorb["tally"]];
    
    if (amplify["total_tally"])
        applicable_dam_mod["amplify"] = amplify[amplify["tally"]];
    
    return applicable_dam_mod;
} /* query_applicable_damage_modifications */

/*
 * Function     : has_dam_mod_shadow
 * Description  : Returns true always. Any person with this shadow
 *                will have this return true. That's how we will determine
 *                whether to create a new shadow or not
 * Arguments    : none
 * Returns      : 1 - true
 */
public int
has_dam_mod_shadow()
{
    return 1;
} /* has_dam_mod_shadow */

/*
 * Function     : remove_dam_mod_shadow
 * Description  : Easy way to remove shadow. Must use this otherwise the
 *                wrong shadow could be removed.
 * Arguments    : none
 * Returns      : nothing
*/
public void
remove_dam_mod_shadow()
{
    remove_shadow();
} /* remove_dam_mod_shadow */

/*
 * Function     : query_max_dam_mod_percentage
 * Description  : Returns the calculated percentage of all the damage mod
 *                objects that the damage mod shadow is currently keeping
 *                keeping track of. Only for the purpose of calculating
 *                maximum damage mod. The actual absorbtion depends on the
 *                situation in query_dam_mod_valid.
 * Arguments    : none
 * Returns      : the calculated stacking percentage
 */
public int 
query_max_dam_mod_percentage()
{
    return query_effect_percentage(query_effects());
} /* query_dam_mod_max_percentage */

/*
 * Function     : query_max_dam_mod_combat_aid
 * Description  : Based on the results of query_dam_mod_percentage
 *                This gives the total combat aid given by damage mod
 *                with the current effects.
 * Arguments    : none
 * Returns      : the calculated stacking combat aid
 */
public int
query_max_dam_mod_combat_aid()
{
    return query_effect_combat_aid(query_effects());
} /* query_dam_mod_max_combat_aid */

/*
 * Function     : remove_dam_mod_effect
 * Description  : Removes the effect from the list of effects
 * Arguments    : object to remove
 * Returns      : nothing
 */
public nomask void
remove_dam_mod_effect(object obj)
{
    remove_effect(obj);
    send_debug_message("dam_mod_sh", "Removing damage modifier effect " 
                     + obj->query_name() + ".");
} /* remove_dam_mod_effect */

/*
 * Function     : add_dam_mod_effect
 * Description  : Adds the damage modifier effect to the list of effects
 * Arguments    : object to add
 * Returns      : nothing
 */
public nomask void
add_dam_mod_effect(object obj)
{
    add_effect(obj);
    send_debug_message("dam_mod_sh", "Adding damage modifier effect " 
                     + obj->query_name() + ".");
    
} /* add_dam_mod_effect */

/* 
 * Function name:   query_dam_mod_effects
 * Description:     Returns the full list of effects currently being kept
 *                  track of by the damage modifier shadow
 * Arguments:       None
 * Returns:         (object *) array of damage modifier effect objects
 */
public object *
query_dam_mod_effects()
{
    return query_effects();
} /* query_dam_mod_effects */

private int
query_damage_modification_percentage(object* effects)
{
    int percentage = query_effect_percentage(effects);
    
    if (!percentage)
    {
        // We need to account for negative dam mod value
        percentage = min(query_effect_combat_aid(effects), 0);
    }
    
    return percentage;
} /* query_damage_modification_percentage */

/*
 * Function name:   hit_me
 * Description:     Called to make damage on this object. The actually
 *                  made damage is returned and will be used to change
 *                  the score of the aggressor.
 * Arguments:       wcpen         - The wc-penetration
 *                  dt            - damagetype, use MAGIC_DT if ac will not
 *                                  help against this attack.
 *                  attacker      - Object hurting us
 *                  attack_id     - Special id saying what attack hit us. If 
 *                                  you have made a special attack, let the 
 *                                  id be -1
 *                  target_hitloc - Optional argument specifying a hitloc
 *                                  to damage.  If not specified or an
 *                                  invalid hitloc is given, a random
 *                                  one will be used.
 * Returns:         The hitresult as given by the external combat object
 */
varargs public mixed 
hit_me(int wcpen, int dt, object attacker, int aid, int target_hitloc = -1)
{
    int oldwcpen, modifier;
    mixed results;
    
    object* valid_dam_mod_effects = ({ });
    
    if (wcpen > 0)
    {
        foreach(object effect : query_dam_mod_effects())
        {
            if (!effect)
            {
                // Just in case there's an invalid object
                continue;
            }
        
            if (!effect->query_dam_mod_valid(shadow_who, attacker, aid, dt))
            {
                continue;
            }
            
            valid_dam_mod_effects += ({ effect });
        }

        oldwcpen = wcpen;
        modifier = query_damage_modification_percentage(valid_dam_mod_effects);

        wcpen = oldwcpen * (100 - modifier) / 100;
        send_debug_message("dam_mod_sh", sprintf(
            "Modifier: %d, old pen %d, new pen %d",
            modifier, oldwcpen, wcpen));
    }

    results = shadow_who->hit_me(wcpen, dt, attacker, aid, target_hitloc);

    if (wcpen > 0 && modifier != 0 && random(100) < abs(modifier))
    {
        mapping applicable_dam_mod = 
            query_applicable_damage_modifications(valid_dam_mod_effects);
        
        object *effects = ({});
        if (modifier < 0)
            effects = applicable_dam_mod["amplify"]["effects"];
        else
            effects = applicable_dam_mod["absorb"]["effects"];
            
       // Randomly select an applicable damage modifier and use it to
        // report to the user
        if (sizeof(effects) > 0)
        {
            send_debug_message("dam_mod_sh", "Notifying player of modified "
                + "attack.\n");
            object effect = effects[random(sizeof(effects))];
            effect->attack_modified(shadow_who, attacker, aid);
        }
    }
    
    return results;
} /* hit_me */
