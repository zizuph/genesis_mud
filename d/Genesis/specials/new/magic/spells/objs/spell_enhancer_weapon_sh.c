/*
 *  Support shadow for the standard invisibility spell. Monitors attacks
 *  on and by the player and removes the invisibility effect.
 *
 *  Created by Eowul, July 2010
 */

#pragma strict_types
#pragma save_binary

#include <composite.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"

inherit SPELL_OBJ_DIR + "shadow_base_sh";

public object   spell_effect = 0;

static mapping ELEMENTS_TO_SKILLS =
  ([
    SS_ELEMENT_FIRE : "fire",
    SS_ELEMENT_WATER : "water",
    SS_ELEMENT_EARTH : "earth",
    SS_ELEMENT_AIR : "air",
    SS_ELEMENT_DEATH : "death",
    SS_ELEMENT_LIFE: "life" ]);


/*
 * Function     : has_spell_enhancer_shadow
 * Description  : Returns true always. Any person with this shadow
 *                will have this return true. That's how we will determine
 *                whether to create a new shadow or not
 * Arguments    : none
 * Returns      : 1 - true
 */
public int 
has_spell_enhancer_shadow() 
{
    return has_spell_shadow();
}

/*
 * Function     : remove_invisibility_shadow
 * Description  : Easy way to remove invisibility shadow. 
 * Arguments    : none
 * Returns      : nothing
*/
public void 
remove_spell_enhancer_shadow()
{
    remove_spell_shadow();
}

/*
 * Function:    initialize_shadow
 * Description: Called after first cloned. Should do all the initialization
 *              effects for this particular shadow.
 */
public void
initialize_shadow(object spell_object, mapping spell_input)
{
    spell_effect = spell_object;
    
    spell_object->set_spell_effect_desc("spell enhancer");
    spell_object->set_short("spell enhancer spell object");
}

public int is_spellpower_enhanceable_item()
{
    if (!shadow_who->query_prop(MAGIC_AM_MAGIC))
    {
        return 0;
    }
    if (!shadow_who->query_hit() || !shadow_who->query_pen())
    {
        return 0;
    }
    if (!objectp(spell_effect))
    {
        return 0;
    }
    return 1;
}

public int compute_magic_spellpower(int hit, int pen)
{
    int strength = (hit + pen);
    strength = strength * 7 / 16;
    return strength;
}

public int*
query_spellpower_elements()
{
    int* result = shadow_who->query_spellpower_elements();
    if (result) {
        return result;
    }
    if (!is_spellpower_enhanceable_item())
    {
        return result;
    }
    return ({ SS_ELEMENT_LIFE, 
              SS_ELEMENT_DEATH,
              SS_ELEMENT_AIR,
              SS_ELEMENT_FIRE,
              SS_ELEMENT_WATER,
              SS_ELEMENT_EARTH });
}



public int
query_magic_spellpower()
{
    int result = shadow_who->query_magic_spellpower();
    if (result)
    {
        return result;
    }
    if (!is_spellpower_enhanceable_item())
    {
        return result;
    }
    return compute_magic_spellpower(shadow_who->query_hit(), 
        shadow_who->query_pen());
}

public string get_element_spells()
{
    if (member_array(SS_ELEMENT_AIR, query_spellpower_elements()) >=0 &&
        member_array(SS_ELEMENT_FIRE, query_spellpower_elements()) >=0 &&
        member_array(SS_ELEMENT_WATER, query_spellpower_elements()) >=0 &&
        member_array(SS_ELEMENT_EARTH, query_spellpower_elements()) >=0 &&
        member_array(SS_ELEMENT_DEATH, query_spellpower_elements()) >=0 &&
        member_array(SS_ELEMENT_LIFE, query_spellpower_elements()) >=0)
    {
        return "spells of any element";
    }
    string* elements = ({});
    foreach(int element : query_spellpower_elements())
    {
        elements += ({ ELEMENTS_TO_SKILLS[element] });
    }
    return COMPOSITE_WORDS(elements) + " spells";
}


/*
 * Function name: item_spellpower_desc
 * Description:   String to be shown as part of the item appraisal.
 */
public string
item_spellpower_desc()
{
    string types = get_element_spells();
    
    return "\nThis weapon can be wielded to enhance " + types + ".\n";
}

/*
 * Function name: item_spellpower_desc
 * Description:   String to be displayed when an object is statted.
 */
string
stat_object_spellpower()
{
    return "Spell power: " + query_magic_spellpower() + ", elements: " 
        + get_element_spells() + "\n";
}

void appraise_object(int num)
{
    shadow_who->appraise_object(num);
    if (shadow_who->query_spellpower_enhancer())
    {
        return;
    }
    if (!is_spellpower_enhanceable_item())
    {
        return;
    }
    write(item_spellpower_desc());
}

string stat_object()
{
    string result = shadow_who->stat_object();
    if (shadow_who->query_spellpower_enhancer())
    {
        return result;
    }
    if (!is_spellpower_enhanceable_item())
    {
        return result;
    }
    return result + stat_object_spellpower();
}


/*
 * Function name: query_spellpower_enhancer
 * Description:   Check whether this object can enhance spells.
 */
public int
query_spellpower_enhancer()
{
    if (shadow_who->query_spellpower_enhancer())
    {
        return 1;
    }
    return is_spellpower_enhanceable_item();
}
