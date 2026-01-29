/*
 *  /d/Gondor/guilds/morgulmage/spells/generic_hooks.c
 * 
 *  File containing hooks that are used in multiple files. This
 *  file can't be used on it's own an needs to be included in 
 *  the spells, as they already inherit the different base spells.
 *
 *  Created by Eowul, September 2009
 */

#include <filter_funs.h>
#include <macros.h>
#include <composite.h>
#include "../morgulmage.h"

#ifndef _NO_DEFAULT_FAILURE_MESSAGE
string query_spell_fail() 
{
    return "You fail to invoke the gift properly.\n";
}
#endif

void hook_room_no_magic_fail(mixed reason, object room)
{
    if (stringp(reason) && strlen(reason))
    {
        write(reason);
    }
    else
    {
        write("A power greater than the Dark Lord prevents you "
            + "from casting this spell.\n" );
    }
}

void hook_room_no_magic_attack_fail(mixed reason, object room)
{
    if (stringp(reason) && strlen(reason))
    {
        write(reason);
    }
    else
    {
        write("A power greater than the Dark Lord prevents you "
            + "from casting this spell.\n" );
    }
}

void hook_no_mana_fail(object ability)
{
    write("You do not feel strong enough to cast the spell.\n");
}

void hook_targets_gone()
{
    write("The target of your spell seems have escaped your wrath.\n");
}

void hook_stun_fail(object ability)
{
    write( "You are too stunned to call upon the Dark Lord.\n" );
}

#ifndef _NO_DEFAULT_CONCENTRATE_MESSAGE
void concentrate_msg(object caster, object *targets, string args)
{
    caster->catch_tell( one_of_list( ({
        "You prepare to employ Dark Sorcery and draw upon the power of the "
        + "Dark Lord.\n",
        "With the powers of the Black Master flowing through you, you "
        + "prepare to employ Dark Sorcery.\n",
        "In preparation to employ Dark Sorcery you draw upon the power "
        + "the Dark Lord has bestowed upon you.\n", }) )  );

    can_see_caster( caster )->catch_msg( one_of_list( ({
        QCTNAME( caster ) + " draws power from the realm of shadows.\n",
        QCTNAME( caster ) + " draws power from the realm of shadows.\n",
        "Suddenly the air feels heavier to breathe as " + QTNAME( caster )
        + " draws power from the realm of shadows.\n",
        "The air stirs and feels heavier to breathe as " + QTNAME( caster )
        + " draws power from the realm of shadows.\n", }) ));
}
#endif

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
    foreach(object ob : ingrs) 
    {
        if (MASTER_OB(ob) == (MORGUL_POTION_DIR + "spell_ingredient")) 
        {
            object *similar_charges = filter(all_inventory(this_player()),
                &operator(==)(ob->query_prop(HEAP_S_UNIQUE_ID))
                @ &->query_prop(HEAP_S_UNIQUE_ID)) - ({ ob });

            int remaining_charges = 0;
            foreach(object charge : similar_charges) 
            {
                remaining_charges += charge->num_heap();
            }

            if ((remaining_charges == 0) && pointerp(ob->query_spell_names())) 
            {
                write("You can no longer cast " 
                    + COMPOSITE_WORDS(ob->query_spell_names()) + ".\n");
            }
        }
    }

    ingrs = filter(ingrs, &->check_seen(this_player()));
    if (sizeof(ingrs))
    {
        write("You sacrificed " + COMPOSITE_ALL_DEAD(ingrs) + ".\n");
    }
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
    write("The Dark Lord rewards preparation. Where are your components "
      + "for " + query_spell_name() + ", wretch?!\n");
}


public void
hook_ingredients_lost_fail(object *ingredients_found)
{
    write("Some spell components have been lost with your bungled"
      + " attempt!\n");
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
    write("Your hasty movements have spoiled your casting!\n");
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
hook_living_no_magic_attack_fail(object target, object ability)
{
    write("What protection is this? Even the gifts of the Dark Lord"
      + " seem unable to be used upon "
      + target->query_the_name(this_player()) + ".\n");
}

public void
hook_cannot_see_fail(object ability)
{
    write("Even the Servants of the East must be able to see their"
      + " victims! You are unable to cast your spell!\n");
}

/*
 * Function:    hook_insufficient_skill
 * Description: This gets called when the player doesn't have the minimum
 *              skill requirements to cast the spell.
 */
public varargs void
hook_insufficient_skill(object caster, int * needed_skills)
{
    string sMessage = "Do not strive beyond your abilities, wretch! You"
      + " first need more training in ";

    string * skill_names = ({ });
    mapping skmap = SS_SKILL_DESC;
    foreach (int skillnum : needed_skills)
    {
        skill_names += ({ skmap[skillnum][0] });
    }
    sMessage += (COMPOSITE_WORDS(skill_names) + ".\n");
    caster->catch_tell(sMessage);
}
