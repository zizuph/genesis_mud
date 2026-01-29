#include <composite.h>
#include <ss_types.h>
#include <wa_types.h>

/*
 * Function name: hook_no_magic_fail
 * Description:   Return the message that should be printed when noone
 *                is supplied with ROOM_M_NO_MAGIC.
 * Arguments:     obj - The room object.
 * Returns:       The message to print.
 */
public void
hook_room_no_magic_fail(mixed reason, object room)
{
    if (stringp(reason))
    {
        write(reason);
    }
    else
    {
        write("You can't draw upon the magic, as if resisted by the " +
            "very air around you.\n");
    }
}

/*
 * Function name: hook_no_magic_attack_fail
 * Description:   Return the message that should be printed when noone
 *                is supplied with ROOM_M_NO_MAGIC_ATTACK.
 * Arguments:     obj - The room object.
 * Returns:       The message to print.
 */
public void
hook_room_no_magic_attack_fail(mixed reason, object room)
{
    if (stringp(reason))
    {
        write(reason);
    }
    else
    {
        write("You can't draw upon the magic, as if resisted by the " +
            "very air around you.\n");
    }
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
    write("You don't have mana enough to properly cast the spell.\n");
}

/*
 * Function name: hook_no_ingredients_fail
 * Description:   Return the message that should be printed when the caster
 *                doesn't have the right ingredients
 * Returns:       The message to print.
 */
public void
hook_no_ingredients_fail(mixed *ingredients_needed)
{
    write("Sorry, but you are not properly prepared to cast the spell!\n");
}

/*
 * Function name: hook_no_identify_herb_ingredient
 * Description:   Return the message that should be printed when the caster
 *                can't identify an herbal ingredient
 * Returns:       The message to print.
 */
public void
hook_no_identify_herb_ingredient(object unidentified_herb)
{
    write("Sorry, but you have no idea how to use one of your herbal ingredients!\n");
}

public void
hook_ingredients_lost_fail(object *ingredients_found)
{
    write("You have lost some of the ingredients!\n");
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
    write("Nobody here to cast the spell on!\n");
}

/*
 * Function name: hook_changed_env
 * Description:   Return the string that will be printed to the caster when
 *                he or she has moved rooms while preparing the spell.
 * Returns:       The message to print.
 */
public void
hook_changed_env()
{
    write("You have lost concentration while moving!\n");
}

/*
 * Function name: hook_use_ingredients
 * Description:   This function should return the message that will be printed
 *                to the caster when he/she has used some ingredients.
 * Arguments:     ingrs - The ingredients that will be used.
 * Returns:       The message to print.
 */
public void
hook_use_ingredients(object *ingrs)
{
    if (sizeof(ingrs))
    {
        write("You sacrifice " + COMPOSITE_ALL_DEAD(ingrs) + ".\n");
    }
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
    write("You can't cast a spell on " +
        target->query_the_name(this_player()) + ".\n");
}

public void
hook_stun_fail(object ability)
{
    write("You are too stunned!\n");
}

public void
hook_cannot_see_fail(object ability)
{
    write("You cannot see to cast the spell!\n");
}

public void
hook_already_has_spell_object(object caster, object target)
{
    write("You have already cast it!\n");
}

public void
hook_resist_spell_object(object *spell_objects, object caster, object *targets)
{
    caster->catch_msg("Your spell was resisted by "
    + FO_COMPOSITE_LIVE(targets, caster) + ".\n");
}

public void
hook_renew_spell_object(object caster, mixed * targets)
{
    write("You renew the duration of the effect!\n");
}

/*
 * Function:    hook_insufficient_skill
 * Description: This gets called when the player doesn't have the minimum
 *              skill requirements to cast the spell.
 */
public varargs void
hook_insufficient_skill(object caster, int * needed_skills)
{
    string sMessage = "You do not have the required skills to cast this "
        + "spell. You will need to receive more training in ";
    
    string * skill_names = ({ });
    mapping skmap = SS_SKILL_DESC;
    foreach (int skillnum : needed_skills)
    {
        skill_names += ({ skmap[skillnum][0] });
    }
    sMessage += (COMPOSITE_WORDS(skill_names) + ".\n");
    caster->catch_tell(sMessage);
}

/*
 * Function:    hook_casting_shield_failure
 * Description: This gets called when the player fails to cast
 * 		the spell due to interference from worn shields.
 */
public void
hook_casting_shield_failure(object caster, object *shields)
{
    caster->catch_tell("You sense that "+
	FO_COMPOSITE_DEAD(shields, caster) +
	(sizeof(shields) == 1 ? " has " : " have ") +
	"interfered with your spellcasting.\n");
}

public void
hook_enhancer_modified_spell(object caster, object enhancer, object *targets)
{
    string type = "";
    int hand_free = !caster->query_tool(W_LEFT)
                   || !caster->query_tool(W_RIGHT);

    if (hand_free)
        type = "strongly ";
        
    caster->catch_msg("You " + type + "channel your energies through your " 
       + enhancer->short() + ".\n");
}


