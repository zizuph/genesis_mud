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
 */
 
#pragma strict_types
#pragma save_binary
#pragma no_inherit

#include "/d/Genesis/specials/defs.h"

inherit EFFECT_BASE_SH;

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <tasks.h>
#include <formulas.h>
#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define DAM_MOD_BASE ("/w/louie/open/neidar/dam_mod_obj_base")

private int Adjusted_wcpen = 0;

/* Function     : query_adjusted_wcpen
 * Description  : Returns the wpen as adjusted by this shadow.
 * Arguments    : None
 * Returns      : The current wpen (int)
 */
public int
query_adjusted_wcpen()
{
    return Adjusted_wcpen;
}

/* Function     : set_adjusted_wcpen
 * Description  : Sets the wcpen as adjusted by this shadow.
 * Arguments    : The new wcpen
 * Returns      : None
 */
public void
set_adjusted_wcpen(int i) 
{
    Adjusted_wcpen = i;
}

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
}

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
}

/*
 * Function     : query_dam_mod_percentage
 * Description  : Returns the calculated percentage of all the damage mod
 *                objects that the damage mod shadow is currently keeping
 *                keeping track of. Only for the purpose of calculating
 *                maximum damage mod. The actual absorbtion depends on the
 *                situation in query_dam_mod_valid.
 * Arguments    : none
 * Returns      : the calculated stacking percentage
 */
public int 
query_dam_mod_percentage()
{
    return query_effect_percentage();    
}

/*
 * Function     : query_dam_mod_combat_aid
 * Description  : Based on the results of query_dam_mod_percentage
 *                This gives the total combat aid given by damage mod
 *                with the current effects.
 * Arguments    : none
 * Returns      : the calculated stacking combat aid
 */
public int
query_dam_mod_combat_aid()
{
    return query_effect_combat_aid();
}

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
}

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
}

/*
 * Function     : query_dam_mod_effects
 * Description  : Returns the full list of effects currently being kept
 *                track of by the damage modifier shadow
 * Arguments    : none
 * Returns      : array of damage modifier effect objects
 */
public object *
query_dam_mod_effects()
{
    return query_effects();
}

/*
 * Function     :   categorize_dam_mod_effect
 * Description  :   Given a damage mod effect and a mapping of arrays of
 *                  damage mod effects, determine which array of effects
 *                  should contain the damage mod.
 *                  Potential groups:
 *                  - Base/Additive (effects that group with all other effects)
 *                  - Non-additive (effects that only group with other effects
 *                      of the same type)
 *                  - Exclusive (effects that do not group with any effect, 
 *                      even others of the same type)
 * Arguments    :   effect - The effect to categories
 *                  eff_map - a map of arrays of groups.
 *                  attacker - the attacker object
 *                  attack_id - attack id
 */
public void
categorize_dam_mod_effect(object effect, mapping eff_map, object attacker, int attack_id)
{
    //Object is valid, so add it to correct mapping
    //If it's additive, add it into the base
    if (effect->query_dam_mod_additive()) {
        if (!eff_map[DAM_MOD_BASE]) {
            eff_map[DAM_MOD_BASE] = ({effect});
        } else {
            eff_map[DAM_MOD_BASE] += ({effect});
        }
    } else {
        //Not additive, so it goes in its own slot.
        if (effect->query_dam_mod_exclusive()) {
            //If it's exclusive, only the best one is used
            string eName = effect->query_name();
            if (!eff_map[eName]) {
                eff_map[eName] = ({effect});
            } else {
                //See if new one is most powerful
                if (effect->query_dam_mod_strength(shadow_who,attacker,attack_id) >
                    eff_map[eName]->query_dam_mod_strength(shadow_who,attacker,attack_id)) {
                        eff_map[eName] = ({effect});
                }
            }

        } else {
            //It's not exclusive, so the same types stack
            string eName = effect->query_name();
            if (!eff_map[eName]) {
                eff_map[eName] = ({effect});
            } else {
                eff_map[eName] += ({effect});
            }
        }
    }
}

/*
 * Function     :   find_and_modify_by_best_effects
 * Description  :   Cycle through an array of arrays of damage mod effects, 
 *                  determining the best effect group (highest adjustment).
 *                  Apply the adjustment to the Adjusted_wpen variable.
 *                  This function is normally called once for the absorb
 *                  effects, and then once for the amplify effects.
 * Arguments    :   wcpen         - The wc-penetration
 *                  attacker      - Object hurting us
 *                  attack_id     - Special id saying what attack hit us. If 
 *                                  you have made a special attack, let the 
 *                                  id be -1
 *                  all_effects   - Array containing arrays of effect objects.
 * Returns      :   The array of effect objects which were used to modify
 *                  the Adjusted_wpen (best effect group).
 */
public mixed
find_and_modify_by_best_effects(int wpen, object attacker, int attack_id, mixed *all_effects)
{
    mixed *results = ({});

    if (!all_effects || !sizeof(all_effects) || wpen < 1)
        return results;

    int best_adjust = 0;

    shadow_who->catch_msg("dam mod sh: find_and_modify 1\n");
    //Go through all the groups, looking for the best group
    foreach(mixed effect_grp : all_effects)
    {
        shadow_who->catch_msg("dam mod sh: find_and_modify 2\n");
        int power = wpen;
        int adjust = 0;
        int total_adjust = 0;
        int absorb = effect_grp[0]->query_dam_mod_absorb();
        shadow_who->catch_msg("dam mod sh: find_and_modify 3\n");

        //For each group, combine the effects to get the total power
        //Basically:  wpen consecutively modified by each object
        foreach(object eff : effect_grp) {
            shadow_who->catch_msg("dam mod sh: find_and_modify 4.  power: "+
                eff->query_dam_mod_strength(shadow_who, attacker, attack_id));
            adjust = power * eff->query_dam_mod_strength(shadow_who, attacker, attack_id) / 100;
            shadow_who->catch_msg("dam mod sh: find_and_modify 5 adjust: "+adjust+"\n");
            //Track total adjustment made by this effect group
            total_adjust += adjust;

            if (absorb)
            {
                //absorbtion adjust reduces the power of the wpen
                power -= adjust;
            } else {
                //amplify adjust increases power of the wpen
                power += adjust;
            }
        }

        //If this effect group is currently most powerful, save it.
        if (total_adjust > best_adjust)
        {
            best_adjust = total_adjust;
            results = effect_grp;
        }
    }

    shadow_who->catch_msg("dam mod sh: find_and_modify 6\n");
    //Now modify the wpen in a positive or neg way depending on effect type
    int adj = query_adjusted_wcpen();
    if (sizeof(results))
    {
        if (results[0]->query_dam_mod_absorb()) 
        {
            //reduce damage for absorb
            shadow_who->catch_msg("dam mod sh: find_and_modify 7\n");
            set_adjusted_wcpen(adj - best_adjust);
        } else {
            //Increase it for amplify
            shadow_who->catch_msg("dam mod sh: find_and_modify 8\n");
            set_adjusted_wcpen(adj + best_adjust);
        }
    }

    shadow_who->catch_msg("dam mod sh: find_and_modify 9\n");
    return results;
}

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
hit_me(int wcpen, int dt, object attacker, int attack_id, 
        int target_hitloc = -1)
{
    /**************
    Here is how to handle multiple effects:
    - Calculate damage point modification for reductions/amplifications
        separately.
    - When calculating multiple modifications of the same type (negative or
        positive), simply apply the % chance in sequence.
        If there are 2 objs:  baseDam * obj1 % * obj2 %= result
        So if baseDam is 100 and both objs are 20% reductions:
            100 * .8 * .8 = 64 (a 36 point reduction)
    - After reductions/amplifications are calculated, merge the results
        to get the final damage.
        So if we have 1 dam amplification object of 15% it would be:
            100 * 1.15 = 115 (a 15 point amplification).
        To get the total of 2 20% reductions and 1 15% amplification would
        be:
            -(reduction) + (amplification) or
            -36 + 15 = -21.
        Applied to the base damage we end up with:
            100 + -21 = 79 damage actually applied after effects.
    *****************/

    int evade_percentage;

    mapping eff_absorb_map = ([ ]), eff_amplify_map = ([ ]);

    shadow_who->catch_msg("dam mod sh 1\n");
    foreach (object effect : query_dam_mod_effects())
    {
        if (!effect)
        {
            // Just in case there's an invalid object
            continue;
        }
        
        if (!effect->query_dam_mod_valid(shadow_who, attacker, attack_id, dt))
        {
            send_debug_message("dam_mod_sh", capitalize(effect->query_name())
                             + " was not valid damage modifier in this "
                             + "situation.");
            continue;
        }

        //Is this effect an absorbtion or amplification of damage?
        if (effect->query_dam_mod_absorb()) {
            categorize_dam_mod_effect(effect, eff_absorb_map, attacker, attack_id);
        } else {
            categorize_dam_mod_effect(effect, eff_amplify_map, attacker, attack_id);
        }
    }
    shadow_who->catch_msg("dam mod sh 2\n");

    //Now we have all the effects categorized.  Determine which to use
    //and the power.
    mixed *absorb_options = m_values(eff_absorb_map);
    mixed *amplify_options = m_values(eff_amplify_map);

    //Set the wpen to the incoming, and then adjust it 
    set_adjusted_wcpen(wcpen);
    shadow_who->catch_msg("dam mod sh 3\n");
    mixed *best_absorb = find_and_modify_by_best_effects(wcpen, attacker, attack_id, absorb_options);
    shadow_who->catch_msg("dam mod sh 4\n");
    mixed *best_amplify = find_and_modify_by_best_effects(wcpen, attacker, attack_id, amplify_options);

    send_debug_message("dam_mod_sh", "Incoming wcpen: "+wcpen+
        " Adjusted wcpen: "+query_adjusted_wcpen()+".");
    shadow_who->catch_msg("Incoming wcpen: "+wcpen+
        " Adjusted wcpen: "+query_adjusted_wcpen()+".\n");

    //Print messages from the objects
    foreach(object effect : best_absorb) 
    {
        effect->damage_modified(shadow_who, attacker, attack_id);
    }

    shadow_who->catch_msg("dam mod sh 5\n");
    foreach(object effect : best_amplify) 
    {
        effect->damage_modified(shadow_who, attacker, attack_id);
    }
    shadow_who->catch_msg("dam mod sh 6\n");
    return shadow_who->hit_me(wcpen, dt, attacker, attack_id, target_hitloc);
}
