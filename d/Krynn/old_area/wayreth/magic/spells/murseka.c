/*
 * Murseka
 *
 * Description: A combat spell that will cause unarmed hits from the
		caster to cause chilling effects.
 * Class:       2
 * Ingredients: myrtleberry and horsetail
 * Mana:        50 (1/3)
* Tax:    0.7
 * Skills:      SS_ELEMENT_DEATH
 *              SS_FORM_ENCHANTMENT
 * Task:        TASK_ROUTINE
 * Restriction: Must be member and may be in combat,
 *              the caster must not be gagged.
 */
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include <language.h>

#define MURSEKA_OBJ "/d/Krynn/wayreth/magic/obj/murseka"

public void murseka_message(object caster, object *targets);

public int
create_spell_murseka(string arg)
{
    if (stringp(arg) && arg != "")
    {
        write("You can only use this spell upon yourself.\n");
	return 1;
    }

    if (check_gagged())
        return 1;

    object *effects = tar->query_magic_effects();
	int t = query_spell_result()[0];
	int size = sizeof(effects);
    
	while(size--)
	{
	    if (MASTER_OB(effects[size]) == MURSEKA_OBJ)
	      {
		write("You already are under the effects of murseka!\n");
		return 1;
	      }
	}

    set_spell_element(SS_ELEMENT_DEATH, 10);
    set_spell_form(SS_FORM_ENCHANTMENT, 7);

    set_spell_fail(spell_wohs_fail);

    set_spell_time(3);
    set_spell_task(TASK_ROUTINE);

    set_spell_mana(25);
    set_find_target(find_caster);
    set_spell_message(murseka_message);
    set_spell_object(MURSEKA_OBJ);
    set_spell_ingredients("mint");
}

public int
do_murseka(string str)
{
    return cast_spell();
}

public void
murseka_message(object caster, object *targets)
{
    object tar = targets[0];
    
    tell_room(E(caster), QCTNAME(caster) + " whispers something and "+
	POSSESSIVE(caster)+ " hands become surrounded by a chilling "+
	"aura.\n", caster)
    caster->catch_msg("You murmer words of power and your hands "+
	"become surrounded by a chilling aura.\n");

    set_spell_duration(60 + (4*t > 500 ? 500 : 4*t));
}
