/*
 * Wounding Shadow
 * 
 * This is a default shadow that allows wounding objects to be added
 * to it in order to support wounding attacks. Bleeding wounds cannot
 * be healed by magic, and must clot on their own. Essentially this
 * means that a person hurt by wounds has to wait for the wounds to
 * heal and can have their "max" hp lowered while bleeding.
 *
 * Modifications:
 *   3/25/2009 - Changed so that wounding total is taken from the list of
 *               wounding effects instead.
 *   7/01/2020 - Added messaging for non-bleed enemies. Arman
 * 
 * Created by Petros, January 2009
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
#include <composite.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Defines
#define     WOUNDING_SUBLOC     "_wounding_subloc_name"
#define     LIVE_I_NO_BLEED     "_live_i_no_bleed"

// Prototypes
public object *     query_wounding_effects();

// Global Variables
public int      wounding_count; // track amount of damage before fatigue penalty
/*
 * Function     : has_wounding_shadow
 * Description  : Returns true always. Any person with this shadow
 *                will have this return true. That's how we will determine
 *                whether to create a new shadow or not
 * Arguments    : none
 * Returns      : 1 - true
 */
public int
has_wounding_shadow()
{
    return 1;
}

public int
query_wound_type(object bleeder)
{
    if(bleeder->query_prop(LIVE_I_UNDEAD) || 
        bleeder->query_prop(LIVE_I_NO_BODY) ||
        bleeder->query_prop(LIVE_I_NO_BLEED))
        return 1;
    else
        return 0;
}

/*
 * Function     : remove_wounding_shadow
 * Description  : Easy way to remove shadow. Must use this otherwise the
 *                wrong shadow could be removed.
 * Arguments    : none
 * Returns      : nothing
*/
public void
remove_wounding_shadow()
{
    string * wound_type_1 = ({ "bleeding", "weakened" });
    string * wound_type_2 = ({ "losing blood", "weakened" });
    int wound_type = query_wound_type(shadow_who);

    switch (random(2))
    {
    case 1:        
        shadow_who->catch_tell("You notice that your wounds have clotted "
            + "and you are no longer " +wound_type_1[wound_type] 
            + " from your wounds.\n");
        break;
    
    case 0:
    default:
        shadow_who->catch_tell("You feel relieved as you notice "
            + "you are no longer " +wound_type_2[wound_type]
            + " from your wounds.\n");
    }
    
    query_shadow_who()->remove_subloc(WOUNDING_SUBLOC);
    remove_shadow();
}

/*
 * Function     : remove_wounding_effect
 * Description  : Removes the effect from the list of effects
 * Arguments    : object to remove
 * Returns      : nothing
 */
public nomask void
remove_wounding_effect(object obj)
{
    remove_effect(obj);
    send_debug_message("wounding_sh", "Removing wounding effect " 
                     + obj->query_name() + " from " 
                     + capitalize(shadow_who->query_name()) + ".");
}

/*
 * Function     : add_wounding_effect
 * Description  : Adds the wounding effect to the list of effects
 * Arguments    : object to add
 * Returns      : nothing
 */
public nomask void
add_wounding_effect(object obj)
{
    string * locations;
    string hitloc_desc;
    string * wound_type_1 = ({ ", increasing the flow of blood from it", "" });
    string * wound_type_2 = ({ ", causing blood to flow freely from it", "" });
    int wound_type = query_wound_type(shadow_who);
    
    if (!sizeof(query_effects()))
    {
        // Adding a sublocation on the first time a wounding object
        // is added.
        query_shadow_who()->add_subloc(WOUNDING_SUBLOC, this_object());
    }
    
    locations = map(query_wounding_effects(), 
                    &->query_wounding_hitloc_desc());
    hitloc_desc = obj->query_wounding_hitloc_desc();
    if (IN_ARRAY(hitloc_desc, locations))
    {
        tell_room(environment(shadow_who), "The wound on "
            + QTPNAME(shadow_who) + " " + hitloc_desc + " rips open "
            + "further" +wound_type_1[wound_type]+".\n", 
            ({ shadow_who }));
    }
    else
    {
        tell_room(environment(shadow_who), "A wound opens on "
            + QTPNAME(shadow_who) + " " + hitloc_desc
            + wound_type_2[wound_type] + ".\n", ({ shadow_who }));
    }
            
    add_effect(obj);

    send_debug_message("wounding_sh", "Adding wounding effect " 
                     + obj->query_name() + " onto "
                     + capitalize(shadow_who->query_name()) + ".");
}

/*
 * Function     : query_wounding_effects
 * Description  : Returns the full list of effects currently being kept
 *                track of by the wounding shadow
 * Arguments    : none
 * Returns      : array of wounding effect objects
 */
public object *
query_wounding_effects()
{
    return query_effects();
}

public string
query_wounding_description()
{
    string * locations;
    string desc;
    
    locations = map(query_wounding_effects(), 
                    &->query_wounding_hitloc_desc());
    desc = COMPOSITE_WORDS(m_indices(mkmapping(locations, locations)));
    return desc;
}

/*
 * Function:    show_subloc
 * Description: The sublocation description is shown when you examine
 *              someone or examine yourself. For the wounding shadow,
 *              it should display the wounds that the person has.
 * Arguments:   subloc  - name of the sublocation to return string for
 *              on      - where the object is on
 *              for_obj - which object to display message to
 * Returns:     nothing
 */
public string
show_subloc(string subloc, object on, object for_obj)
{
    string data, desc;
    string * wound_type_1 = ({ "bleeding from", "weakened by" });
    int wound_type = query_wound_type(on);

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return shadow_who->show_subloc(subloc, on, for_obj);
    }
    
    if (subloc != WOUNDING_SUBLOC)
    {
        return shadow_who->show_subloc(subloc, on, for_obj);
    }
    
    if (for_obj == on)
    {
        if (sizeof(query_wounding_effects()) == 1)
        {
            return "You are "+wound_type_1[wound_type]+" a wound on your "
                + query_wounding_description() + ".\n";
        }
        return  "You are "+wound_type_1[wound_type]+" wounds on your "
            + query_wounding_description() + ".\n";
    }
    else
    {
        if (sizeof(query_wounding_effects()) == 1)
        {
            return (capitalize(on->query_pronoun())) + " is "
                +wound_type_1[wound_type]+" a wound on " 
                + on->query_possessive()
                + " " + query_wounding_description() + ".\n";
        } 
        return (capitalize(on->query_pronoun())) + " is "
            +wound_type_1[wound_type]+" from wounds on " 
            + on->query_possessive()
            + " " + query_wounding_description() + ".\n";
    }
}

public int
query_wounding_total()
{
    int total = 0;
    
    foreach (object effect : query_wounding_effects())
    {
        total += effect->query_damage_dealt();
    }
    
    return total;
}

public void
add_wounding_damage(int damage)
{
    int max_hp, max_with_wounding;
    string * wound_type_1 = ({ "from the loss of blood", 
        "from the damage caused by your wound" });
    int wound_type = query_wound_type(shadow_who);
    
    wounding_count += damage;
        
    max_hp = shadow_who->query_max_hp();
    if (wounding_count > max_hp * 10 / 100)
    {
        wounding_count = 0;
        // Fatigue penalty for every 10% of health lost through
        // wounding.
        shadow_who->add_fatigue(shadow_who->query_max_fatigue() / 10);
        shadow_who->catch_tell("You feel tired "+wound_type_1[wound_type]+".\n");
    }
    
    // Since heal_hp from the savevars.c is called directly without going
    // through this shadow, we will reset the hp to its maximum allowed
    // whenever add_wounding_damage is added.
    max_with_wounding = max_hp - query_wounding_total();
    if (shadow_who->query_hp() > max_with_wounding)
    {
        shadow_who->heal_hp(max_with_wounding - shadow_who->query_hp());
    }
}

/*
 * Function name:   heal_hp
 * Description:     Increase the number of hitpoints with a few.
 * Arguments:       hp: The difference
 */
public void
heal_hp(int hp)
{
    int max_hp, current_hp, wounding_total;
    
    if (hp <= 0)
    {
        // Removing hit points isn't modified.
        shadow_who->heal_hp(hp);
        return;
    }
    
    // We check to see if we will heal past the max that they can
    // have with their current damage total.
    current_hp = shadow_who->query_hp();
    max_hp = shadow_who->query_max_hp();
    wounding_total = query_wounding_total();
    if ((current_hp + hp) > (max_hp - wounding_total))
    {
        send_debug_message("wounding_sh", capitalize(shadow_who->query_name())
            + " cannot heal beyond " + (max_hp - wounding_total)
            + " hit points.");
        hp = max_hp - wounding_total - current_hp;
        if (hp <= 0)
        {
            shadow_who->heal_hp(0);
            return;
        }
    }
    
    shadow_who->heal_hp(hp);   
}
