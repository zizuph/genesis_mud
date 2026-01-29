/*
 *  Herlad know alignment spell
 *
 *  Redone and updated for the new Spellcasting system by
 *  Igneous Feb, 1998.
 */

#include "spells.h"

inherit SPELL_INHERIT;

void
do_khil_spell(object caster, object *targets, int *resist, int result)
{
    int align;

    if (resist[0] > random(100))
    {
	caster->catch_tell(targets[0]->query_The_name(caster) +
	  " resists your prayer.\n");
	return;
    }

    align = targets[0]->query_alignment();
    switch (align)
    {
    case -1200..-800:
	caster->catch_tell(targets[0]->query_The_name(caster) +
	  " is lost in the darkness of Melkor.\n");
	break;
    case -799..-300:
	caster->catch_tell(targets[0]->query_The_name(caster) +
	  " knows darkness well.\n");
	break;
    case -299..-1:
	caster->catch_tell(targets[0]->query_The_name(caster) +
	  " is beginning to gather shadows.\n");
	break;
    case 0..300:
	caster->catch_tell(targets[0]->query_The_name(caster) +
	  " is not captured by the darkness.\n");
	break;
    case 301..799:
	caster->catch_tell(targets[0]->query_The_name(caster) +
	  " seems to know something of the Valar.\n");
	break;
    case 800..1200:
	caster->catch_tell(targets[0]->query_The_name(caster) +
	  " is a true enemy of Melkor.\n");
	break;
    default:
	caster->catch_tell(targets[0]->query_The_name(caster) +
	  " baffles you.\n");
	break;
    }
}

int
create_khil_spell(object caster, string args, object *targets)
{
    default_herald_spell_config();
    set_spell_time(6);
    set_spell_mana(30);
    set_spell_task(TASK_ROUTINE - (caster->query_stat(SS_LAYMAN) / 2));
    set_spell_ingredients(0);
    set_spell_peaceful(0);
    set_spell_element(SS_ELEMENT_LIFE, 25);
    set_spell_form(SS_FORM_DIVINATION, 30);
    set_spell_effect(do_khil_spell);
}
