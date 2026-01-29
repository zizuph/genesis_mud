/*
 * Centralized Base Spell
 *
 * Include this file in a centralized spell. This header file includes functions
 * that should only be executed by the first spell to inherit from
 * centralized_spell.c. All other spells will be unable to call these setters.
 *
 * Created by Petros, March 2013
 */

#include <formulas.h>

/* We mask a bunch of functions to prevent them from ever being called */
/*
 * Function:    set_spell_mana
 * Description: Sets the base mana cost for the spell. By making it
 *              private, it prevents all inherited spells from setting
 *              it. If you wish to change the mana cost, use 
 *              set_spell_mana_factor instead.
 */
private nomask void 
set_spell_mana(int mana)
{
    ::set_spell_mana(mana);
}

/*
 * Function:    set_spell_time
 * Description: Sets the base casting time for the spell. By making it
 *              private, it prevents all inherited spells from setting
 *              it. If you wish to change the casting time, use 
 *              set_spell_time_factor instead.
 */
private nomask void 
set_spell_time(int seconds)
{
    ::set_spell_time(seconds);
}
