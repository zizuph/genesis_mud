/*
 * Common Spell Functions to be used in all Elementalist Spells
 *
 * Created by Petros, April 2014
 */

#pragma strict_types

#include <composite.h>
#include "defs.h"

/*
 * Function:    can_cast_elementalist_spell
 * Description: Defines the conditions under which a spell can be
 *              cast.
 */
public int
can_cast_elementalist_spell(object caster)
{
    setuid();
    seteuid(getuid());

    if (caster->query_wiz_level())
    {
        return 1;
    }
    // Only Guild Members can cast these spells
    if (!IS_CLERIC(caster) && !IS_WORSHIPPER(caster) && !IS_SEEKER(caster))
    {
        caster->catch_tell("You are not a follower of the Elementals!\n");
        return 0;
    }
    
    // If spell banned, can't allow casting
    if (GUILD_MANAGER->query_is_punish_spell_banned(caster))
    {
        caster->catch_tell("The Elementalist Guild Council has banned you "
                           + "from invoking the gifts of the Elementals.\n");
        return 0;
    }

    int align = caster->query_alignment();
    switch (align)
    {
    	case 0..1200: // No penalty
    		caster->add_prop(CONDUIT_PENALTY, 0);
    		break;
    	case -300..-1: // Halved conduit gain
    		caster->add_prop(CONDUIT_PENALTY, 1);
    		break;
    	case -600..-301: // Halved conduit gain, double conduit cost
    		caster->add_prop(CONDUIT_PENALTY, 2);
    		break;
    	case -1200..-601: // Halved conduit gain, double conduit cost,
    		              // halved CAID
    		caster->add_prop(CONDUIT_PENALTY, 3);
    		break;
    }
    
    return 1;
}

public varargs string
query_restricted_ability_message(string ability, object player)
{
    string short_desc;
    
    short_desc = ability->short();
    if (!strlen(short_desc))
    {
        return "You are busy concentrating on a prayer.\n";
    }
    
    return "You are too busy concentrating on a prayer to "
        + short_desc + ".\n";    
}

/*
 * Function name: hook_no_mana_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have enough mana.
 * Returns:       The message to print.
 */
public void
hook_no_mana_fail(object ability)
{
    write("You don't have mana enough to properly use the prayer.\n");
}

/*
 * Function name: hook_targets_gone
 * Description:   Return the string that will be printed to the caster when
 *                the targets has disappeared during the prepartion of the
 *                spell.
 * Returns:       The message to print
 */
public void
hook_targets_gone()
{
    write("Nobody here to use the prayer on!\n");
}

/*
 * Function name: hook_living_no_magic_attack_fail
 * Description:   This function should return the string that will be printed
 *                to the caster, when trying to attack a living that has the
 *                property OBJ_M_NO_MAGIC_ATTACK set.
 * Arguments:     target - The intended targer
 * Returns:       The message to print
 */
public void
hook_living_no_magic_attack_fail(object target,object ability)
{
    write("You can't use a prayer on " +
        target->query_the_name(this_player()) + ".\n");
}

public void
hook_cannot_see_fail(object ability)
{
    write("You cannot see to use the prayer!\n");
}

/*
* Function:    hook_casting_shield_failure
* Description: This gets called when the player fails to cast
*               the spell due to interference from worn shields.
*/
public void
hook_casting_shield_failure(object caster, object *shields)
{
	caster->catch_tell("You sense that "+
		FO_COMPOSITE_DEAD(shields, caster) +
		(sizeof(shields) == 1 ? " has " : " have ") +
		"interfered with your prayer.\n");
}
