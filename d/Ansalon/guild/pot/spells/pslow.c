/*
 * pSlow
 */

#pragma strict_types

inherit "/d/Ansalon/guild/pot/spells/std_pot_spell";

#include "/d/Ansalon/common/defs.h"
#include "../spells.h"
#include "../guild.h"
#include <macros.h>
#include <tasks.h> 

/* Function name: query_spell_level
 * Description:   Internally used by the standing system
 * Returns:       int - the spell level
 */
int
query_spell_level()
{
    return 5;
}

/*
 * Function name: resolve_spell
 * Description:   Complete the casting of the spell
 * Arguments:     object caster   - the caster
 *                object *targets - an array of targets
 *                int *resist     - resistance percentages corresponding to
 *                                  each target
 *                int result      - how well the spell was cast
 */
public void
resolve_spell(object caster, object *targets, int *resist, int result)
{
    object ob, tar = targets[0];

    if (!P("needle", caster) && !caster->query_prop("_wizard_ignore_spell_ingredients"))
    {
    	caster->catch_tell("In a hurry you cannot find a needle!\n");
    	return;
    }

    if (caster->query_wiz_level())
	caster->catch_tell("*** pslow: resist "+resist[0]+", result "+result+" ***\n");

    result = ((100 - resist[0]) * 3 * result) / 200;

    if ((result < 5) || P(SLOW_ID,tar))
    {
	caster->catch_tell("You prick your thumb with the needle and blow "+
	    "a drop of blood in "+tar->query_the_name(caster)+
	    "'s direction. The air around "+HIM(tar)+
	    " colors to red for a brief moment.\n");
	all_msgbb(QCTNAME(caster)+" pricks "+HIS(caster)+
	    " thumb with the needle and blows a drop of blood in "+
	    QTNAME(tar)+"'s direction. The air around "+HIM(tar)+
	    " colors to red for a brief moment.\n", caster, tar);
	if (caster->check_seen(tar))
	{
	    tar->catch_tell(caster->query_The_name(tar)+" pricks "+HIS(caster)+
	    " thumb with the needle and blows a drop of blood in your "+
	    "direction. The air around you colors to red for a brief moment.\n");
	}
	else if (tar->can_see_in_room())
	{
	    tar->catch_tell("The air around you colors to red for a brief moment.\n");
	}
	return;
    }

    caster->catch_tell("You prick your thumb with the needle and blow "+
        "a drop of blood in "+tar->query_the_name(caster)+
        "'s direction. The air around "+HIM(tar)+" colors to red.\n");
    all_msgbb(QCTNAME(caster)+" pricks "+HIS(caster)+
        " thumb with the needle and blows a drop of blood in "+
        QTNAME(tar)+"'s direction. The air around "+HIM(tar)+
        " colors to red.\n", caster, tar);
    if (caster->check_seen(tar))
    {
        tar->catch_tell(caster->query_The_name(tar)+" pricks "+HIS(caster)+
        " thumb with the needle and blows a drop of blood in your "+
        "direction. The air around you colors to red.\n");
    }
    else if (tar->can_see_in_room())
    {
        tar->catch_tell("The air around you colors to red.\n");
    }

    GUILD_ADMIN->log(caster, "pslow", tar->query_real_name() + " (" +
        file_name(tar) + "): " + result + ", resist: " + resist[0]);

    setuid();
    seteuid(getuid());
    ob = make_spell_effect_object(SLOW_OBJ, caster, tar, resist, result);
    ob->set_pslow_time(result);
}

/*
 * pslow_target: a combination of spell_target_one_other_present_living
 * and spell_target_one_present_enemy
 */
public object *
pslow_target(object caster, string str)
{
    if (!stringp(str) || (str == ""))
        return spell_target_one_present_enemy(caster, str);
    else
        return spell_target_one_other_present_living(caster, str);
}


/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       0/1 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string argument)
{
    if (caster && !P("needle", caster) && !caster->query_prop("_wizard_ignore_spell_ingredients"))
    {
    	caster->catch_tell("You need a needle!\n");
       	return 1;
    }

    set_spell_name("pslow");
    set_spell_desc("Slow down your enemy with thickening air");
    
    set_spell_time(5);
    set_spell_element(SS_ELEMENT_AIR, 35);
    set_spell_form(SS_FORM_ENCHANTMENT, 40);
    set_spell_mana(65);
    set_spell_task(TASK_ROUTINE);
    set_spell_target(pslow_target);
    set_spell_target_verify(spell_verify_present);
    set_spell_stationary(0);
    
    set_spell_offensive(1);
    
#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"tiger lily"}));
#endif

    return 0;
}
