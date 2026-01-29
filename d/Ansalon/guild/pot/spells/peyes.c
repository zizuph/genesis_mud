/*
 * pEyes
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

    if (result < 5 || resist[0] > result)
    {
	tar->catch_tell("You feel a stabbing pain in your eyes, " +
	    "but it quickly passes.\n");
	all_msgbb(QCTNAME(tar) + " winces.\n", tar);
	return;
    }

    tar->catch_tell("You close your eyes in pain for a moment. " +
	"When you open them you see things better.\n");
    all_msgbb(QCTNAME(tar)+ " closes "+HIS(tar)+" eyes for a moment.\n", tar);

    setuid();
    seteuid(getuid());
    ob = make_spell_effect_object(EYES_OBJ, caster, tar, resist, result);
    ob->set_peyes_time(result * 2);
}

/*
 * Function name: config_spell
 * Description:   configure the spell
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       1/0 - spell configured/not configured (cannot be cast)
 */
public varargs int
config_spell(object caster, object *targets, string arg)
{
    set_spell_name("peyes");
    set_spell_desc("Give yourself the vision of a dragon");

    set_spell_visual(0);
    set_spell_time(6);
    set_spell_element(SS_ELEMENT_LIFE,  45);
    set_spell_form(SS_FORM_ENCHANTMENT, 30);
    set_spell_mana(61);
    set_spell_task(TASK_ROUTINE);
    set_spell_resist(spell_resist_beneficial);
    set_spell_target(spell_target_one_present_living);
    set_spell_target_verify(spell_verify_present);

#ifndef NO_INGREDIENTS
    set_spell_ingredients(({"eye","eye"}));
#endif

    return 0;
}
