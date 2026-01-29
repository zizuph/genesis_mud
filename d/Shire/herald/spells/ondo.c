/*
 *  Herald Ondo Spell
 *
 *  Updated and revised by for the new Spellcasting system
 *  by Igneous Feb 1998
 */

#include "spells.h"

inherit SPELL_INHERIT;

void
wear_off(object robe)
{
    if (!objectp(robe) || !objectp(ENV(robe)))
	return;
    robe->ondo_spell(0);
    ENV(robe)->catch_tell("Your flawless flowing white robe glimmers "+
      "again, then grows lighter.\n");
}

void
do_ondo_spell(object caster, object *targets, int *resist, int result)
{
    if (resist[0] > random(100))
    {
	caster->catch_tell("You prayer reamins unheard.\n");
	return;
    }
    set_alarm(itof((400 + result) / 2), 0.0, &wear_off(targets[0]));
    result = MAX(10, MIN(40, result));
    targets[0]->ondo_spell(result);
    caster->catch_tell("You touch your hands to the ground, and "+
      "gain strength from the rock and the earth.\n"+
      "Your robe shimmers and then dims slightly, growing heavier.\n");
    tell_room(environment(caster), QCTNAME(caster) + " touches "+
      HIS_HER(caster)+" hands to the ground.  When "+HE_SHE(caster)+
      " stands "+HE_SHE(caster)+" is visibly strengthened.\n", ({caster}));

}

int
create_ondo_spell(object caster, object *targets, string args)
{
    if (targets[0]->query_ondo_effect())
    {
	caster->catch_tell("But your robe is already under the "+
	  "effects of the ondo prayer.\n");
	return 1;
    }
    default_herald_spell_config();
    set_spell_mana(60);
    set_spell_time(6);
    set_spell_peaceful(0);
    set_spell_task((TASK_ROUTINE + 150) - (caster->query_stat(SS_LAYMAN) / 2));
    set_spell_element(SS_ELEMENT_EARTH, 40);
    set_spell_form(SS_FORM_DIVINATION,  30);
    set_spell_ingredients(({ "_prot_spell_ingr1_" }));
    set_spell_effect(do_ondo_spell);
}
