/* File         : /d/Gondor/common/guild/newspells/elbereth.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : April 22nd 2000
 * Purpose      : A spell used to scare away the undead.
 * Related Files: /d/Gondor/common/guild/newspells/spell_inherit.c
 * Comments     : This is the ranger elbereth spell, orginally coded
 *                by the great Elessar Telcontar!
 * Modifications:
 */
#pragma strict_types

#include "/d/Gondor/defs.h"
#include "spells.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include <cmdparse.h>

inherit SPELL_INHERIT;

/* Function name: spell_target_undead
 * Description  : A custom targeting function to search for undead.
 * Arguments    : caster - person casting this spell
 *                str    - the str used for finding a target
 * Returns      : if found, a valid target for the spell
 */
object *
spell_target_undead(object caster, string str)
{
    object *undead;

    if (!str)
    {
	caster->catch_tell("Cast elbereth on whom?\n");
	return ({ });
    }

    undead = PARSE_THIS(str, "[at] / [on] [the] %l");

    undead = filter(undead, &->query_prop(LIVE_I_UNDEAD));
    if (!sizeof(undead))
    {
	caster->catch_tell("What undead do you wish to target?\n");
	return ({});
    }
    if (sizeof(undead) > 1)
    {
	caster->catch_tell("You can only target one undead at a time.\n");
	return ({});
    }

    return undead;
}

/* Function name: elbereth_ingredients
 * Description  : My own ingredient search function, since I need
 *                to find myself a *lit* torch for this spell to 
 *                work.
 * Arguments    : caster - person casting the spell
 * Returns      : 0 or an object pointer to a lit torch.
 */
mixed
elbereth_ingredients(object caster)
{
    object *list;

    // get_item_search_list is a function used to search a players
    // inventory and generate a list of accessable items for spellcasting.
    list = get_item_search_list(caster);

    // Are any of these torch objects?
    list = filter(list, &operator(==)(TORCH_OBJECT) @
      &function_exists("create_object",));
    // Are any of these torches lit?
    list = filter(list, &->query_prop(OBJ_I_HAS_FIRE));

    if (!sizeof(list))
	return 0;

    return ({ list[0] });
}


void
hook_no_ingredients_fail(mixed *ingredients_needed)
{
    write("You need a lit torch in order to ward off the undead.\n");
}

/* Function name: resolve spell
 * Description  : This is the "guts" of the spell. Everything worked
 *                and the spell was cast, this function does the spell
 *                effect and finishes the job.
 * Arguments    : caster  - the person who cast the spell
 *                targets - Who the spell was cast on
 *                resist  - How must the targets resisted the spell
 *                success - How well the spell was cast
 */
void
resolve_spell(object caster, object *targets, int *resist, int success)
{
    int diff, result, undead, i, x;

    undead = targets[0]->query_prop(LIVE_I_UNDEAD);

    if (undead > 100)
	undead = 100;

    diff = TASK_SIMPLE /2 + undead * (TASK_DIFFICULT - TASK_ROUTINE) / 100;
    if (caster->query_guild_name_race() == "Dunedain")
	diff -= caster->query_dunedain_level() / 2;
    if (caster->query_race() == "elf")
	diff -= caster->query_average_stat() / 2;

    result = caster->resolve_task(diff, 
      ({ SKILL_WEIGHT, 50, SS_SPELLCRAFT,
	SKILL_WEIGHT, 90, SKILL_AVG, TS_WIS, TS_INT, SKILL_END,
	SKILL_WEIGHT, 30, SS_FORM_CONJURATION, 
	SKILL_WEIGHT, 30, SS_ELEMENT_LIFE }), 
      targets[0],
      ({ SKILL_WEIGHT, 30, SS_FORM_ABJURATION,
	SKILL_WEIGHT, 70, SS_ELEMENT_LIFE,
	SKILL_AVG, TS_WIS, TS_DIS, SKILL_END, }) );

    setuid(); seteuid(setuid());
    log_file("elbereth", ctime(time()) + " " + caster->query_name() + " " +
      "casts Elbereth with success: " + result + " against " +
      targets[0]->query_name() + ", undead level: " + undead + ".\n");

    if (success <= 0)
    {
	caster->catch_tell("You desperately wave the burning torch "+
	  "before "+targets[0]->query_the_name(caster) + ".\n");
	targets[0]->catch_tell(caster->query_The_name(targets[0]) +
	  " desperately waves a burning torch before you.\n");
	tell_room(ENV(caster), QCTNAME(caster) + " desperately "+
	  "waves a burning torch before "+QTNAME(targets[0]) +
	  ".\n", ({caster, targets[0]}));
	return;
    }
    caster->catch_tell("You wave the burning torch before "+
      targets[0]->query_the_name(caster) + ", crying:\n\t" +
      "O Elbereth! Gilthoniel!\n");
    targets[0]->catch_tell(caster->query_The_name(targets[0]) +
      " waves a burning torch before you, crying out loudy: \n" +
      "O Elbereth! Gilthoniel!\nYou feel fear seizing your mind "+
      "for a moment!\n");
    tell_room(ENV(caster), QCTNAME(caster) + " waves a burning torch "+
      "before "+QTNAME(targets[0])+", crying: O Elbereth! Gilthoniel!\n",
      ({ caster, targets[0]}));
    targets[0]->add_panic(result + (caster->query_stat(SS_OCCUP) / 2));
    if (result < 33)
	targets[0]->command("$back "+ caster->query_real_name());
    if (IS_MORGUL_MAGE(targets[0]))
	targets[0]->command("$mshriek");
    if (result >= 33)
    {
	i = -1;
	x = min(3, result / 33);
	while (++i < x)
	    targets[0]->run_away();
    }
}

/* Function name: config_spell
 * Description  : configures the spell, allowing you to set the
 *                various spell functions tothe values you wish
 *                for the spell.  Used much like the create_*
 *                function for rooms, monsters, objects etc...
 * Arguments    : caster  - person casting the spell
 *                targets - what the spell is cast on
 *                args    - Extra arguments for the spell
 * Returns      : 1 if the configuration didn't work
 *                0 if everything went ok
 */
int
config_spell(object caster, object *targets, string args)
{
    set_spell_name("elbereth");
    set_spell_desc("Chase away the undead.");
    set_spell_target(spell_target_undead);

    if (!default_ranger_spell_setup(caster))
	return 1;
    set_spell_mana(75);
    set_spell_time(2);
    set_spell_ingredients(elbereth_ingredients);
    set_spell_element(SS_ELEMENT_LIFE, 35);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_peaceful(0);
    set_spell_task(TASK_ROUTINE);
    set_spell_resist(spell_resist);
}
