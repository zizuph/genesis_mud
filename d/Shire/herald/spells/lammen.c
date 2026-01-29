/*  
 *    Herald Lammen spell
 *
 *    Updated and revised by for the new Spellcasting system
 *    by Igneous, Feb 1998.
 */

#include "spells.h"

inherit SPELL_INHERIT;

void
do_lammen_spell(object caster, object *targets, int *resist, int result)
{
    if (resist[0] > random(100))
    {
	caster->catch_tell("Your prayer remains unheard.\n");
	return;
    }

    tell_room(ENV(caster),QCTNAME(caster) + " raises "+HIS_HER(caster)+ 
      " hands to the sky, calling on Manwe for power.\n"+
      CAP(HIS_HER(caster))+ " voice rises to a tremendous "+
      "crescendo.\n", ({ caster }));
    caster->catch_tell("You call upon Manwe for his voice, and "+
      "you feel your voice begin to strengthen.\n");
    FIXEUID;
    make_spell_effect_object(query_spell_object(), caster, targets,
      resist, result);
}

int
create_lammen_spell(object caster, object *targets, string args)
{
    if (present("_herald_mic", caster))
    {
	caster->catch_tell("You already speak with the voice of Manwe.\n");
	return 1;
    }
    default_herald_spell_config();
    set_spell_mana(15);
    set_spell_time(6);
    set_spell_task(TASK_SIMPLE - (caster->query_stat(SS_LAYMAN) / 4));
    set_spell_element(SS_ELEMENT_EARTH, 10);
    set_spell_form(SS_FORM_DIVINATION,  10);
    set_spell_ingredients(0);
    set_spell_effect(do_lammen_spell);
    set_spell_resist(spell_resist_beneficial);
    set_spell_object(SPELL_OBJECT_DIR + "mic");
    return 0;
}
