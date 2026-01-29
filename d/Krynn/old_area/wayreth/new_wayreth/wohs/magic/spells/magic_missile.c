/*
 * A simple damage spell
 *
 */

#pragma strict_types

inherit "/d/Genesis/magic/components";
inherit "/d/Genesis/magic/resist";
inherit "/d/Genesis/magic/targetting";
inherit "/d/Genesis/magic/spell_config";

#include <ss_types.h>
#include <tasks.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <wa_types.h>


/*
 * Function prototypes
 *
 */
public void magic_missile(object caster, object *targets, int *resist,
    int result);

public void magic_missile_conc_msg(object caster, object *targets,
    string arg);

public int create_spell_magic_missile(object caster, string argument,
    object *targets);

/*
 * Here we define what the spell object does when it adds us as a
 * spell.
 */
public void
add_spell_magic_missile()
{
    this_object()->add_spell("missile", "Fire a magical arrow",
	create_spell_magic_missile, spell_target_one_present_enemy);
}

/*
 * Function name: create_spell_magic_missile
 * Description:   configure the spell "magic missile"
 * Arguments:     object caster   - the caster
 *                object *targets - array of spell targets found
 *                string argument - arguments to the spell invocation
 * Returns:       int - 1 - spell configured
 *                      0 - spell not configured (cannot be cast)
 */
public int
create_spell_magic_missile(object caster, object *targets, string argument)
{
    set_spell_time(4);	// The amount of time for concentration
    set_spell_mana(60); // The amount of mana used in a successful cast
    set_spell_task(TASK_ROUTINE); // See 'man tasks'

    /* We have de
    set_spell_element(SS_ELEMENT_AIR, 20); // The spell is an air spell and
                                           // (figure out task part)
    set_spell_form(SS_FORM_ENCHANTMENT, 20); // Enchantment ... it enchants
                                             // 

}
