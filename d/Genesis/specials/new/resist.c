#include <formulas.h>
#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <math.h>
#include "/std/combat/combat.h"

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
 * We convert AC into a 'natural resistance', so that any NPC that does
 * not have resistances set, will have the same elemental resistance as
 * its AC.  We then apply an AC modifier, based on the spell element and
 * the race, using the PER_RACE_RESISTANCE table.  Players get half their
 * AC applied as natural resistance.
 *
 * We combine the natural resistance with the existing resistances using
 * the combine_resistances formula.
 *
 */
static mapping PER_RACE_RESISTANCE =
([
    "half-elf": ([ MAGIC_I_RES_EARTH: -5, MAGIC_I_RES_FIRE: -5,
                   MAGIC_I_RES_COLD: 5, MAGIC_I_RES_ILLUSION: 5 ]),
    "elf":      ([ MAGIC_I_RES_EARTH: -10, MAGIC_I_RES_FIRE: -10,
                   MAGIC_I_RES_COLD: 10, MAGIC_I_RES_ILLUSION: 10 ]),
    "drow":     ([ MAGIC_I_RES_WATER: -10, MAGIC_I_RES_AIR: -10,
                   MAGIC_I_RES_COLD: 10, MAGIC_I_RES_ILLUSION: 10 ]),
    "dwarf":    ([ MAGIC_I_RES_POISON: 10, MAGIC_I_RES_WATER: -10,
                   MAGIC_I_RES_AIR: -10, MAGIC_I_RES_EARTH: 10 ]),
    "hobbit":   ([ MAGIC_I_RES_ELECTRICITY: -10, MAGIC_I_RES_POISON: 10,
                   MAGIC_I_RES_DEATH: -10, MAGIC_I_RES_AIR: 10 ]),
    "halfling": ([ MAGIC_I_RES_ELECTRICITY: -10, MAGIC_I_RES_EARTH: 10,
                   MAGIC_I_RES_DEATH: -10, MAGIC_I_RES_AIR: 10 ]),
    "kender":   ([ MAGIC_I_RES_AIR: 10, MAGIC_I_RES_ILLUSION: -10]),
    "gnome":    ([ MAGIC_I_RES_ELECTRICITY: 10, MAGIC_I_RES_WATER: -10,
                   MAGIC_I_RES_COLD: -10, MAGIC_I_RES_ILLUSION: 10 ]),
    "goblin":   ([ MAGIC_I_RES_DEATH: 10, MAGIC_I_RES_EARTH: 10,
                   MAGIC_I_RES_COLD: -10, MAGIC_I_RES_ILLUSION: -10 ]),
    "halfling": ([ MAGIC_I_RES_ELECTRICITY: -10, MAGIC_I_RES_EARTH: 10,
                   MAGIC_I_RES_DEATH: -10, MAGIC_I_RES_AIR: 10 ]),
    "orc":      ([ MAGIC_I_RES_POISON: 10, MAGIC_I_RES_WATER: -10,
                   MAGIC_I_RES_AIR: -10, MAGIC_I_RES_FIRE: 10 ]),
    "uruk":     ([ MAGIC_I_RES_POISON: 10, MAGIC_I_RES_WATER: -10,
                   MAGIC_I_RES_AIR: -10, MAGIC_I_RES_FIRE: 10 ]),
    "minotaur": ([ MAGIC_I_RES_ELECTRICITY: -10, MAGIC_I_RES_WATER: 10,
                   MAGIC_I_RES_EARTH: -10, MAGIC_I_RES_ACID: 10 ]),
    "kobold":   ([ MAGIC_I_RES_POISON: -10, MAGIC_I_RES_AIR: -10,
                   MAGIC_I_RES_COLD: 20 ]),
    "troll":    ([ MAGIC_I_RES_ELECTRICITY: 15, MAGIC_I_RES_POISON: 15,
                   MAGIC_I_RES_FIRE: -15, MAGIC_I_RES_ACID: -15 ]),
    "ogre":     ([ MAGIC_I_RES_POISON: 10, MAGIC_I_RES_EARTH: -10,
                   MAGIC_I_RES_COLD: 10, MAGIC_I_RES_ILLUSION: -10 ]),
    "half-ogre":([ MAGIC_I_RES_POISON: 5, MAGIC_I_RES_EARTH: -5,
                   MAGIC_I_RES_COLD: 5, MAGIC_I_RES_ILLUSION: -5 ]),
    "giant":    ([ MAGIC_I_RES_POISON: 10, MAGIC_I_RES_EARTH: -10,
                   MAGIC_I_RES_COLD: 10, MAGIC_I_RES_ILLUSION: -10 ]),
    "centaur":  ([ MAGIC_I_RES_LIFE: 10, MAGIC_I_RES_EARTH: -10,
                   MAGIC_I_RES_FIRE: -10, MAGIC_I_RES_ILLUSION: 10 ]),
    // Undead had two many values on the original chart, took out poison.
    "undead":   ([ MAGIC_I_RES_COLD:  15, MAGIC_I_RES_LIFE: -15,
                   MAGIC_I_RES_DEATH: 15, MAGIC_I_RES_FIRE: -15 ])
]);

//Arman, Nov 2021

//RACIAL MAGIC RESISTANCE MAX SCALING BONUS (%)
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| RACE     | Elec | Pois | Iden | Life | Deat | Wate | Air  | Eart | Fire | Cold | Acid | Illu |
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Human    |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Half-elf |  0   |  0   |  0   |  0   |  0   |  0   |   0  |  -5  |  -5  |  +5  |  0   |  +5  |
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Elf      |  0   |  0   |  0   |  0   |  0   |  0   |   0  | -10  | -10  | +10  |  0   | +10  |
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Drow     |  0   |  0   |  0   |  0   |  0   | -10  | -10  |  0   |  0   | +10  |  0   | +10  |
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Dwarf    |  0   | +10  |  0   |  0   |  0   | -10  | -10  | +10  |  0   |  0   |  0   |  0   | 
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Hobbit   | -10  | +10  |  0   |  0   | -10  |  0   | +10  |  0   |  0   |  0   |  0   |  0   | 
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Halfling | -10  |  0   |  0   |  0   | -10  |  0   | +10  | +10  |  0   |  0   |  0   |  0   | 
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Kender   |  0   |  0   |  0   |  0   |  0   |  0   | +10  |  0   |  0   |  0   |  0   | -10  | 
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Gnome    | +10  |  0   |  0   |  0   |  0   | -10  |  0   |  0   |  0   | -10  |  0   | +10  | 
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Goblin   |  0   |  0   |  0   |  0   | +10  |  0   |  0   | +10  |  0   | -10  |  0   | -10  | 
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Orc      |  0   | +10  |  0   |  0   |  0   | -10  | -10  |  0   | +10  |  0   |  0   |  0   | 
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Uruk     |  0   | +10  |  0   |  0   |  0   | -10  | -10  |  0   | +10  |  0   |  0   |  0   | 
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Minotaur | -10  |  0   |  0   |  0   |  0   | +10  |  0   | -10  |  0   |  0   | +10  |  0   |  
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Kobold   |  0   | -10  |  0   |  0   |  0   |  0   | -10  |  0   |  0   | +20  |  0   |  0   | 
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Troll    | +15  | +15  |  0   |  0   |  0   |  0   |  0   |  0   | -15  |  0   | -15  |  0   |  
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Ogre     |  0   | +10  |  0   |  0   |  0   |  0   |  0   | -10  |  0   | +10  |  0   | -10  |  
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Half-Ogre|  0   | +5   |  0   |  0   |  0   |  0   |  0   | -5   |  0   | +5   |  0   | -5   |  
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Giant    |  0   | +10  |  0   |  0   |  0   |  0   |  0   | -10  |  0   | +10  |  0   | -10  |  
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Centaur  |  0   |  0   |  0   | +10  |  0   |  0   |   0  | -10  | -10  |  0   |  0   | +10  |
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Undead * |  0   | +15  |  0   | -15  | +15  |  0   |  0   |  0   | -15  | +15  |  0   |  0   |  
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+
//| Kroug    |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  0   |  
//+----------+------+------+------+------+------+------+------+------+------+------+------+------+

public int
spell_resist_modify_by_race(string race, string element, int starting_value)
{
    mapping race_modifier = PER_RACE_RESISTANCE[race];
    if (!mappingp(race_modifier))
        return starting_value;
    mixed element_modifier = race_modifier[element];
    if (!intp(element_modifier))
        return starting_value;
    return starting_value * (100 + element_modifier) / 100;
}

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
     * cb_hit_me uses 
     * rnd(pen/4) + rnd(pen/4) + rnd(pen/4) + rnd(pen/4) for non-magic hits, and 
     * rnd(pen/4) + rnd(pen/4) + rnd(pen/4) + pen/4 for MAGIT_DT hits.
     * 
     * Average damage for non-magic:
     * pen/8 + pen/8 + pen/8 + pen/8 = 4*pen/8.
     * Average damage for MAGIC_DT:
     * pen/8 + pen/8 + pen/8 + pen/4 = 5*pen/8
     *
     * To account for this discrepancy, we will multiply pen by 4/5 to bring
     * it on the same scale as non-magic cb_hit_me
     */
    value = value * 4 / 5;
    
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

    // F_NEW_DAMAGE causes a lot of misses on high resist.
    // we'll try just reducing the damage outright and see if that is
    // a better player experience, even if it does not affect DPS.
    return value * (100 - resist) / 100;

    //return F_NEW_DAMAGE(value, random(100), resist);
} /* spell_resist_modify_value */

/*
 * Function name:   natural_resistance_from_armour
 * Description:     This function calculates the average armour class,
                    modified by the racial modifiers.
 * Arguments:       (object) target  - target of the spell
 *                  (string) restance - the element of the spell
 * Returns:         (int) result - the value modified by the resistance
 */
public int
natural_resistance_from_armour(object target, string resistance)
{
    object co = target->query_combat_object();

    int tmp = random(100);
    mixed hitloc, last_hitloc;
    foreach (int id : co->query_hitloc_id())
    {
        hitloc = co->query_hitloc(id);
        
        if (sizeof(hitloc) < 2)
        {
            continue;
        }
        last_hitloc = hitloc;
        tmp -= last_hitloc[HIT_PHIT];
        if (tmp < 0)
        {
            break;
        }
    }
    int armour = 1;
    if (last_hitloc)
    {
        if (intp(last_hitloc[HIT_AC]))
        {
            armour = last_hitloc[HIT_AC];
        }
        else if (sizeof(last_hitloc[HIT_AC]))
        {
            armour = one_of_list(last_hitloc[HIT_AC]);
        }
    }

    if (target->query_prop(LIVE_I_UNDEAD))
    {
        armour = spell_resist_modify_by_race("undead", resistance, armour);
    }
    armour = spell_resist_modify_by_race(target->query_race_name(),
        resistance, armour);
    return armour;
}

/*
 * Function name: combine_resistances
 * Description:   Sometimes spells are resisted by more than
 *                one type of resistance (typically MAGIC_I_RES_MAGIC and
 *                MAGIC_I_RES_<element>).  This function returns the highest
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

    if (res < 0)
    {
        res = res / 2;
    }
    return res;
}

/*
 * Function name: combine_resistances_with_base
 * Description:   Combine AC-based resistance with elemental resistance.
 * Arguments:     object target - the object to check for resistance
 *                int natural_resistance - the average AC of the
 *                   target, modified by race.
 *                int elemental_resistance - the percentage resistance
 *                   to the elements.
 * Returns:       The total resistance
 */
public int
combine_resistance_with_base(object target, int natural_resistance, 
                             int elemental_resistance)
{
    int result;
    if (target->query_npc())
    {
        // Return the better of AC-based resistance, or that
        // coming from the elemental resistance on the NPC.
        int base_resistance = ftoi(F_AC_MOD(natural_resistance));
        
        // Elemental Resistance only affects the remaining percentage,
        // apply it as well.
        base_resistance = (100 - base_resistance) 
            * (100 - elemental_resistance) / 100;
        result = 100 - base_resistance;
    }
    else
    {
        // For players, 50% of their AC goes into base resistance.  They
        // can get up to 125% of their AC through elemental resistance,
        // and can only pass 125% of their AC-based bonus through
        // elemental resistance exclusively.
        // In other words, they get less resistance than NPCs, but have
        // items available that can cover this gap (and exceed it).
        int base_resistance = ftoi(F_AC_MOD(natural_resistance / 2));
        
        // Elemental Resistance only affects the remaining percentage,
        // apply it as well.
        base_resistance = (100 - base_resistance) 
            * (100 - elemental_resistance) / 100;
        base_resistance = 100 - base_resistance;
        
        // Armour can only help contribute up to this maximum resistance.
        int max_natural_percent = ftoi(F_AC_MOD(natural_resistance * 5 / 4));

        // Make sure armour + elemental < maximum armour + elemental
        result = min(max_natural_percent, base_resistance);

        // Elemental can surpass armour-based - use it.
        result = max(elemental_resistance, result);
    }    
    return (min(100, result));
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
    int natural_res = 0;
    foreach(string resistance_prop : resistances)
    {
        natural_res = max(natural_res, 
            natural_resistance_from_armour(target, resistance_prop));
    }
    
    int elemental_res = combine_resistances(target, resistances);
    return combine_resistance_with_base(target,natural_res, elemental_res);
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
    
    return spell_resist_basic(caster, target, element_list, difficulty);
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
    int natural_res = natural_resistance_from_armour(target, 
         MAGIC_I_RES_ILLUSION);
    
    int elemental_res = combine_resistances(target, 
        ({ MAGIC_I_RES_MAGIC, MAGIC_I_RES_ILLUSION }));
        
    return combine_resistance_with_base(target, natural_res, elemental_res);
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
        res = natural_resistance_from_armour(target, 
             MAGIC_I_RES_ILLUSION);
    }
    
    int elemental_res = combine_resistances(target, 
        ({ MAGIC_I_RES_MAGIC, resistance_map[element], 
           MAGIC_I_RES_IDENTIFY }));
        
    return combine_resistance_with_base(target,res, elemental_res);


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
 * Function name: spell_resist_natural_only 
 * Description  : Resistance function for a generic damage type which
 *                is not the same as the spell element.
 */
public int
spell_resist_natural_only(object caster, object target, int element)
{
    int natural_res = natural_resistance_from_armour(target, resistance_map[element]);
    return combine_resistance_with_base(target, natural_res, 0);
}

/* 
 * Function name: spell_resist_damage_type 
 * Description  : Resistance function for a generic damage type which
 *                is not the same as the spell element.
 */
public int
spell_resist_damage_type(string resistance_prop, object caster, object target, int element, int difficulty)
{
    int natural_res = natural_resistance_from_armour(target, resistance_prop);
    int elemental_res = combine_resistances(target, ({ MAGIC_I_RES_MAGIC, resistance_prop }));
    return combine_resistance_with_base(target,natural_res, elemental_res);
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




public string *
element_to_resistance(mixed element_list)
{
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
    
    return resistances;
}


public string *
spell_resist_immunity(object caster, object target, string *resistances)
{
    object *items = target->query_magic_effects();
    string *list = ({});
    
    for (int j = 0; j < sizeof(resistances); j++)
    {
        if (target->query_prop(PRE_OBJ_MAGIC_RES + resistances[j]) >= 100)
        {
            list += ({ resistances[j] });
            continue;
        }
        
        for (int i = 0; i < sizeof(items); i++)
        {
            mixed value = items[i]->query_magic_protection(resistances[j], target);

            if (!pointerp(value) || value[0] < 100)
                continue;
        
            list += ({ resistances[j] });
        }
    }
    
    return list;
}


public mixed *
compound_resistances(object target, string *resistances)
{
    int     resist = 0;
    string *list = ({});
    object *items = target->query_magic_effects();
    
    for (int r = 0; r < sizeof(resistances); r++)
    {
        int *value = allocate(2);
        
        value[0] = target->query_prop(PRE_OBJ_MAGIC_RES + resistances[r]);
        target->catch_msg("Base res: " + value[0] + "\n");
        
        if (value[0] >= 100)
        {
            list += ({ resistances[r] });
            continue;
        }
        
        for (int i = 0; i < sizeof(items); i++)
        {
            mixed   prop;
            int     stack = 0;

            prop = items[i]->query_magic_protection(resistances[r], target);
            
            if (pointerp(prop))
            {
                stack = prop[1];
                prop = prop[0];
            }
            
            target->catch_msg("Item: " + file_name(items[i]) + " Res: " + resistances[r] + " Value: " + prop + "\n");
            
            if (prop < 100)
            {
                value[stack] += prop;
                continue;
            }
            
            list += ({ resistances[r] });
        }
        
        resist += max(value[0], value[1]) / 5;
    }

    return ({ resist, list });
}

public int
natural_spell_resist(object target, mixed element_list)
{
    int res, average_skill = 0;
    if (intp(element_list))
    {
        average_skill = target->query_skill(element_list);
    }
    else if (pointerp(element_list))
    {
        // First we determine the average of the element skills and weight it by 40
        int * skill_amounts = ({ });
        foreach (int element : element_list)
        {
            skill_amounts += ({ target->query_skill(element) });
        }
        average_skill = SUM_ARRAY(skill_amounts) / max(1, sizeof(skill_amounts));
    }
    int average_skill_weighted = (average_skill * 40) / 100;
    
    res = target->find_drm(({
        SKILL_WEIGHT,   40, SS_FORM_ABJURATION,
        SKILL_VALUE,    average_skill_weighted, 
        SKILL_WEIGHT,   20, SS_SPELLCRAFT,
        SKILL_WEIGHT,   40, TS_INT,
        SKILL_WEIGHT,   40, TS_WIS,
        SKILL_WEIGHT,   20, TS_DIS })) / 10;
    
    // Lets cap it at 40.
    return max(0, min(40, res));
}

public int
spell_resist_test(object caster, object target, mixed element_list)
{
    string *resistances = element_to_resistance(element_list);
    int     res = natural_spell_resist(target, element_list);
    target->catch_msg("Res: " + res + " Resistances: " + implode(resistances, ", ") + "\n");
    //if (sizeof(spell_resist_immunity(caster, target, resistances)))
    //    return 100;
    
    int *compound = compound_resistances(target, resistances);
    
    if (pointerp(compound))
    {
        if (sizeof(compound[1]))
        {
            target->catch_msg("Immunities: " + implode(compound[1], ", ") + "\n");
            return 100;
        }
        
        res += compound[0];
    }

    target->catch_msg("Res2: " + res + "\n");
    return ftoi(F_AC_MOD(res));
}


public int
combine_values(int* values)
{
    int i, res = 100;

    for (i = 0; i < sizeof(values); i++)
    {
        res = res * (100 - values[i]) / 100;
    }

    if (res >= 0)
    {
        res = 100 - res;
    }

    return res;
}
