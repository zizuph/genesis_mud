/*
 *  Herald Silme spell
 *
 *  Updated and revised by for the new Spellcasting system
 *  By Igneous Feb 1998
 */

#include "spells.h"

inherit SPELL_INHERIT;

void
do_silme_spell(object caster, object *targets, int *resist, int result)
{
    object robe = targets[0];

    if (resist[0] > random(100))
    {
	caster->catch_tell("Your prayer remains unheard.\n");
	return;
    }
    tell_room(ENV(caster),QCTNAME(caster) + " raises "+ HIS_HER(caster)+ 
      " hands in the air, chanting softly to Varda.\n"+CAP(HIS_HER(caster))+ 
      " "+robe->short()+" begins to shimmer with a steady glow.\n", caster);
    caster->catch_tell("You chant a prayer to Elbereth, and your "+
      robe->short()+" begins to shine.\n");

    FIXEUID;
    make_spell_effect_object(query_spell_object(), caster, ({caster}), 
      resist, result);
}

int
create_silme_spell(object caster, object *targets, string args)
{
    if (present("_herald_aura_", caster))
    {
	caster->catch_tell("You may only be effected by one silme "+
	  "prayer at a time.\n");
	return 1;
    }
    default_herald_spell_config();
    set_spell_mana(15);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_LAYMAN) / 2));
    set_spell_time(6);
    set_spell_element(SS_ELEMENT_LIFE, 25);
    set_spell_form(SS_FORM_CONJURATION, 20);
    set_spell_ingredients(0);
    set_spell_effect(do_silme_spell);
    set_spell_object(SPELL_OBJECT_DIR + "aura");
    set_spell_resist(spell_resist_beneficial);
    return 0;
}
