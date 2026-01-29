#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>

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
 * Function name: spell_resist
 * Description:   Determines a target's resistance to a typical spell
 * Arguments:     object target - the target of the spell
 *                int element   - the spell element
 *                int difficulty - the difficulty of resisting the spell
 * Returns:       Resistance percentage
 */
public int
spell_resist(object caster, object target, int element, int difficulty)
{
    int res;

    res = max(0, min(100, 
        target->resolve_task(difficulty,
        ({ SKILL_WEIGHT, 40, SS_FORM_ABJURATION,
           SKILL_WEIGHT, 40, element,
           SKILL_WEIGHT, 20, SS_SPELLCRAFT,
           SKILL_WEIGHT, 20, TS_INT,
           SKILL_WEIGHT, 40, TS_WIS,
           SKILL_WEIGHT, 40, TS_DIS }))));

    res += combine_resistances(target, 
        ({ MAGIC_I_RES_MAGIC, resistance_map[element] }));

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
    int res;

    res = max(0, min(100,
        target->resolve_task(difficulty,
        ({ SKILL_WEIGHT, 20, SS_FORM_ABJURATION,
           SKILL_WEIGHT, 60, SS_AWARENESS,
           SKILL_WEIGHT, 20, SS_SPELLCRAFT,
           SKILL_WEIGHT, 40, TS_INT,
           SKILL_WEIGHT, 40, TS_WIS,
           SKILL_WEIGHT, 20, TS_DIS }))));

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
        if (magic = target->query_prop(MAGIC_AM_MAGIC))
        {
            res = magic[0] / 4 + random(magic[0] / 4);
        }
    }
    else
    {
        res = max(0, min(100, 
            target->resolve_task(difficulty,
            ({ SKILL_WEIGHT, 40, SS_FORM_ABJURATION,
               SKILL_WEIGHT, 40, element,
               SKILL_WEIGHT, 20, SS_SPELLCRAFT,
               SKILL_WEIGHT, 20, TS_INT,
               SKILL_WEIGHT, 40, TS_WIS,
               SKILL_WEIGHT, 40, TS_DIS }))));
    }

    res += combine_resistances(target, ({ MAGIC_I_RES_MAGIC,
        resistance_map[element], MAGIC_I_RES_IDENTIFY }));

    return min(100, res);
}

/*
 * Function name: spell_resist_basic
 * Description:   Determines a target's base resistance to a spell.  This
 *                can be used for spells for which stat/skill-based
 *                resistance checks don't make sense.
 * Arguments:     object caster - the caster of the spell
 *                object target - the target of the spell
 *                int element   - the spell element
 *                int difficulty - the difficulty of resisting the spell
 * Returns:       Resistance percentage
 */
public int
spell_resist_basic(object caster, object target, int element,
    int difficulty)
{
    return combine_resistances(target,
        ({ MAGIC_I_RES_MAGIC, resistance_map[element] }));
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
    return combine_resistances(target,
        ({ MAGIC_I_RES_MAGIC, resistance_map[element], MAGIC_I_RES_HEALING }));
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
    return combine_resistances(target,
        ({ MAGIC_I_RES_MAGIC, resistance_map[element] }));
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
spell_resist_cold(object caster, object target, int element,
    int difficulty)
{
    int res;

    res = max(0, min(100,
        target->resolve_task(difficulty,
        ({ SKILL_WEIGHT, 40, SS_FORM_ABJURATION,
           SKILL_WEIGHT, 40, element,
           SKILL_WEIGHT, 20, SS_SPELLCRAFT,
           SKILL_WEIGHT, 20, TS_INT,
           SKILL_WEIGHT, 40, TS_WIS,
           SKILL_WEIGHT, 40, TS_DIS }))));

    res += combine_resistances(target,
        ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_COLD }));

    return min(res, 100);
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
spell_resist_electricity(object caster, object target, int element,
    int difficulty)
{
    int res;

    res = max(0, min(100,
        target->resolve_task(difficulty,
        ({ SKILL_WEIGHT, 40, SS_FORM_ABJURATION,
           SKILL_WEIGHT, 40, element,
           SKILL_WEIGHT, 20, SS_SPELLCRAFT,
           SKILL_WEIGHT, 20, TS_INT,
           SKILL_WEIGHT, 40, TS_WIS,
           SKILL_WEIGHT, 40, TS_DIS }))));

    res += combine_resistances(target,
        ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_ELECTRICITY }));

    return min(res, 100);
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
