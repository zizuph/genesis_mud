#include <formulas.h>
#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <math.h>

#ifndef MAGIC_I_RES_HEALING
#define MAGIC_I_RES_HEALING "_magic_i_res_healing"
#endif

static mapping resistance_map = 
([
    SS_ELEMENT_FIRE  : MAGIC_I_RES_FIRE,
    SS_ELEMENT_WATER : MAGIC_I_RES_WATER,
    SS_ELEMENT_EARTH : MAGIC_I_RES_EARTH,
    SS_ELEMENT_AIR   : MAGIC_I_RES_AIR,
    SS_ELEMENT_DEATH : MAGIC_I_RES_DEATH,
    SS_ELEMENT_LIFE  : MAGIC_I_RES_LIFE,
]);

/*
 * Function name:   spell_resist_modify_value
 * Description:     This function modifies the specified value based on the
 *                  specified resistance, reducing or increasing it.
 * Arguments:       (int) value  - value to modify, most likely a pen value
 *                  (int) resist - resistance mod, the return of spell_resist 
 * Returns:         (int) result - the value modified by the resistance
 */
public int
spell_resist_modify_value(int value, int resist)
{
    /* Clamp */
    resist = max(min(resist, 100), -100);
    
    /*
     * Reduces the effectiveness of vulnerability, -100 resistance equals 50%
     * bonus effect on the spell instead of 100%.
     * 
     * F_NEW_DAMAGE does not deal with negatives 
     */
    if (resist < 0) {
        resist /= 2;
        return value * (100 - resist) / 100;
    }

    return F_NEW_DAMAGE(value, random(100), resist);
} /* spell_resist_modify_value */

/*
 * Function name: combine_resistances
 * Description:   Sometimes spells are resisted by more than
 *                one type of resistance (typically MAGIC_I_RES_MAGIC and
 *                MAGIC_I_RES_<element>).  This function returns a composite
 *                resistance value for a target, given a list of resistance
 *                types to check.
 * Arguments:     object target - the object to check for resistance
 *                string resistances - the resistance types to check
 * Returns:       The total resistance
 */
public int
combine_resistances(object target, string *resistances)
{
    int i, res = 100;

    for (i = 0; i < sizeof(resistances); i++)
    {
        res = res * (100 - target->query_magic_res(resistances[i])) / 100;
    }

    if (res >= 0)
    {
        res = 100 - res;
    }

    return res;
}

/*
 * Function:    spell_resist_base
 * Description: This function provides the basic resistance a person has
 *              based on their skills and stats. It is added onto the
 *              results of combine_resistances to provide the total
 *              resistance the person has to the spell.
 *              Note that you can pass either an element by itself, or a
 *              list of elements. The difficulty is also by default TASK_FORMIDABLE
 *              unless otherwise specified.
 * Arguments:   target - this is the target that we are checking resistance on
 *              element_list - can be either a single element, or a list of elements
 *              difficulty - a task difficulty which defaults to TASK_FORMIDABLE if
 *                           not specified.
 */
public int
spell_resist_base(object target, mixed element_list, int difficulty = -1)
{
    int average_skill = 0;
    
    if (intp(element_list))
    {
        average_skill = target->query_skill(element_list);
    }
    else if (pointerp(element_list))
    {
            
        // First we determine the average of the element skills and weight it by 40
        int * element_skill_amounts = ({ });
        foreach (int element : element_list)
        {
            element_skill_amounts += ({ target->query_skill(element) });
        }
        average_skill = SUM_ARRAY(element_skill_amounts) / max(1, sizeof(element_skill_amounts));
    }    
    int average_skill_weighted = (average_skill * 40) / 100;
    
    if (difficulty < 0)
    {
        difficulty = TASK_FORMIDABLE;
    }
    
    int res = max(0, min(100,
        target->resolve_task(difficulty,
        ({ SKILL_WEIGHT, 40, SS_FORM_ABJURATION,
           SKILL_VALUE, average_skill_weighted,
           SKILL_WEIGHT, 20, SS_SPELLCRAFT,
           SKILL_WEIGHT, 20, TS_INT,
           SKILL_WEIGHT, 40, TS_WIS,
           SKILL_WEIGHT, 40, TS_DIS }))));
           
    return res;
}

/*
 * Function name: spell_resist_basic
 * Description:   Determines a target's base resistance to a spell.  This
 *                can be used for spells for which stat/skill-based
 *                resistance checks don't make sense.
 * Arguments:     object caster - the caster of the spell
 *                object target - the target of the spell
 *                int element   - list of spell element(s)
 *                int difficulty - the difficulty of resisting the spell
 * Returns:       Resistance percentage
 */
public int
spell_resist_basic(object caster, object target, mixed element_list,
    int difficulty)
{
    // We add all the applicable resistances
    string * resistances = ({ MAGIC_I_RES_MAGIC });
    if (intp(element_list))
    {
        resistances += ({ resistance_map[element_list] });
    }
    else if (pointerp(element_list))
    {
        foreach (int element : element_list)
        {
            if (resistance_map[element])
            {
                resistances += ({ resistance_map[element] });
            }
        }
    }
    return combine_resistances(target, resistances);
}

/*
 * Function name: spell_resist
 * Description:   Determines a target's resistance to a typical spell
 * Arguments:     object target - the target of the spell
 *                int element_list   - a list of the spell element(s)
 *                int difficulty - the difficulty of resisting the spell
 * Returns:       Resistance percentage
 */
public int
spell_resist(object caster, object target, mixed element_list, int difficulty = -1)
{
    if (difficulty < 0)
    {
        difficulty = TASK_FORMIDABLE;
    }
    
    int res = spell_resist_base(target, element_list, difficulty);

    res += spell_resist_basic(caster, target, element_list, difficulty);
    
    return min(res, 100);
}

/*
 * Function name: spell_resist_illusion
 * Description:   Determines a target's resistance to an illusion spell
 * Arguments:     object target - the target of the spell
 *                int element   - the spell element
 *                int difficulty - the difficulty of resisting the spell
 * Returns:       Resistance percentage
 */
public int
spell_resist_illusion(object caster, object target, int element,
    int difficulty)
{
    int res = spell_resist_base(target, SS_AWARENESS, difficulty);

    res += combine_resistances(target,
        ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_ILLUSION }));

    return min(res, 100);
}

/*
 * Function name: spell_resist_identify
 * Description:   Determines a target's resistance to identification spells
 * Arguments:     object target - the target of the spell
 *                int element   - the spell element
 *                int difficulty - the difficulty of resisting the spell
 * Returns:       Resistance percentage
 */
public int
spell_resist_identify(object caster, object target, int element,
    int difficulty)
{
    mixed *magic;
    int res;

    if (!living(target))
    {
        if ((magic = target->query_prop(MAGIC_AM_MAGIC)) && intp(magic[0]))
        {
            res = magic[0] / 4 + random(magic[0] / 4);
        }
    }
    else
    {
        res = spell_resist_base(target, element, difficulty);
    }

    res += combine_resistances(target, ({ MAGIC_I_RES_MAGIC,
        resistance_map[element], MAGIC_I_RES_IDENTIFY }));

    return min(100, res);
}


/*
 * Function name: spell_resist_healing
 * Description:   Determines target's resistance to a healing spell.
 * Arguments:     object caster - the caster of the spell
 *                object target - the target of the spell
 *                int element   - the spell element
 *                int difficulty - the difficulty of resisting the spell
 * Returns:       Resistance percentage
 */
public int
spell_resist_healing(object caster, object target, int element,
    int difficulty)
{
    int res = spell_resist_base(target, element, difficulty);

    res += combine_resistances(target,
        ({ MAGIC_I_RES_MAGIC, resistance_map[element], MAGIC_I_RES_HEALING }));
    
    return res;
}    

/*
 * Function name: spell_resist_beneficial
 * Description:   Determines target's resistance to a beneficial spell
 * Arguments:     object caster - the caster of the spell
 *                object target - the target of the spell
 *                int element   - the spell element
 *                int difficulty - the difficulty of resisting the spell
 * Returns:       Resistance percentage
 */
public int
spell_resist_beneficial(object caster, object target, int element,
    int difficulty)
{
    int res = spell_resist_base(target, element, difficulty);

    res += combine_resistances(target,
        ({ MAGIC_I_RES_MAGIC, resistance_map[element] }));
    
    return res;
}

/* 
 * Function name: spell_resist_damage_type 
 * Description  : Resistance function for a generic damage type which
 *                is not the same as the spell element.
 */
public int
spell_resist_damage_type(string resistance_prop, object caster, object target, int element, int difficulty)
{
    int res = spell_resist_base(target, element, difficulty);
    res += combine_resistances(target, ({ MAGIC_I_RES_MAGIC, resistance_prop }));
    return min(res, 100);
}


/*
 * Function name: spell_resist_cold
 * Description:   Determines a target's resistance to a cold spell
 *                (checks MAGIC_I_RES_COLD)
 * Arguments:     object target - the target of the spell
 *                int element   - the spell element
 *                int difficulty - the difficulty of resisting the spell
 * Returns:       Resistance percentage
 */
public int
spell_resist_cold(object caster, object target, int element, int difficulty)
{
    return spell_resist_damage_type(MAGIC_I_RES_COLD, caster, target, element, difficulty);
}

/*
 * Function name: spell_resist_electricity
 * Description:   Determines a target's resistance to an electricity spell
 *                (checks MAGIC_I_RES_ELECTRICITY)
 * Arguments:     object target - the target of the spell
 *                int element   - the spell element
 *                int difficulty - the difficulty of resisting the spell
 * Returns:       Resistance percentage
 */
public int
spell_resist_electricity(object caster, object target, int element, int difficulty)
{
    return spell_resist_damage_type(MAGIC_I_RES_ELECTRICITY, caster, target, element, difficulty);
}

/*
 * Function name: spell_resist_poison
 * Description:   Determines a target's resistance to a poison spell
 *                (checks MAGIC_I_RES_POISON)
 * Arguments:     object target - the target of the spell
 *                int element   - the spell element
 *                int difficulty - the difficulty of resisting the spell
 * Returns:       Resistance percentage
 */
public int
spell_resist_poison(object caster, object target, int element, int difficulty )
{
    return spell_resist_damage_type(MAGIC_I_RES_POISON, caster, target, element, difficulty);
}

/*
 * Function name: spell_resist_acid
 * Description:   Determines a target's resistance to a acid spell
 *                (checks MAGIC_I_RES_ACID)
 * Arguments:     object target - the target of the spell
 *                int element   - the spell element
 *                int difficulty - the difficulty of resisting the spell
 * Returns:       Resistance percentage
 */
public int
spell_resist_acid(object caster, object target, int element, int difficulty )
{
    return spell_resist_damage_type(MAGIC_I_RES_ACID, caster, target, element, difficulty);
}

/*
 * Function name: add_element_resistance
 * Description:   Define a resistance type for a nonstandard element type.
 * Arguments:     1. (int) element - the skill used for the nonstandard element
 *                2. (string) resistance - the resistance property to be
 *                                         used
 * Note:          If you use a nonstandard (not mudlib defined) element, you
 *                must either use this function to identify a resistance type
 *                or define your own resistance formulae. The former is
 *                preferred.
 *
 *                Typically, the resistance type should be one of the standard,
 *                mudlib-defined resistances (MAGIC_I_RES_*).
 */
public void
add_element_resistance(int element, string resistance)
{
    resistance_map[element] = resistance;
}
