/*
 * A compendium of formulas used for specials, a way to easily keep track
 * and re-balance these formulas.
 *
 * I have in no way, shape or form, created the below listed formulas. They
 * are copied from spells that have previously been balanced.
 * 
 * Compiled by Carnak.
 *
 * November 2021 - Zizuph - added convert_caid_to_percentage, already in
 *                          heavy usage.
 *
 */
#include <ss_types.h>
#include <formulas.h>

#define LIVE_I_SPELLPOWER   "_live_i_spellpower"

/*
 * Function name:   convert_caid_to_haste
 * Description:     Calculate the haste value of specified caid.
 * Arguments:       1. (object) player: The target player for the conversion
 *                              (for future development)
 *                  2. (int) caid: The combat aid value to convert.
 * Returns:         (int) : The converted value
 */
public int
convert_caid_to_haste(object player, int caid)
{
    /*
     * Haste formula has been changed by AoB
     *
     * There is an effective cap on all haste at 150, so the cap has been
     * raised to that.
     *
     * caid is calculated as the percentage increase in hit rate.
     * 300 quickness translates to a 2 second swing time, instead of the
     * standard 5.
     * 5 / 2 = 2.5, or 250% the speed of a 5 second swing.  This is 150
     * caid, as it is 150% over the 100% base.
     *
     * Representing this formula based on this:
     * (100 + caid) = 50000 / (500 - quickness)
     *
     * Rearranging this formula and solving for quickness:
     * quickness = 500 - (50000 / (100 + caid))
     *
     */
    caid    = min(150, caid);
    
    return 500 - (50000 / (100 + caid));
} /* convert_caid_to_haste */


/*
 * Function name:   convert_caid_to_percentage
 * Description:     Calculate the percentage effect of specified caid.
 * Returns:         (int) : The converted percentage effect.  This assumes
 *                     a base effect of 100, and may need additional scaling 
 *                     based on what the percentage is modifying.
 */
public int
convert_caid_to_percentage(int caid)
{
    return (caid * 100) / (caid + 100);
}

/*
 * Function name:   convert_caid_to_stat
 * Description:     Calculate the stat value for specified caid.
 * Arguments:       1. (object) player: The target player for the conversion
 *                              (for future development)
 *                  2. (int) caid: The combat aid value to convert.
 *                  3. (int) stat: The stat we wish to convert. (0-5)
 * Returns:         (int) : The converted value
 */
public int
convert_caid_to_stat(object player, int caid, int stat)
{
    int     base, boost, value;
    float   modus;
    
    base = player->query_base_stat(stat);
    boost = convert_caid_to_percentage(caid);
    
    switch(stat)
    {
        case SS_STR:
            modus = 1.0 + (itof(boost) / 100.0);
            boost = ftoi(150.0 * (modus - 1.0) + (itof(base) * modus));
            value = boost - base;
            break;
            
        default:
            value = (base * boost) / 100;
            break;
    }
    
    return value;
} /* convert_caid_to_stat */

/*
 * Function name:   convert_caid_to_resistance
 * Description:     Calculate the resistance value for specified caid.
 * Arguments:       1. (object) player: The target player for the conversion
 *                              (for future development)
 *                  2. (int) caid: The combat aid value to convert.
 *                  3. (string) resistance: The resistance prop.
 *                              (for future development)
 * Returns:         (int) : The converted value
 */
public int
convert_caid_to_resistance(object player, int caid, string resistance)
{
    return convert_caid_to_percentage(caid);
} /* convert_caid_to_resistance */

/*
 * Function name:   convert_caid_to_skill
 * Description:     Calculate the skill value for specified caid. Skills without
 *                  a combat oriented value will result in null.
 * Arguments:       1. (object) player: The target player for the conversion
 *                              (for future development)
 *                  2. (int) caid: The combat aid value to convert.
 *                  3. (int) skill: The skill number of the target skill.
 *                              (for future development)
 * Returns:         (int) : Converted skill level
 */
public int
convert_caid_to_skill(object player, int caid, int skill)
{
    // Null value has yet to be added, this function is still in development
    return convert_caid_to_percentage(caid);
} /* convert_caid_to_skill */

/*
 * Function name:   convert_caid_to_armour_class
 * Description:     Calculate the armour value for specified caid.
 * Arguments:       1. (object) target: The target armour for the conversion
 *                              (for future development)
 *                  2. (int) caid: The combat aid value to convert.
 * Returns:         (int) : Converted armour value
 */
public int
convert_caid_to_armour_class(object target, int caid)
{
    int armour = target->query_ac();
    // Dont use this! Just a test, needs a proper calculations.
    // Multiply by (5 - hitlocs)...
    return (((100 * caid) / (100 + caid)) * (60 - armour)) / 60;
} /* convert_caid_to_armour_class */

/*
 * Function name:   convert_caid_to_weapon_hit
 * Description:     Calculate the weapon hit value for specified caid.
 * Arguments:       1. (object) target: The target weapon for the conversion
 *                              (for future development)
 *                  2. (int) caid: The combat aid value to convert.
 * Returns:         (int) : Converted hit value
 */
public int
convert_caid_to_weapon_hit(object target, int caid)
{
    int hit = target->query_hit();
    // Dont use this! Just a test, needs a proper calculations.
    return (((100 * caid) / (100 + caid)) * (60 - hit)) / 60;
} /* convert_caid_to_weapon_hit */

/*
 * Function name:   convert_caid_to_weapon_pen
 * Description:     Calculate the weapon pen value for specified caid.
 * Arguments:       1. (object) target: The target weapon for the conversion
 *                              (for future development)
 *                  2. (int) caid: The combat aid value to convert.
 * Returns:         (int) : Converted pen value
 */
public int
convert_caid_to_weapon_pen(object target, int caid)
{
    int pen = target->query_pen();
    // Dont use this! Just a test, needs a proper calculations.
    return (((100 * caid) / (100 + caid)) * (60 - pen)) / 60;
} /* convert_caid_to_weapon_pen */


/*
 * Function name:   convert_tohit_to_combat_aid_reduction
 * Description:     Calculate expected percentage of hits
 * Arguments:       1. (int) tohit: The tohit value to convert.
 * Returns:         (int) : The percentage an effect has been reduced
 *                  based on its tohit.
 */
public int 
convert_tohit_to_combat_aid_reduction(int tohit)
{
    // Not the most elegant solution, but works for now, until we
    // set a good formulae for this.
    mapping hit_list = ([
        70:68, 71:69, 72:70, 73:71, 74:72,
        75:73, 76:74, 77:74, 78:75, 79:76,
        80:77, 81:77, 82:78, 83:79, 84:80,
        85:80, 86:81, 87:81, 88:82, 89:83,
        90:83, 91:84, 92:84, 93:85, 94:85,
        95:86, 96:86, 97:87, 98:87, 99:88,
        100:88, 101:88, 102:89, 103:89, 104:89,
        105:90, 106:90, 107:90, 108:91, 109:91,
        110:91, 111:92, 112:92, 113:92, 114:92,
        115:93, 116:93, 117:93, 118:93, 119:93,
        120:94, 121:94, 122:94, 123:94, 124:94
    ]);
    
    switch (tohit / 5)
    {
        case 0..13: return 100 - max(1, tohit - 1);
        case 14..24: return 100 - hit_list[tohit];
        case 25..26: return 5;
        case 27..28: return 4;
        case 29..30: return 3;
        case 31..35: return 2;
        case 36..50: return 1;
        default: return 0;
    }
    return 0;
}

public int get_natural_spellpower(object living)
{
    if (living->query_prop(LIVE_I_SPELLPOWER))
    {
        return living->query_prop(LIVE_I_SPELLPOWER);
    }
    
    // We use the same number for both hit/pen, so compute this
    // as an average of the two unarmed formulas, using INT and
    // WIS and SS_SPELLCRAFT.
    int spellcraft = living->query_skill(SS_SPELLCRAFT);
    int skill = F_UNARMED_HIT(spellcraft, living->query_stat(SS_INT))
        + F_UNARMED_PEN(spellcraft, living->query_stat(SS_WIS));
    skill += W_HAND_HIT + W_HAND_PEN;

    return skill / 2;
}

